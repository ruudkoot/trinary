/******************************************************************************/
/* Mithrill : System Initializer : IA-32 : IBM : A20 Support                  */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

typedef enum
{
    a20_methode_kbc1,
    a20_methode_vectra
} a20_methode;

bool a20_test(void);
void a20_enable_kbc1(void);
void a20_enable_kbc2(void);
void a20_enable_ps2(void);
void a20_enable_vectra(void);

bool a20_enable(a20_methode methode)
{
    log_item("Enabling A20");

    /* Check if A20 is already enabled.                                       */
    if (a20_test())
    {
        log_status(log_status_success);
        return true;
    }

    /* Try 'Keyboard Controller #1'.                                          */
    log_subitem("Keyboard Controller #1");
    a20_enable_kbc1();
    
    if (a20_test())
    {
        log_status(log_status_success);
        return true;
    }

    /* Try 'Vectra'.                                                          */
    log_subitem("Vectra");
    a20_enable_vectra();

    if (a20_test())
    {
        log_status(log_status_success);
        return true;
    }
}

/******************************************************************************/
/* a20_test                             Enabled A20 Test                      */
/*                                                                            */
/* This funcion test if A20 is enabled.                                       */
/******************************************************************************/
bool a20_test(void)
{
    unsigned a;

    asm
    (
        /* Store a reference byte in conventional memory.                     */
        "movb $0x55, 0xFFEF;"
        
        /* Write a byte into the High Memory Area.                            */
        "movw $0xFFFF, %%ax;"
        "movw %%ax, %%ds;"
        "movb $0xAA, 0xFFFF;"
        "xorw %%ax, %%ax;"
        "movw %%ax, %%ds;"

        /* Load the reference byte.                                           */
        "movb 0xFFEF, %%al;"
        :
        "=a" (a)
    );
    
    /* If the reference byte changed, the HMA wrapped around, meaning A20 is
       disabled.                                                              */
    return (a == 0x55);
}

/******************************************************************************/
/* sys_arch_a20_enable_kbc - Enable A20 (Keyboard Controller)                 */
/******************************************************************************/
void a20_enable_kbc2(void)
{
    unt8 status;
    
    /* Disable the keyboard.                                                  */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xAD);

    /* Read the current status.                                               */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xD0);
    sys_arch_kbc_waitread();
    status = sys_arch_kbc_readdata();

    /* Write the new status.                                                  */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xD1);
    sys_arch_kbc_waitsend();
    sys_arch_kbc_senddata(status | 0x02);

    /* Enable the keyboard.                                                   */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xAE);
}

/******************************************************************************/
/* sys_arch_a20_enable_vectra - Enable A20 (HP Vectra)                        */
/******************************************************************************/
void a20_enable_vectra(void)
{
    /* Disable the keyboard.                                                  */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xAD);

    /* Enable the A20 address line.                                           */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xDF);

    /* Enable the keyboard.                                                   */
    sys_arch_kbc_waitsend();
    sys_arch_kbc_sendcommand(0xAE);
}


/******************************************************************************/
/* sys_arch_a20_enable_vectra - Enable A20 (PS/2 BIOS)                        */
/******************************************************************************/
void a20_enable_ps2(void)
{
    asm("movl $0x2401, %eax; int $0x15;");
}

/******************************************************************************/
/* system_arch_a20_enable - Enable A20 Address Line                           */
/*                                                                            */
/* This fucntion enabled the A20 address line, which is required for          */
/* accessing memory above 1 MB.                                               */
/******************************************************************************/
void a20_enable_kbc1(void)
{
    asm(
        "A20:"
	    "call empty8042;"
	    "movb $0xD1, %al;"
	    "outb %al, $0x64;"
	    "call empty8042;"
	    "movb $0xDF, %al;"
	    "outb %al ,$0x60;"
	    "call empty8042;"
	    "jmp argq;"

        "empty8042:"
	    "inb $0x64, %al;"
	    "testb $0x02, %al;"
	    "jnz empty8042;"
	    "ret;"

        "argq:"
       );

}
