/******************************************************************************/
/* Signal Handling                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void sched_arch_switch_wrapper(void);

void sig_arch_interrupt_wrapper(void);

void sig_arch_exception_divideerror_wrapper(void);
void sig_arch_exception_debug_wrapper(void);
void sig_arch_exception_nmi_wrapper(void);
void sig_arch_exception_breakpoint_wrapper(void);
void sig_arch_exception_overflow_wrapper(void);
void sig_arch_exception_bounds_wrapper(void);
void sig_arch_exception_opcode_wrapper(void);
void sig_arch_exception_device_wrapper(void);
void sig_arch_exception_double_wrapper(void);
void sig_arch_exception_overrun_wrapper(void);
void sig_arch_exception_tss_wrapper(void);
void sig_arch_exception_segment_wrapper(void);
void sig_arch_exception_stack_wrapper(void);
void sig_arch_exception_protection_wrapper(void);
void sig_arch_exception_page_wrapper(void);
void sig_arch_exception_reserved_wrapper(void);
void sig_arch_exception_math_wrapper(void);
void sig_arch_exception_alignment_wrapper(void);
void sig_arch_exception_machine_wrapper(void);
void sig_arch_exception_sse_wrapper(void);
void sig_arch_exception_unknown14_wrapper(void);
void sig_arch_exception_unknown15_wrapper(void);
void sig_arch_exception_unknown16_wrapper(void);
void sig_arch_exception_unknown17_wrapper(void);
void sig_arch_exception_unknown18_wrapper(void);
void sig_arch_exception_unknown19_wrapper(void);
void sig_arch_exception_unknown1a_wrapper(void);
void sig_arch_exception_unknown1b_wrapper(void);
void sig_arch_exception_unknown1c_wrapper(void);
void sig_arch_exception_unknown1d_wrapper(void);
void sig_arch_exception_unknown1e_wrapper(void);
void sig_arch_exception_unknown1f_wrapper(void);

void sig_arch_irq0_wrapper(void);
void sig_arch_irq1_wrapper(void);
void sig_arch_irq2_wrapper(void);
void sig_arch_irq3_wrapper(void);
void sig_arch_irq4_wrapper(void);
void sig_arch_irq5_wrapper(void);
void sig_arch_irq6_wrapper(void);
void sig_arch_irq7_wrapper(void);
void sig_arch_irq8_wrapper(void);
void sig_arch_irq9_wrapper(void);
void sig_arch_irq10_wrapper(void);
void sig_arch_irq11_wrapper(void);
void sig_arch_irq12_wrapper(void);
void sig_arch_irq13_wrapper(void);
void sig_arch_irq14_wrapper(void);
void sig_arch_irq15_wrapper(void);

typedef struct idt_t
{
    unsigned d1;
    unsigned d2;
} idt_t;

extern void sigWrapper(void);


idt_t sigIDT[256];

void (*sigTable[256])(void);
void sig_arch_setinterruptgate(unsigned intr, void (*func)(void));
void sig_arch_settrapgate(unsigned intr, void (*func)(void));

void discardable sig_arch_init(void)
{
    int i;
    
    struct __attribute ((__packed__))
    {
        unsigned short limit;
        idt_t* address;
    } descriptor;

    descriptor.limit = 0x0800;
    descriptor.address = sigIDT;

    //address = (unsigned*)&descriptor[2];
    //*address = (unsigned)(sigIDT);

    asm ("lidt %0"::"m" (descriptor));
    asm ("sidt 100");
    
    for (i = 0; i < 256; i++)
    {
		sigIDT[i].d1 = 0x00080000 + (((unsigned)(sig_arch_interrupt_wrapper)) & 0x0000FFFF);
		sigIDT[i].d2 = 0x00008E00 + (((unsigned)(sig_arch_interrupt_wrapper)) & 0xFFFF0000);
    }

    sig_arch_settrapgate(0x00, sig_arch_exception_divideerror_wrapper);
    sig_arch_settrapgate(0x01, sig_arch_exception_debug_wrapper);
    sig_arch_settrapgate(0x02, sig_arch_exception_nmi_wrapper);
    sig_arch_settrapgate(0x03, sig_arch_exception_breakpoint_wrapper);
    sig_arch_settrapgate(0x04, sig_arch_exception_overflow_wrapper);
    sig_arch_settrapgate(0x05, sig_arch_exception_bounds_wrapper);
    sig_arch_settrapgate(0x06, sig_arch_exception_opcode_wrapper);
    sig_arch_settrapgate(0x07, sig_arch_exception_device_wrapper);
    sig_arch_settrapgate(0x08, sig_arch_exception_double_wrapper);
    sig_arch_settrapgate(0x09, sig_arch_exception_overrun_wrapper);
    sig_arch_settrapgate(0x0A, sig_arch_exception_tss_wrapper);
    sig_arch_settrapgate(0x0B, sig_arch_exception_segment_wrapper);
    sig_arch_settrapgate(0x0C, sig_arch_exception_stack_wrapper);
    sig_arch_settrapgate(0x0D, sig_arch_exception_protection_wrapper);
    sig_arch_settrapgate(0x0E, sig_arch_exception_page_wrapper);
    sig_arch_settrapgate(0x0F, sig_arch_exception_reserved_wrapper);
    sig_arch_settrapgate(0x10, sig_arch_exception_math_wrapper);
    sig_arch_settrapgate(0x11, sig_arch_exception_alignment_wrapper);
    sig_arch_settrapgate(0x12, sig_arch_exception_machine_wrapper);
    sig_arch_settrapgate(0x13, sig_arch_exception_sse_wrapper);
    sig_arch_settrapgate(0x14, sig_arch_exception_unknown14_wrapper);
    sig_arch_settrapgate(0x15, sig_arch_exception_unknown15_wrapper);
    sig_arch_settrapgate(0x16, sig_arch_exception_unknown16_wrapper);
    sig_arch_settrapgate(0x17, sig_arch_exception_unknown17_wrapper);
    sig_arch_settrapgate(0x18, sig_arch_exception_unknown18_wrapper);
    sig_arch_settrapgate(0x19, sig_arch_exception_unknown19_wrapper);
    sig_arch_settrapgate(0x1A, sig_arch_exception_unknown1a_wrapper);
    sig_arch_settrapgate(0x1B, sig_arch_exception_unknown1b_wrapper);
    sig_arch_settrapgate(0x1C, sig_arch_exception_unknown1c_wrapper);
    sig_arch_settrapgate(0x1D, sig_arch_exception_unknown1d_wrapper);
    sig_arch_settrapgate(0x1E, sig_arch_exception_unknown1e_wrapper);
    sig_arch_settrapgate(0x1F, sig_arch_exception_unknown1f_wrapper);
    
    sig_arch_setinterruptgate(0x20, sig_arch_irq0_wrapper);
    sig_arch_setinterruptgate(0x21, sig_arch_irq1_wrapper);
    sig_arch_setinterruptgate(0x22, sig_arch_irq2_wrapper);
    sig_arch_setinterruptgate(0x23, sig_arch_irq3_wrapper);
    sig_arch_setinterruptgate(0x24, sig_arch_irq4_wrapper);
    sig_arch_setinterruptgate(0x25, sig_arch_irq5_wrapper);
    sig_arch_setinterruptgate(0x26, sig_arch_irq6_wrapper);
    sig_arch_setinterruptgate(0x27, sig_arch_irq7_wrapper);
    sig_arch_setinterruptgate(0x28, sig_arch_irq8_wrapper);
    sig_arch_setinterruptgate(0x29, sig_arch_irq9_wrapper);
    sig_arch_setinterruptgate(0x2A, sig_arch_irq10_wrapper);
    sig_arch_setinterruptgate(0x2B, sig_arch_irq11_wrapper);
    sig_arch_setinterruptgate(0x2C, sig_arch_irq12_wrapper);
    sig_arch_setinterruptgate(0x2D, sig_arch_irq13_wrapper);
    sig_arch_setinterruptgate(0x2E, sig_arch_irq14_wrapper);
    sig_arch_setinterruptgate(0x2F, sig_arch_irq15_wrapper);

    sig_arch_settrapgate(0xC0, sig_arch_exception_unknown1f_wrapper);
}

void sig_arch_setinterruptgate(unsigned intr, void (*func)(void))
{
	sigIDT[intr].d1 = 0x00080000 + (((unsigned)(func)) & 0x0000FFFF);   //Segment 8
	sigIDT[intr].d2 = 0x00008E00 + (((unsigned)(func)) & 0xFFFF0000);   //Present / RPL 0 / 32 bits / Interrupt
}

void sig_arch_settrapgate(unsigned intr, void (*func)(void))
{
	sigIDT[intr].d1 = 0x00080000 + (((unsigned)(func)) & 0x0000FFFF);   //Segment 8
	sigIDT[intr].d2 = 0x00008F00 + (((unsigned)(func)) & 0xFFFF0000);   //Present / RPL 0 / 32 bits / Trap
}

/*************************************************************/

bool TEMP_sig_arch_monitorstatus[16] = {false};

void sig_arch_exception_divideerror(void)
{
    panic("EXCEPTION: DIVIDE ERROR (00)");
}

void sig_arch_exception_debug(void)
{
    panic("EXCEPTION: DEBUG (01)");
}

void sig_arch_exception_nmi(void)
{
    panic("EXCEPTION: NON-MASKABLE INTERRUPT (02)");
}

void sig_arch_exception_breakpoint(void)
{
    panic("EXCEPTION: BREAKPOINT (03)");
}

void sig_arch_exception_overflow(void)
{
    panic("EXCEPTION: OVERFLOW (04)");
}

void sig_arch_exception_bounds(void)
{
    panic("EXCEPTION: BOUND RANGE EXCEEDED (05)");
}

void sig_arch_exception_opcode(void)
{
    panic("EXCEPTION: INVALID/UNDEFINED OPCODE (06)");
}

void sig_arch_exception_device(void)
{
    panic("EXCEPTION: NO MATH COPROCESSOR (07)");
}

void sig_arch_exception_double(void)
{
    panic("EXCEPTION: DOUBLE FAULT (08)");
}

void sig_arch_exception_overrun(void)
{
    panic("EXCEPTION: COPROCESSOR SEGMENT OVERRUN (09)");
}

void sig_arch_exception_tss(void)
{
    panic("EXCEPTION: INVALID TSS (0A)");
}

void sig_arch_exception_segment(void)
{
    panic("EXCEPTION: SEGMENT NOT PRESENT (0B)");
}

void sig_arch_exception_stack(void)
{
    panic("EXCEPTION: STACK SEGMENT FAULT (0C)");
}

void sig_arch_exception_protection(void)
{
    panic("EXCEPTION: GENERAL PROTECTION (0D)");
}

void sig_arch_exception_page(void)
{
    panic("EXCEPTION: PAGE FAULT (0E)");
}

void sig_arch_exception_reserved(void)
{
    panic("EXCEPTION: RESERVED (0F)");
}

void sig_arch_exception_math(void)
{
    panic("EXCEPTION: MATH FAULT (10)");
}

void sig_arch_exception_alignment(void)
{
    panic("EXCEPTION: ALIGNMENT CHECK (11)");
}

void sig_arch_exception_machine(void)
{
    panic("EXCEPTION: MACHINE CHECK (12)");
}

void sig_arch_exception_sse(void)
{
    panic("EXCEPTION: SIMD FLOATING-POINT EXCEPTION (13)");
}

void sig_arch_exception_unknown14(void)
{
    panic("EXCEPTION: UNKNOWN (14)");
}

void sig_arch_exception_unknown15(void)
{
    panic("EXCEPTION: UNKNOWN (15)");
}

void sig_arch_exception_unknown16(void)
{
    panic("EXCEPTION: UNKNOWN (16)");
}

void sig_arch_exception_unknown17(void)
{
    panic("EXCEPTION: UNKNOWN (17)");
}

void sig_arch_exception_unknown18(void)
{
    panic("EXCEPTION: UNKNOWN (18)");
}

void sig_arch_exception_unknown19(void)
{
    panic("EXCEPTION: UNKNOWN (19)");
}

void sig_arch_exception_unknown1a(void)
{
    panic("EXCEPTION: UNKNOWN (1A)");
}

void sig_arch_exception_unknown1b(void)
{
    panic("EXCEPTION: UNKNOWN (1B)");
}

void sig_arch_exception_unknown1c(void)
{
    panic("EXCEPTION: UNKNOWN (1C)");
}

void sig_arch_exception_unknown1d(void)
{
    panic("EXCEPTION: UNKNOWN (1D)");
}

void sig_arch_exception_unknown1e(void)
{
    panic("EXCEPTION: UNKNOWN (1E)");
}

void sig_arch_exception_unknown1f(void)
{
    panic("EXCEPTION: UNKNOWN (1F)");
}

void TEMP_sig_arch_monitor(int irq)
{
    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (63 + irq));
    *v = irq >= 10 ? (irq - 10) + 'A' : irq + '0';
    v++;
    *v = TEMP_sig_arch_monitorstatus[irq] ? 0x10 : 0x17;
    TEMP_sig_arch_monitorstatus[irq] = !TEMP_sig_arch_monitorstatus[irq];
}

void sig_arch_irq0(void)
{
    TEMP_sig_arch_monitor(0);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));

    sched_schedule();
}

void sig_arch_irq1(void)
{
    unt32 key;
    
    TEMP_sig_arch_monitor(1);

    asm ("inb %%dx,%%al":"=a" (key):"d" (0x60));

    logHex("Scancode", key);

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq2(void)
{
    TEMP_sig_arch_monitor(2);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq3(void)
{
    TEMP_sig_arch_monitor(3);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq4(void)
{
    TEMP_sig_arch_monitor(4);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq5(void)
{
    TEMP_sig_arch_monitor(5);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq6(void)
{
    TEMP_sig_arch_monitor(6);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq7(void)
{
    TEMP_sig_arch_monitor(7);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq8(void)
{
    TEMP_sig_arch_monitor(8);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq9(void)
{
    TEMP_sig_arch_monitor(9);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq10(void)
{
    TEMP_sig_arch_monitor(10);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq11(void)
{
    TEMP_sig_arch_monitor(11);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq12(void)
{
    TEMP_sig_arch_monitor(12);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq13(void)
{
    TEMP_sig_arch_monitor(13);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq14(void)
{
    TEMP_sig_arch_monitor(14);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}

void sig_arch_irq15(void)
{
    TEMP_sig_arch_monitor(15);
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
}
