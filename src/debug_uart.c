

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "debug_uart.h"
#include "driverlib.h"
#include "uformat/uformat.h"


struct RingBufferInfo {
    uint16_t nbytes;
    uint16_t wp;
    uint16_t rp;
};

#define RB_Push(bfr, info, val, len) do { \
    bfr[info.wp] = val; \
    info.wp = (info.wp + 1) % len; \
    ++info.nbytes; \
} while(0)

#define RB_Front(bfr, info)  (bfr[info.rp])

#define RB_Pop(info, len) do { \
    info.rp = (info.rp + 1) % len; \
    --info.nbytes; \
} while(0)


#define RB_Full(info, len)  (info.nbytes == len)
#define RB_Clear(info) do { \
    info.rp = 0; \
    info.wp = 0; \
    info.nbytes = 0; \
} while(0)


//*****************************************************************************
// Static variables
//*****************************************************************************

// Output ring buffer is written only from user code and read only from interrupt.
// Input ring buffer is written only from interrupt and read only from user code.
// echoPtr is an alternate read pointer for the input buffer, used by the interrupt
// to echo input characters.

static volatile char dbg_outputBuffer[DBG_OUT_BUFFER_SIZE];
static volatile struct RingBufferInfo outputRB = {0, 0, 0};

static char dbg_inputBuffer[DBG_IN_BUFFER_SIZE];
static volatile struct RingBufferInfo inputRB = {0, 0, 0};
uint16_t echoPtr = 0;

// Number of \r characters in the input buffer. Used for quickly checking for
// input lines.
volatile static int newlines = 0;

//*****************************************************************************
// Character output functions
// dbg_putc() will block until space is available, dbg_putc_nb() will drop
// characters.
//*****************************************************************************
int dbg_putc(char ch, void * userdata)
{
    if(ROM_UARTSpaceAvail(UART0_BASE) && outputRB.nbytes == 0)
    {
        ROM_UARTCharPutNonBlocking(UART0_BASE, ch);
    }
    else
    {
        while(RB_Full(outputRB, DBG_OUT_BUFFER_SIZE))
            {;}
        
        RB_Push(dbg_outputBuffer, outputRB, ch, DBG_OUT_BUFFER_SIZE);
    }
    return 0;
}

int dbg_putc_nb(char ch, void * userdata)
{
    if(ROM_UARTSpaceAvail(UART0_BASE) && outputRB.nbytes == 0)
    {
        ROM_UARTCharPutNonBlocking(UART0_BASE, ch);
    }
    else
    {
        if(!RB_Full(outputRB, DBG_OUT_BUFFER_SIZE))
            RB_Push(dbg_outputBuffer, outputRB, ch, DBG_OUT_BUFFER_SIZE);
    }
    return 0;
}


//*****************************************************************************
//*****************************************************************************
void dbg_putstr(const char * str)
{
    while(*str != '\0')
        dbg_putc(*str++, NULL);
}

void dbg_putstr_nb(const char * str)
{
    while(*str != '\0')
        dbg_putc_nb(*str++, NULL);
}


//*****************************************************************************
//*****************************************************************************
void dbg_printf(const char * format, ...)
{
    int len = DBG_OUT_BUFFER_SIZE - outputRB.nbytes;
    va_list args;
    va_start(args, format);
    vprintf_chars(dbg_putc, NULL, len, format, args);
    va_end(args);
}

void dbg_printf_nb(const char * format, ...)
{
    int len = DBG_OUT_BUFFER_SIZE - outputRB.nbytes;
    va_list args;
    va_start(args, format);
    vprintf_chars(dbg_putc_nb, NULL, len, format, args);
    va_end(args);
}


//*****************************************************************************
//*****************************************************************************
int dbg_getline_nb(char * bfr, int len)
{
    int nchars = 0;
    if(newlines > 0)
    {
        while(nchars < len)
        {
            char ch = RB_Front(dbg_inputBuffer, inputRB);
            RB_Pop(inputRB, DBG_IN_BUFFER_SIZE);
            if(ch == '\r')
            {
                *bfr++ = '\0';
                break;
            }
            else
            {
                *bfr++ = ch;
                ++nchars;
            }
        }
        --newlines;
    }
    return nchars;
} // dbg_getline_nb()


//*****************************************************************************
// UART interrupt handler.
//*****************************************************************************
void UART0_IntHandler(void)
{
    uint32_t status = ROM_UARTIntStatus(UART0_BASE, true);
    ROM_UARTIntClear(UART0_BASE, status);
    
    // drain rx FIFO
    while(ROM_UARTCharsAvail(UART0_BASE))
    {
        char ch = ROM_UARTCharGetNonBlocking(UART0_BASE);
        
        if(inputRB.nbytes < DBG_IN_BUFFER_SIZE)
        {
            RB_Push(dbg_inputBuffer, inputRB, ch, DBG_IN_BUFFER_SIZE);
            if(ch == '\r')
                ++newlines;
        }
        else
        {
            // Attempt to report overflow and clear buffer
            // Must do this to avoid condition where buffer is full and code
            // is waiting for a newline that can not fit in the buffer.
            dbg_putstr_nb("\rRXOVF\r\n");
            RB_Clear(inputRB);
            newlines = 0;
        }
    }
    
    // feed tx FIFO
    // Echo received characters
    while(ROM_UARTSpaceAvail(UART0_BASE) && echoPtr != inputRB.wp)
    {
        ROM_UARTCharPutNonBlocking(UART0_BASE, dbg_inputBuffer[echoPtr]);
        echoPtr = (echoPtr + 1) % DBG_IN_BUFFER_SIZE;
    }
    // Write pending characters
    while(ROM_UARTSpaceAvail(UART0_BASE) && outputRB.nbytes > 0)
    {
        ROM_UARTCharPutNonBlocking(UART0_BASE, RB_Front(dbg_outputBuffer, outputRB));
        RB_Pop(outputRB, DBG_OUT_BUFFER_SIZE);
    }
} // UART0_IntHandler()



//*****************************************************************************
//*****************************************************************************
#define UART_CFG_8N1  (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)

void DBG_Init(void)
{
    newlines = 0;
    
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), DBG_BAUD, UART_CFG_8N1);
    ROM_UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8);
    
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_TX | UART_INT_RX | UART_INT_RT);
} // DBG_Init()

