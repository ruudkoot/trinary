/******************************************************************************/
/* Signal Handling                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

typedef struct idt_t
{
    unsigned d1;
    unsigned d2;
} idt_t;

extern void sigWrapper(void);
void Chandler(void);
void isr(void);
void timer(void);


bool d = true;

idt_t sigIDT[256];

void (*sigTable[256])(void);
void sigSetInterruptGate(unsigned intr, void (*func)(void));

bool sigIRQ[16] = {false};

void sigIRQ0(void);
void sigIRQ1(void);
void sigIRQ2(void);
void sigIRQ3(void);
void sigIRQ4(void);
void sigIRQ5(void);
void sigIRQ6(void);
void sigIRQ7(void);
void sigIRQ8(void);
void sigIRQ9(void);
void sigIRQA(void);
void sigIRQB(void);
void sigIRQC(void);
void sigIRQD(void);
void sigIRQE(void);
void sigIRQF(void);


/*******************************/

void sigExceptionDivide(void);
void sigExceptionDebug(void);
void sigExceptionNMI(void);
void sigExceptionBreakpoint(void);
void sigExceptionOverflow(void);
void sigExceptionBounds(void);
void sigExceptionOpcode(void);
void sigExceptionDevice(void);
void sigExceptionDouble(void);
void sigExceptionOverrun(void);
void sigExceptionTSS(void);
void sigExceptionSegment(void);
void sigExceptionStack(void);
void sigExceptionProtection(void);
void sigExceptionPage(void);
void sigExceptionReserved(void);
void sigExceptionMath(void);
void sigExceptionAlignment(void);
void sigExceptionMachine(void);
void sigExceptionSSE(void);
void sigExceptionUnknown14(void);
void sigExceptionUnknown15(void);
void sigExceptionUnknown16(void);
void sigExceptionUnknown17(void);
void sigExceptionUnknown18(void);
void sigExceptionUnknown19(void);
void sigExceptionUnknown1A(void);
void sigExceptionUnknown1B(void);
void sigExceptionUnknown1C(void);
void sigExceptionUnknown1D(void);
void sigExceptionUnknown1E(void);
void sigExceptionUnknown1F(void);

/********************************/

void discardable sigInit(void)
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
		sigIDT[i].d1 = 0x00080000 + (((unsigned)(Chandler)) & 0x0000FFFF);
		sigIDT[i].d2 = 0x00008E00 + (((unsigned)(Chandler)) & 0xFFFF0000);
    }

    sigSetInterruptGate(0x00, sigExceptionDivide);
    sigSetInterruptGate(0x01, sigExceptionDebug);
    sigSetInterruptGate(0x02, sigExceptionNMI);
    sigSetInterruptGate(0x03, sigExceptionBreakpoint);
    sigSetInterruptGate(0x04, sigExceptionOverflow);
    sigSetInterruptGate(0x05, sigExceptionBounds);
    sigSetInterruptGate(0x06, sigExceptionOpcode);
    sigSetInterruptGate(0x07, sigExceptionDevice);
    sigSetInterruptGate(0x08, sigExceptionDouble);
    sigSetInterruptGate(0x09, sigExceptionOverrun);
    sigSetInterruptGate(0x0A, sigExceptionTSS);
    sigSetInterruptGate(0x0B, sigExceptionSegment);
    sigSetInterruptGate(0x0C, sigExceptionStack);
    sigSetInterruptGate(0x0D, sigExceptionProtection);
    sigSetInterruptGate(0x0E, sigExceptionPage);
    sigSetInterruptGate(0x0F, sigExceptionReserved);
    sigSetInterruptGate(0x10, sigExceptionMath);
    sigSetInterruptGate(0x11, sigExceptionAlignment);
    sigSetInterruptGate(0x12, sigExceptionMachine);
    sigSetInterruptGate(0x13, sigExceptionSSE);
    sigSetInterruptGate(0x14, sigExceptionUnknown14);
    sigSetInterruptGate(0x15, sigExceptionUnknown15);
    sigSetInterruptGate(0x16, sigExceptionUnknown16);
    sigSetInterruptGate(0x17, sigExceptionUnknown17);
    sigSetInterruptGate(0x18, sigExceptionUnknown18);
    sigSetInterruptGate(0x19, sigExceptionUnknown19);
    sigSetInterruptGate(0x1A, sigExceptionUnknown1A);
    sigSetInterruptGate(0x1B, sigExceptionUnknown1B);
    sigSetInterruptGate(0x1C, sigExceptionUnknown1C);
    sigSetInterruptGate(0x1D, sigExceptionUnknown1D);
    sigSetInterruptGate(0x1E, sigExceptionUnknown1E);
    sigSetInterruptGate(0x1F, sigExceptionUnknown1F);
    
    //sigSetInterruptGate(0x20, timer);
    sigSetInterruptGate(0x20, sigWrapper);
    //sigSetInterruptGate(0x20, sigIRQ0);
    sigSetInterruptGate(0x21, sigIRQ1);
    sigSetInterruptGate(0x22, sigIRQ2);
    sigSetInterruptGate(0x23, sigIRQ3);
    sigSetInterruptGate(0x24, sigIRQ4);
    sigSetInterruptGate(0x25, sigIRQ5);
    sigSetInterruptGate(0x26, sigIRQ6);
    sigSetInterruptGate(0x27, sigIRQ7);
    sigSetInterruptGate(0x28, sigIRQ8);
    sigSetInterruptGate(0x29, sigIRQ9);
    sigSetInterruptGate(0x2A, sigIRQA);
    sigSetInterruptGate(0x2B, sigIRQB);
    sigSetInterruptGate(0x2C, sigIRQC);
    sigSetInterruptGate(0x2D, sigIRQD);
    sigSetInterruptGate(0x2E, sigIRQE);
    sigSetInterruptGate(0x2F, sigIRQF);

    return;
}

/*************************************************************/

void sigSetInterruptGate(unsigned intr, void (*func)(void))
{
	sigIDT[intr].d1 = 0x00080000 + (((unsigned)(func)) & 0x0000FFFF);   //Segment 8
	sigIDT[intr].d2 = 0x00008E00 + (((unsigned)(func)) & 0xFFFF0000);   //Present / RPL 0 / 32 bits / Interrupt
}

void sigSetTrapGate(unsigned intr, void (*func)(void))
{
	sigIDT[intr].d1 = 0x00080000 + (((unsigned)(func)) & 0x0000FFFF);   //Segment 8
	sigIDT[intr].d2 = 0x00008F00 + (((unsigned)(func)) & 0xFFFF0000);   //Present / RPL 0 / 32 bits / Trap
}

void isr(void)
{
    displayString("isr()", 0x07);
}

void timer(void)
{
    asm ("pusha");
    if (d == true)
    {
        displayString("timer tick", 0x03);
        d = false;
    }
    else
    {
        displayString("tomer tock", 0x03);
        d = true;
    }
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));     //MACRO!!!
    asm ("popa");
    asm ("iret");
}

void Chandler(void)
{
    asm ("pusha");
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    asm ("popa");
    asm ("iret");
}

void sigIRQ0(void)
{
    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 16));
    *v = '0';
    v++;
    *v = sigIRQ[0] ? 0x10 : 0x17;
    sigIRQ[0] = !sigIRQ[0];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
}

void sigIRQ1(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 15));
    *v = '1';
    v++;
    *v = sigIRQ[1] ? 0x10 : 0x17;
    sigIRQ[1] = !sigIRQ[1];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ2(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 14));
    *v = '2';
    v++;
    *v = sigIRQ[2] ? 0x10 : 0x17;
    sigIRQ[2] = !sigIRQ[2];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ3(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 13));
    *v = '3';
    v++;
    *v = sigIRQ[3] ? 0x10 : 0x17;
    sigIRQ[3] = !sigIRQ[3];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ4(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 12));
    *v = '4';
    v++;
    *v = sigIRQ[4] ? 0x10 : 0x17;
    sigIRQ[4] = !sigIRQ[4];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ5(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 11));
    *v = '5';
    v++;
    *v = sigIRQ[5] ? 0x10 : 0x17;
    sigIRQ[5] = !sigIRQ[5];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ6(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 10));
    *v = '6';
    v++;
    *v = sigIRQ[6] ? 0x10 : 0x17;
    sigIRQ[6] = !sigIRQ[6];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ7(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 9));
    *v = '7';
    v++;
    *v = sigIRQ[7] ? 0x10 : 0x17;
    sigIRQ[7] = !sigIRQ[7];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ8(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 8));
    *v = '8';
    v++;
    *v = sigIRQ[8] ? 0x10 : 0x17;
    sigIRQ[8] = !sigIRQ[8];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQ9(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 7));
    *v = '9';
    v++;
    *v = sigIRQ[9] ? 0x10 : 0x17;
    sigIRQ[9] = !sigIRQ[9];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQA(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 6));
    *v = 'A';
    v++;
    *v = sigIRQ[10] ? 0x10 : 0x17;
    sigIRQ[10] = !sigIRQ[10];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQB(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 5));
    *v = 'B';
    v++;
    *v = sigIRQ[11] ? 0x10 : 0x17;
    sigIRQ[11] = !sigIRQ[11];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQC(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 4));
    *v = 'C';
    v++;
    *v = sigIRQ[12] ? 0x10 : 0x17;
    sigIRQ[12] = !sigIRQ[12];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQD(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 3));
    *v = 'D';
    v++;
    *v = sigIRQ[13] ? 0x10 : 0x17;
    sigIRQ[13] = !sigIRQ[13];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQE(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 2));
    *v = 'E';
    v++;
    *v = sigIRQ[14] ? 0x10 : 0x17;
    sigIRQ[14] = !sigIRQ[14];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}
void sigIRQF(void)
{
    

    unsigned char* v = (unsigned char*)(0xB8000 + 2 * (79 - 1));
    *v = 'F';
    v++;
    *v = sigIRQ[15] ? 0x10 : 0x17;
    sigIRQ[15] = !sigIRQ[15];

    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0xA0));
    asm ("outb %%al,%%dx"::"a" (0x20),"d" (0x20));
    
    asm ("iret");
}

/********************************************/

void sigExceptionDivide(void)
{
    panic("EXCEPTION: DIVIDE ERROR (00)");
}

void sigExceptionDebug(void)
{
    panic("EXCEPTION: DEBUG (01)");
}

void sigExceptionNMI(void)
{
    panic("EXCEPTION: NON-MASKABLE INTERRUPT (02)");
}

void sigExceptionBreakpoint(void)
{
    panic("EXCEPTION: BREAKPOINT (03)");
}

void sigExceptionOverflow(void)
{
    panic("EXCEPTION: OVERFLOW (04)");
}

void sigExceptionBounds(void)
{
    panic("EXCEPTION: BOUND RANGE EXCEEDED (05)");
}

void sigExceptionOpcode(void)
{
    panic("EXCEPTION: INVALID/UNDEFINED OPCODE (06)");
}

void sigExceptionDevice(void)
{
    panic("EXCEPTION: NO MATH COPROCESSOR (07)");
}

void sigExceptionDouble(void)
{
    panic("EXCEPTION: DOUBLE FAULT (08)");
}

void sigExceptionOverrun(void)
{
    panic("EXCEPTION: COPROCESSOR SEGMENT OVERRUN (09)");
}

void sigExceptionTSS(void)
{
    panic("EXCEPTION: INVALID TSS (0A)");
}

void sigExceptionSegment(void)
{
    panic("EXCEPTION: SEGMENT NOT PRESENT (0B)");
}

void sigExceptionStack(void)
{
    panic("EXCEPTION: STACK SEGMENT FAULT (0C)");
}

void sigExceptionProtection(void)
{
    panic("EXCEPTION: GENERAL PROTECTION (0D)");
}

void sigExceptionPage(void)
{
    panic("EXCEPTION: PAGE FAULT (0E)");
}

void sigExceptionReserved(void)
{
    panic("EXCEPTION: RESERVED (0F)");
}

void sigExceptionMath(void)
{
    panic("EXCEPTION: MATH FAULT (10)");
}

void sigExceptionAlignment(void)
{
    panic("EXCEPTION: ALIGNMENT CHECK (11)");
}

void sigExceptionMachine(void)
{
    panic("EXCEPTION: MACHINE CHECK (12)");
}

void sigExceptionSSE(void)
{
    panic("EXCEPTION: SIMD FLOATING-POINT EXCEPTION (13)");
}

void sigExceptionUnknown14(void)
{
    panic("EXCEPTION: UNKNOWN (14)");
}

void sigExceptionUnknown15(void)
{
    panic("EXCEPTION: UNKNOWN (15)");
}

void sigExceptionUnknown16(void)
{
    panic("EXCEPTION: UNKNOWN (16)");
}

void sigExceptionUnknown17(void)
{
    panic("EXCEPTION: UNKNOWN (17)");
}

void sigExceptionUnknown18(void)
{
    panic("EXCEPTION: UNKNOWN (18)");
}

void sigExceptionUnknown19(void)
{
    panic("EXCEPTION: UNKNOWN (19)");
}

void sigExceptionUnknown1A(void)
{
    panic("EXCEPTION: UNKNOWN (1A)");
}

void sigExceptionUnknown1B(void)
{
    panic("EXCEPTION: UNKNOWN (1B)");
}

void sigExceptionUnknown1C(void)
{
    panic("EXCEPTION: UNKNOWN (1C)");
}

void sigExceptionUnknown1D(void)
{
    panic("EXCEPTION: UNKNOWN (1D)");
}

void sigExceptionUnknown1E(void)
{
    panic("EXCEPTION: UNKNOWN (1E)");
}

void sigExceptionUnknown1F(void)
{
    panic("EXCEPTION: UNKNOWN (1F)");
}
