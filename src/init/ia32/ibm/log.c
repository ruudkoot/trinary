/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

unsigned log_status_success = 0x0AFB;

void log_writestring(char* s);

void log_item(char* s)
{
    char t[77];

    strcpy(t, "[ ][.....................................................................]");
    strpst(t + 4, s);

    log_writestring(t);
}

void log_subitem(char* s)
{
    char t[77];

    strcpy(t, "   [.....................................................................]");
    strpst(t + 4, s);

    log_writestring(t);
}

void log_number(string* property, unsigned number)
{
    char value[20];    
    char output[75];

    u32toa(number, value, 10);

    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    
    log_writestring(output);
}

void log_hex(string* property, unsigned number)
{
    char value[20];    
    char output[75];

    u32toa(number, value, 16);

    strcpy(output, "   [.............................................................0000000h]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(72 - strlen(value), 4), value, 66);
    
    log_writestring(output);
}

void log_status(unsigned s)
{
    asm volatile
    (
        /* Set the cursor at the correct position.                            */
        "movb $0x02, %%ah;"
        "xorb %%bh, %%bh;"
        "movw $0x1705, %%dx;"
        "int $0x10;"

        /* Write the status 'icon'.                                           */
        "movb $0x09, %%ah;"
        "xorb %%bh, %%bh;"
        "movw $1, %%cx;"
        "int $0x10;"
        :
        :
        "a" (s),
        "b" (s / 256)
    );
}

void log_writestring(char* s)
{
    asm volatile
    (
        /* Scroll the previous lines up.                                      */
        "movw $0x0601, %%ax;"
        "movb $0x0F, %%bh;"
        "movw $0x0202, %%cx;"
        "movw $0x184F, %%dx;"
        "int $0x10;"

        /* Set the cursor at the correct position.                            */
        "movb $0x02, %%ah;"
        "xorb %%bh, %%bh;"
        "movw $0x1704, %%dx;"
        "int $0x10;"

        /* Write the string to the screen.                                    */
        "cld;"
	    "1:"
            "lodsb;"
            "orb %%al, %%al;"
            "jz 1f;"
            "movb $0x0E, %%ah;"
            "movw $0x000F, %%bx;"
            "int $0x10;"
            "jmp 1b;"
	    "1:"
    :
    :
        "S" (s)
    );
}

