

// #include "delay.h"

#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"

#include "drivers/rgb.h"


volatile uint16_t rx_led_ctr = 0;


//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char * filename, uint32_t line)
{
}
#endif

//*****************************************************************************
// UART interrupt handler.
//*****************************************************************************
void UART0_IntHandler(void)
{
    uint32_t status = ROM_UARTIntStatus(UART0_BASE, true);
    ROM_UARTIntClear(UART0_BASE, status);
    
    while(ROM_UARTCharsAvail(UART0_BASE))
    {
        // Just echo typed characters and trigger Rx LED
        char ch = ROM_UARTCharGetNonBlocking(UART0_BASE);
        ROM_UARTCharPutNonBlocking(UART0_BASE, ch);
        rx_led_ctr = 1;
    }
}

//*****************************************************************************
// Send a short string of bytes to the UART. There must be room in the FIFO for
// the data.
//*****************************************************************************
void UART_SendNonblock(const uint8_t * bfr, uint32_t count)
{
    while(count--)
        ROM_UARTCharPutNonBlocking(UART0_BASE, *bfr++);
}

//*****************************************************************************
// Send a string of bytes to the UART, blocking if necessary.
//*****************************************************************************
void UART_Send(const uint8_t * bfr, uint32_t count)
{
    while(count--)
        ROM_UARTCharPut(UART0_BASE, *bfr++);
}

//*****************************************************************************
// Send a C string to the UART, blocking if necessary.
//*****************************************************************************
void UART_PutStr(const char * bfr)
{
    while(*bfr != '\0')
        ROM_UARTCharPut(UART0_BASE, (uint8_t)*bfr++);
}

#define UART_CFG_8N1  (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)
void UART_Init(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200, UART_CFG_8N1);
    
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

void Init_Sys(void)
{
    ROM_FPUEnable();
    // enable lazy stacking if FPU is to be used in interrupt handlers, or multiple tasks.
//    ROM_FPULazyStackingEnable();
    
    // 16 MHz clock directly from the crystal
//    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // System clock frequency is 400 MHz/(2*SYSDIV)
    // 50 MHz clock off PLL
//    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // Max speed: 80 MHz clock off PLL
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}

//*****************************************************************************
// This example demonstrates how to send a string of data to the UART.
//*****************************************************************************
int main(void)
{
    Init_Sys();
    ROM_IntMasterEnable();
    UART_Init();
    
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    // LEDs
    ROM_GPIOPinTypeGPIOOutput(RED_GPIO_BASE, RED_GPIO_PIN);
    GPIOPinWrite(RED_GPIO_BASE, RED_GPIO_PIN, 0);
    ROM_GPIOPinTypeGPIOOutput(GREEN_GPIO_BASE, GREEN_GPIO_PIN);
    GPIOPinWrite(GREEN_GPIO_BASE, GREEN_GPIO_PIN, 0);
    ROM_GPIOPinTypeGPIOOutput(BLUE_GPIO_BASE, BLUE_GPIO_PIN);
    GPIOPinWrite(BLUE_GPIO_BASE, BLUE_GPIO_PIN, 0);
    
    
    
    UART_PutStr("\033[2JReady:\r\n");
    
    static uint16_t heartbeat_ctr = 0;
    while(1)
    {
        if(rx_led_ctr > 0)
        {
            --rx_led_ctr;
            GPIOPinWrite(BLUE_GPIO_BASE, BLUE_GPIO_PIN, BLUE_GPIO_PIN);
        }
        else
        {
            GPIOPinWrite(BLUE_GPIO_BASE, BLUE_GPIO_PIN, 0);
        }
        
        // Blink heartbeat LED
        if(heartbeat_ctr > 0)
        {
            --heartbeat_ctr;
        }
        else
        {
            if(GPIOPinRead(GREEN_GPIO_BASE, GREEN_GPIO_PIN))
            {
                GPIOPinWrite(GREEN_GPIO_BASE, GREEN_GPIO_PIN, 0);
                heartbeat_ctr = 200;
            }
            else
            {
                GPIOPinWrite(GREEN_GPIO_BASE, GREEN_GPIO_PIN, GREEN_GPIO_PIN);
                heartbeat_ctr = 1;
            }
        }
        
        ROM_SysCtlDelay(ROM_SysCtlClockGet()/(1000*3));
    }
}
