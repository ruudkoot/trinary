#include <bootlog.h>
#include <debug.h>
#include <heap.h>
#include <mm.h>
#include <cpu.h>

void swab (
        char *src,
        char *dest,
        int nbytes
        );

void doInt(void);
void setInt(unsigned intr, void (*func)(void));

void isr(void);
void irq0(void);
void irq1(void);
void irq2(void);
void irq3(void);
void irq4(void);
void irq5(void);
void irq6(void);
void irq7(void);
void irq8(void);
void irq9(void);
void irqA(void);
void irqB(void);
void irqC(void);
void irqD(void);
void irqE(void);
void irqF(void);



struct IDT_t
{
	unsigned d1;
	unsigned d2;
};

IDT_t IDT[256];
unsigned IRQMon[16];

//This is the entry point of the Trinary Operating System Kernel. Be assume to
//be located at physical and logical memory location 0x00000000. We should be
//in 32-bit Protected Mode. In the current version paging is disabled. Our
//segments (CS, SS, DS, ES, FS and GS) should have a base address of 0 and a
//limit of 4GB. The code has to be read-only, while the other segments have to
//be read-write.
void _cdecl main(void)
{

	unsigned char* a;
	a = (unsigned char*)0xB8E6A;
	*a = 0xFB;
	a++;
	*a = 0x0A;

	//heapInit(2*1024*1024, 0);

	logItem("Initializing Memory Management");
	mmInit();
	
	logItem("Identifing CPU");
	logStatus(success);
	cpuInit();

	logItem("Initializing Interrupt Management");
	doInt();

	_asm sti;

		_asm mov dx, 0x1F7;
		_asm mov al, 0xEC;
		_asm out dx, al;

/*	_asm mov dx, 0x60;
	_asm in al, dx;
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;
	_asm sti;*/
	logStatus(success);

	//Shutdown the CPU
	
	logMessage("Press [RESET] to reboot ;-)");

	_asm sti;
	for (;;) _asm hlt;


	//logMessage("WHOO HOO!");

	_asm cli;
	_asm hlt;

}

void doInt(void)
{
	unsigned char pointer[6];
	unsigned* a;

	pointer[0] = 0x00;
	pointer[1] = 0x08;
	a = (unsigned*)(pointer+2);
	*a = (unsigned)(IDT);
	
	for (int j = 0; j < 16; j++)
	{
		IRQMon[j] = -1;
	}

	for (int i = 0; i < 256; i++)
	{
		IDT[i].d1 = 0x00080000 + (((unsigned)(isr)) & 0x0000FFFF);
		IDT[i].d2 = 0x00008E00 + (((unsigned)(isr)) & 0xFFFF0000);
	}

	setInt(0x08, irq0);
	setInt(0x09, irq1);
	setInt(0x0A, irq2);
	setInt(0x0B, irq3);
	setInt(0x0C, irq4);
	setInt(0x0D, irq5);
	setInt(0x0E, irq6);
	setInt(0x0F, irq7);

	setInt(0x70, irq8);
	setInt(0x71, irq9);
	setInt(0x72, irqA);
	setInt(0x73, irqB);
	setInt(0x74, irqC);
	setInt(0x75, irqD);
	setInt(0x76, irqE);
	setInt(0x77, irqF);


	_asm mov ebx, 0x100;
	_asm sidt [ebx];
	_asm lidt pointer;
	_asm mov ebx, 0x110;
	_asm sidt [ebx];

}

void setInt(unsigned intr, void (*func)(void))
{
	IDT[intr].d1 = 0x00080000 + (((unsigned)(func)) & 0x0000FFFF);
	IDT[intr].d2 = 0x00008E00 + (((unsigned)(func)) & 0xFFFF0000);
}

void _declspec(naked) isr(void)
{
/*	
	_asm _emit 0x60;
	//_asm pusha;
	_asm mov ebx, 0xB8000;
	
		_asm mov dx, 0x60;
	_asm in al, dx;
	
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm inc byte ptr [ebx];
	_asm _emit 0x61;
	//_asm popa;
	_asm _emit 0xCF;
	//_asm iret;
*/
	_asm pushad;
	
	logMessage("OH FUCK!!!");
	
	_asm mov al, 0x20;
	_asm mov dx, 0x20;
	_asm out dx, al;
	
	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq0(void)
{
	_asm pushad;

	IRQMon[0]++;
	if (IRQMon[0] >= 10) IRQMon[0] = 0;
	
	_asm mov ebx, 0xB807C;
	_asm mov eax, IRQMon[0];
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq1(void)
{
	_asm pushad;

	unsigned a;
	
	IRQMon[1]++;
	if (IRQMon[1] >= 10) IRQMon[1] = 0;

	a = IRQMon[1];
	
	_asm mov ebx, 0xB807E;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;
	
	_asm in al, 0x60;
	
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq2(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[2]++;
	if (IRQMon[2] >= 10) IRQMon[2] = 0;
	
	a = IRQMon[2];
	
	_asm mov ebx, 0xB8080;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq3(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[3]++;
	if (IRQMon[3] >= 10) IRQMon[3] = 0;
	
	a = IRQMon[3];
	
	_asm mov ebx, 0xB8082;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq4(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[4]++;
	if (IRQMon[4] >= 10) IRQMon[4] = 0;
	
	a = IRQMon[4];
	
	_asm mov ebx, 0xB8084;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq5(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[5]++;
	if (IRQMon[5] >= 10) IRQMon[5] = 0;
	
	a = IRQMon[5];
	
	_asm mov ebx, 0xB8086;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq6(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[6]++;
	if (IRQMon[6] >= 10) IRQMon[6] = 0;
	
	a = IRQMon[6];
	
	_asm mov ebx, 0xB8088;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq7(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[7]++;
	if (IRQMon[7] >= 10) IRQMon[7] = 0;
	
	a = IRQMon[7];
	
	_asm mov ebx, 0xB808A;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq8(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[8]++;
	if (IRQMon[8] >= 10) IRQMon[8] = 0;
	
	a = IRQMon[8];
	
	_asm mov ebx, 0xB808C;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irq9(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[9]++;
	if (IRQMon[9] >= 10) IRQMon[9] = 0;
	
	a = IRQMon[9];
	
	_asm mov ebx, 0xB808E;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irqA(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[10]++;
	if (IRQMon[10] >= 10) IRQMon[10] = 0;
	
	a = IRQMon[10];
	
	_asm mov ebx, 0xB8090;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irqB(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[11]++;
	if (IRQMon[11] >= 10) IRQMon[11] = 0;
	
	a = IRQMon[11];
	
	_asm mov ebx, 0xB8092;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irqC(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[12]++;
	if (IRQMon[12] >= 10) IRQMon[12] = 0;
	
	a = IRQMon[12];
	
	_asm mov ebx, 0xB8094;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void _declspec(naked) irqD(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[13]++;
	if (IRQMon[13] >= 10) IRQMon[13] = 0;
	
	a = IRQMon[13];
	
	_asm mov ebx, 0xB8096;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;
	
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void irqE(void)
{
	_asm pushad;

	unsigned a;
	unsigned short buf[256];
	unsigned i;

	IRQMon[14]++;
	if (IRQMon[14] >= 10) IRQMon[14] = 0;
	
	a = IRQMon[14];
	
	_asm mov ebx, 0xB8098;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;	

	_asm mov dx, 0x1F7;
	_asm in al, dx;

	for (i = 0; i < 256; i++)
	{
		_asm mov dx, 0x1F0;
		_asm in ax, dx;
		_asm mov a, eax;
		buf[i] = a;
		_asm mov dx, 0x1F7;
		_asm in al, dx;
	}

	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;
	
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	swab((char*)buf, (char*)buf, 512);
	
	logMessage(((char*)buf)+27*2);

	_asm popad;
	
	for (;;);
	
	_asm iretd;
}

void _declspec(naked) irqF(void)
{
	_asm pushad;

	unsigned a;

	IRQMon[15]++;
	if (IRQMon[15] >= 10) IRQMon[15] = 0;
	
	a = IRQMon[15];
	
	_asm mov ebx, 0xB809A;
	_asm mov eax, a;
	_asm add al, '0';
	_asm mov byte ptr [ebx], al;
	
	_asm mov dx, 0x177;
	_asm in al, dx;
	
	_asm mov dx, 0xA0;
	_asm mov al, 0x20;
	_asm out dx, al;
	
	_asm mov dx, 0x20;
	_asm mov al, 0x20;
	_asm out dx, al;

	_asm popad;
	_asm iretd;
}

void swab (
        char *src,
        char *dest,
        int nbytes
        )
{
        char b1, b2;

        while (nbytes > 1) {
                b1 = *src++;
                b2 = *src++;
                *dest++ = b2;
                *dest++ = b1;
                nbytes -= 2;
        }
}

