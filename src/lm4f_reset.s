/* Reset ISR in assembly */

#include "inc/asmdefs.h"
#include "inc/hw_nvic.h"

.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.word _etext  /* end of .text section (start of initialization data in flash) */
.word _data  /* start of .data section (data in RAM) */
.word _edata  /* end of .data section (data in RAM) */
.word _bss  /* start of .bss section */
.word _ebss /* end of .bss section */


    .global ResetISR
    .type   ResetISR, %function
ResetISR:
    
    /* Initialize .data section from flash */
    /* Load start of .data into r0, end of .data into .r1, source of data into .r2,
       and copy words until r0 >= r1, using r4 as a temporary register. */
    ldr r0, =_data
    ldr r1, =_edata
    ldr r2, =_etext
    
datainit_loop:
        cmp r0, r1
        itt lt
        ldrlt r4, [r2], #4
        strlt r4, [r0], #4
        blt datainit_loop
    
    /* Initialize .bss section with zeros */
    /* Same as above, but r4 is kept set to 0*/
    ldr r0, =_bss
    ldr r1, =_ebss
    movs r4, #0
bssclr_loop:
        cmp r0, r1
        it lt
        strlt r4, [r0], #4
        blt bssclr_loop
    
    bl SystemStartup
    
    b main
