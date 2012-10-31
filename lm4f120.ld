
MEMORY
{
    flash (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    sram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

ENTRY(ResetISR)

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        
        *(.text*)
        
        *(.rodata)
        *(.rodata*)
        _etext = .;
    } > flash
    
    .preinit_array :
    {
        __preinit_array_start__ = .;
        KEEP(*(.preinit_array*))
        __preinit_array_end__ = .;
    } > flash
    
    .init_array :
    {
        __init_array_start__ = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        __init_array_end__ = .;
    } > flash
    
    .fini_array :
    {
        __fini_array_start__ = .;
        KEEP(*(.fini_array*))
        KEEP(*(SORT(.fini_array.*)))
        __fini_array_end__ = .;
    } > flash
    
    _data_init = .;
    
    .data : AT(_data_init)
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > sram

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > sram
}
