OUTPUT_FORMAT("elf32-i386")
ENTRY(_entry)
SECTIONS
{
    .text 0xC0000000 :
    {
        *(.text)
    }

    .data :
    {
        . = ALIGN(4096);
        *(.data)
    }

    .rodata :
    {
        . = ALIGN(4096);
        *(.rodata)
    }

    .bss :
    {
        . = ALIGN(4096);
        *(.bss)
    }
}