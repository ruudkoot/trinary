OUTPUT_FORMAT("elf32-i386")
ENTRY(_entry)
SECTIONS
{
    .text 0xC0000000 :
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
        data = .; _data = .; __data = .;
        *(.data)
        . = ALIGN(4096);
    }

    .rodata :
    {
        rodata = .; _rodata = .; __rodata = .;
        *(.rodata)
        . = ALIGN(4096);
    }

    .text.init :
    {
        discard = .; _discard = .; __discard = .;
        *(.text.init)
        . = ALIGN(4096);
    }

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }

    end = .; _end = .; __end = .;
}