
#include "common.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

extern int main(void);

static void IntDefaultHandler(void);

void ResetISR(void);
void NmiSR(void) ALIAS(IntDefaultHandler);
void FaultISR(void) ALIAS(IntDefaultHandler);
void MPU_FaultISR(void) ALIAS(IntDefaultHandler);
void BusFaultISR(void) ALIAS(IntDefaultHandler);
void UsageFaultISR(void) ALIAS(IntDefaultHandler);

// Default interrupt handlers
void SVCall_IntHandler(void) ALIAS(IntDefaultHandler);
void DebugMon_IntHandler(void) ALIAS(IntDefaultHandler);
void PendSV_IntHandler(void) ALIAS(IntDefaultHandler);
void SysTick_IntHandler(void) ALIAS(IntDefaultHandler);

void Hibernate_IntHandler(void) ALIAS(IntDefaultHandler);
void SYSCON_IntHandler(void) ALIAS(IntDefaultHandler);
void FLASH_IntHandler(void) ALIAS(IntDefaultHandler);
void FPU_IntHandler(void) ALIAS(IntDefaultHandler);
void PECI0_IntHandler(void) ALIAS(IntDefaultHandler);
void LPC0_IntHandler(void) ALIAS(IntDefaultHandler);

void uDMA_SoftTrans_IntHandler(void) ALIAS(IntDefaultHandler);
void uDMA_Error_IntHandler(void) ALIAS(IntDefaultHandler);

void GPIOA_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOB_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOC_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOD_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOE_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOF_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOG_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOH_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOJ_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOK_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOL_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOM_IntHandler(void) ALIAS(IntDefaultHandler);
void GPION_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP1_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP2_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP3_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP4_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP5_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP6_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOP7_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ1_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ2_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ3_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ4_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ5_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ6_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOQ7_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOR_IntHandler(void) ALIAS(IntDefaultHandler);
void GPIOS_IntHandler(void) ALIAS(IntDefaultHandler);

void UART0_IntHandler(void) ALIAS(IntDefaultHandler);
void UART1_IntHandler(void) ALIAS(IntDefaultHandler);
void UART2_IntHandler(void) ALIAS(IntDefaultHandler);
void UART3_IntHandler(void) ALIAS(IntDefaultHandler);
void UART4_IntHandler(void) ALIAS(IntDefaultHandler);
void UART5_IntHandler(void) ALIAS(IntDefaultHandler);
void UART6_IntHandler(void) ALIAS(IntDefaultHandler);
void UART7_IntHandler(void) ALIAS(IntDefaultHandler);

void SSI0_IntHandler(void) ALIAS(IntDefaultHandler);
void SSI1_IntHandler(void) ALIAS(IntDefaultHandler);
void SSI2_IntHandler(void) ALIAS(IntDefaultHandler);
void SSI3_IntHandler(void) ALIAS(IntDefaultHandler);

void I2C0_IntHandler(void) ALIAS(IntDefaultHandler);
void I2C1_IntHandler(void) ALIAS(IntDefaultHandler);
void I2C2_IntHandler(void) ALIAS(IntDefaultHandler);
void I2C3_IntHandler(void) ALIAS(IntDefaultHandler);
void I2C4_IntHandler(void) ALIAS(IntDefaultHandler);
void I2C5_IntHandler(void) ALIAS(IntDefaultHandler);

void I2S0_IntHandler(void) ALIAS(IntDefaultHandler);

void CAN0_IntHandler(void) ALIAS(IntDefaultHandler);
void CAN1_IntHandler(void) ALIAS(IntDefaultHandler);
void CAN2_IntHandler(void) ALIAS(IntDefaultHandler);

void Ethernet_IntHandler(void) ALIAS(IntDefaultHandler);

void USB0_IntHandler(void) ALIAS(IntDefaultHandler);

void EBI0_IntHandler(void) ALIAS(IntDefaultHandler);

void PWMFault_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM0_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM1_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM2_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM3_IntHandler(void) ALIAS(IntDefaultHandler);

void PWM1Fault_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM1_0_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM1_1_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM1_2_IntHandler(void) ALIAS(IntDefaultHandler);
void PWM1_3_IntHandler(void) ALIAS(IntDefaultHandler);

void Quad0_IntHandler(void) ALIAS(IntDefaultHandler);
void Quad1_IntHandler(void) ALIAS(IntDefaultHandler);
void Quad2_IntHandler(void) ALIAS(IntDefaultHandler);

void Fan0_IntHandler(void) ALIAS(IntDefaultHandler);

void ADC_Seq0_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC_Seq1_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC_Seq2_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC_Seq3_IntHandler(void) ALIAS(IntDefaultHandler);

void ADC1_Seq0_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC1_Seq1_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC1_Seq2_IntHandler(void) ALIAS(IntDefaultHandler);
void ADC1_Seq3_IntHandler(void) ALIAS(IntDefaultHandler);

void AComp0_IntHandler(void) ALIAS(IntDefaultHandler);
void AComp1_IntHandler(void) ALIAS(IntDefaultHandler);
void AComp2_IntHandler(void) ALIAS(IntDefaultHandler);

void WDT_IntHandler(void) ALIAS(IntDefaultHandler);

void Timer0A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer0B_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer1A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer1B_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer2A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer2B_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer3A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer3B_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer4A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer4B_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer5A_IntHandler(void) ALIAS(IntDefaultHandler);
void Timer5B_IntHandler(void) ALIAS(IntDefaultHandler);

void WTimer0A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer0B_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer1A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer1B_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer2A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer2B_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer3A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer3B_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer4A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer4B_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer5A_IntHandler(void) ALIAS(IntDefaultHandler);
void WTimer5B_IntHandler(void) ALIAS(IntDefaultHandler);


// Stack is left to the linker to locate
#ifndef STACK_SIZE
static uint32_t mainStack[64];
#else
static uint32_t mainStack[(STACK_SIZE + 3)/4];// round up to multiple of 4 bytes
#endif

typedef void (*isr_handler_t)(void);

__attribute__ ((section(".isr_vector")))
const isr_handler_t isrVector[] =
{
    (isr_handler_t)((uint32_t)mainStack + sizeof(mainStack)),
    ResetISR,                  // Reset handler
    NmiSR,                     // NMI handler
    FaultISR,                  // hard fault handler
    MPU_FaultISR,              // MPU fault handler
    BusFaultISR,               // bus fault handler
    UsageFaultISR,             // usage fault handler
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    SVCall_IntHandler,         // SVCall handler
    DebugMon_IntHandler,       // Debug monitor handler
    0, // Reserved
    PendSV_IntHandler,         // PendSV handler
    SysTick_IntHandler,        // SysTick handler
    GPIOA_IntHandler,          // GPIO Port A
    GPIOB_IntHandler,          // GPIO Port B
    GPIOC_IntHandler,          // GPIO Port C
    GPIOD_IntHandler,          // GPIO Port D
    GPIOE_IntHandler,          // GPIO Port E
    UART0_IntHandler,          // UART0 Rx and Tx
    UART1_IntHandler,          // UART1 Rx and Tx
    SSI0_IntHandler,           // SSI0 Rx and Tx
    I2C0_IntHandler,           // I2C0 Master and Slave
    PWMFault_IntHandler,       // PWM Fault
    PWM0_IntHandler,           // PWM Generator 0
    PWM1_IntHandler,           // PWM Generator 1
    PWM2_IntHandler,           // PWM Generator 2
    Quad0_IntHandler,          // Quadrature Encoder 0
    ADC_Seq0_IntHandler,       // ADC Sequence 0
    ADC_Seq1_IntHandler,       // ADC Sequence 1
    ADC_Seq2_IntHandler,       // ADC Sequence 2
    ADC_Seq3_IntHandler,       // ADC Sequence 3
    WDT_IntHandler,            // Watchdog timer
    Timer0A_IntHandler,        // Timer 0 subtimer A
    Timer0B_IntHandler,        // Timer 0 subtimer B
    Timer1A_IntHandler,        // Timer 1 subtimer A
    Timer1B_IntHandler,        // Timer 1 subtimer B
    Timer2A_IntHandler,        // Timer 2 subtimer A
    Timer2B_IntHandler,        // Timer 2 subtimer B
    AComp0_IntHandler,         // Analog Comparator 0
    AComp1_IntHandler,         // Analog Comparator 1
    AComp2_IntHandler,         // Analog Comparator 2
    SYSCON_IntHandler,         // System Control (PLL, OSC, BO)
    FLASH_IntHandler,          // FLASH Control
    GPIOF_IntHandler,          // GPIO Port F
    GPIOG_IntHandler,          // GPIO Port G
    GPIOH_IntHandler,          // GPIO Port H
    UART2_IntHandler,          // UART2 Rx and Tx
    SSI1_IntHandler,           // SSI1 Rx and Tx
    Timer3A_IntHandler,        // Timer 3 subtimer A
    Timer3B_IntHandler,        // Timer 3 subtimer B
    I2C1_IntHandler,           // I2C1 Master and Slave
    Quad1_IntHandler,          // Quadrature Encoder 1
    CAN0_IntHandler,           // CAN0
    CAN1_IntHandler,           // CAN1
    CAN2_IntHandler,           // CAN2
    Ethernet_IntHandler,       // Ethernet
    Hibernate_IntHandler,      // Hibernate
    USB0_IntHandler,           // USB0
    PWM3_IntHandler,           // PWM Generator 3
    uDMA_SoftTrans_IntHandler, // uDMA Software Transfer
    uDMA_Error_IntHandler,     // uDMA Error
    ADC1_Seq0_IntHandler,      // ADC1 Sequence 0
    ADC1_Seq1_IntHandler,      // ADC1 Sequence 1
    ADC1_Seq2_IntHandler,      // ADC1 Sequence 2
    ADC1_Seq3_IntHandler,      // ADC1 Sequence 3
    I2S0_IntHandler,           // I2S0
    EBI0_IntHandler,           // External Bus Interface 0
    GPIOJ_IntHandler,          // GPIO Port J
    GPIOK_IntHandler,          // GPIO Port K
    GPIOL_IntHandler,          // GPIO Port L
    SSI2_IntHandler,           // SSI2 Rx and Tx
    SSI3_IntHandler,           // SSI3 Rx and Tx
    UART3_IntHandler,          // UART3 Rx and Tx
    UART4_IntHandler,          // UART4 Rx and Tx
    UART5_IntHandler,          // UART5 Rx and Tx
    UART6_IntHandler,          // UART6 Rx and Tx
    UART7_IntHandler,          // UART7 Rx and Tx
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    I2C2_IntHandler,           // I2C2 Master and Slave
    I2C3_IntHandler,           // I2C3 Master and Slave
    Timer4A_IntHandler,        // Timer 4 subtimer A
    Timer4B_IntHandler,        // Timer 4 subtimer B
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved
    Timer5A_IntHandler,        // Timer 5 subtimer A
    Timer5B_IntHandler,        // Timer 5 subtimer B
    WTimer0A_IntHandler,       // Wide Timer 0 subtimer A
    WTimer0B_IntHandler,       // Wide Timer 0 subtimer B
    WTimer1A_IntHandler,       // Wide Timer 1 subtimer A
    WTimer1B_IntHandler,       // Wide Timer 1 subtimer B
    WTimer2A_IntHandler,       // Wide Timer 2 subtimer A
    WTimer2B_IntHandler,       // Wide Timer 2 subtimer B
    WTimer3A_IntHandler,       // Wide Timer 3 subtimer A
    WTimer3B_IntHandler,       // Wide Timer 3 subtimer B
    WTimer4A_IntHandler,       // Wide Timer 4 subtimer A
    WTimer4B_IntHandler,       // Wide Timer 4 subtimer B
    WTimer5A_IntHandler,       // Wide Timer 5 subtimer A
    WTimer5B_IntHandler,       // Wide Timer 5 subtimer B
    FPU_IntHandler,            // FPU
    PECI0_IntHandler,          // PECI 0
    LPC0_IntHandler,           // LPC 0
    I2C4_IntHandler,           // I2C4 Master and Slave
    I2C5_IntHandler,           // I2C5 Master and Slave
    GPIOM_IntHandler,          // GPIO Port M
    GPION_IntHandler,          // GPIO Port N
    Quad2_IntHandler,          // Quadrature Encoder 2
    Fan0_IntHandler,           // Fan 0
    0, // Reserved
    GPIOP_IntHandler,          // GPIO Port P (Summary or P0)
    GPIOP1_IntHandler,         // GPIO Port P1
    GPIOP2_IntHandler,         // GPIO Port P2
    GPIOP3_IntHandler,         // GPIO Port P3
    GPIOP4_IntHandler,         // GPIO Port P4
    GPIOP5_IntHandler,         // GPIO Port P5
    GPIOP6_IntHandler,         // GPIO Port P6
    GPIOP7_IntHandler,         // GPIO Port P7
    GPIOQ_IntHandler,          // GPIO Port Q (Summary or Q0)
    GPIOQ1_IntHandler,         // GPIO Port Q1
    GPIOQ2_IntHandler,         // GPIO Port Q2
    GPIOQ3_IntHandler,         // GPIO Port Q3
    GPIOQ4_IntHandler,         // GPIO Port Q4
    GPIOQ5_IntHandler,         // GPIO Port Q5
    GPIOQ6_IntHandler,         // GPIO Port Q6
    GPIOQ7_IntHandler,         // GPIO Port Q7
    GPIOR_IntHandler,          // GPIO Port R
    GPIOS_IntHandler,          // GPIO Port S
    PWM1Fault_IntHandler,      // PWM 1 Generator 0
    PWM1_0_IntHandler,         // PWM 1 Generator 1
    PWM1_1_IntHandler,         // PWM 1 Generator 2
    PWM1_2_IntHandler,         // PWM 1 Generator 3
    PWM1_3_IntHandler          // PWM 1 Fault
};

static void IntDefaultHandler(void)
{
    while(1)
        {;}
}

extern void __libc_init_array(void) WEAK;

extern void SystemStartup(void) WEAK;
void SystemStartup(void)
{
    // Enable FPU
    HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) &
                         ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
                        NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);
    
    if(__libc_init_array)
        __libc_init_array();
}
