

// #include "delay.h"

#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"

#include "drivers/rgb.h"

#include "debug_uart.h"

volatile uint16_t rx_led_ctr = 0;


//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void __error__(char * filename, uint32_t line)
{
    dbg_printf("%s@%d: driverlib error.\r\n", filename, line);
}
#endif


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



int main(void)
{
    Init_Sys();
    ROM_IntMasterEnable();
    DBG_Init();
    
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
    
    
//     dbg_putstr("\033[2JInitializing...\r\n");
    dbg_putstr("\033[2JInitializing C app...\r\n");
    dbg_putstr("Ready:\r\n");
    
    static uint16_t heartbeat_ctr = 0;
    while(1)
    {
        char cmdbfr[64];
        if(dbg_getline_nb(cmdbfr, 64) > 0)
        {
            GPIOPinWrite(RED_GPIO_BASE, RED_GPIO_PIN, RED_GPIO_PIN);
            dbg_printf("\r\nEntered: %s\r\n", cmdbfr);
        }
        
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
