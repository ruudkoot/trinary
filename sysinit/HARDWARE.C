#include "hardware.h"

indexstring processorNames[] =
{
	{0x0000, "Intel i8088"},
	{0x0001, "Intel i8086"},
	{0x0010, "Intel i80C88"},
	{0x0011, "Intel i80C86"},
	{0x0100, "NEC V20"},
	{0x0101, "NEC V30"},
	{0x0110, "NEC V25"},
	{0x0111, "NEC V35"},
	{0x0120, "NEC V25 Software Guard"},
	{0x0121, "NEC V35 Software Guard"},
	{0x0130, "NEC V40"},
	{0x0131, "NEC V50"},
	{0x1000, "Intel i80188"},
	{0x1001, "Intel i80186"},
	{0x1100, "NEC V25 Plus"},
	{0x1101, "NEC V35 Plus"},
	{0x2000, "Intel i286"},
	{0x3000, "Intel i386"},
	{0x4000, "Intel i486"},
	{0x0FFF, "Unknown 8086"},
	{0x1FFF, "Unknown 80186"},
	{0x2FFF, "Unknown 286"},
	{0x3FFF, "Unknown 386"},
	{0x4FFF, "Unknown 486"},
	{0x5FFF, "Unknown 586"},
	{0x6FFF, "Unknown 686"},
	{0xFFFF, "Unknown CPU"}
};

indexstring xprocessorNames[] =
{
	{0x0000, "Intel i8087"},
	{0x2002, "Intel i80287 / AMD Am80287 / Cyrix Cx287"},
	{0x3001, "Intel i80187"},
	{0x3002, "Intel i80287XL"},
	{0x3003, "Intel i80387 / Intel i80387SX"},
	{0x3013, "Intel i80387DX / Intel i80387SL"},
	{0x3102, "Cyrix FasMath Cx82S87"},
	{0x3112, "Cyrix FasMath Cx82S87+"},
	{0x3202, "IIT IIT-2C87"},
	{0x0FFF, "Unknown 8087"},
	{0x2FFF, "Unknown 80287"},
	{0x3FFF, "Unknown 80387"},
	{0xFFFF, "No FPU Installed"},
	{0x1234, "A serious error occured!"}
};

int identifyCPU(void)
{
	asm push sp;
	asm pop ax;
	asm cmp ax, sp;
	asm je test286;

	return identifyCPU0();

	test286:
		asm pushf;
		asm pop ax;
		asm or ax, 0x3000;
		asm push ax;
		asm popf;
		asm pushf;
		asm pop ax;
		asm test ax, 0x3000;
		asm jnz test386;

		return identifyCPU2();

	test386:
		return i386;
}

//These functions are designed to be used as 16-bit code, because they will be used before entering
//Protected Mode.

//Algorithm based on ideas of Grzegorz Mazur
//
//8-bit and 16-bit processors can be identified by their Prefetch Queue Size. It's 4 bytes for 8-bit
//CPUs and 6 bytes for 16-bit CPUs.
//
//The 80186/80188 and higher can be differentiated from the 8086/8088/V20/V30 by the change of the SHL
//instruction, which is documented in The IA-32 Inter Architecture Software Developer's Manual. Cl is
//masked with 0x1F on the 80186/80188. If you shift a non zero value in AX 32 bits, the contents of AX
//will not change (It will be shifted (0x20 & 0x1F) = 0 bits). It will on the 8086/8088/V20/V30 (It
//will be shifted 32 bits, moving the value outside register, resulting in a value of 0). I think this
//is a very nice methode.
//
//The 8086/8086 can then be differentiated by the V20/30 by using the PUSHA instruction. On the V20/30
//it work normaly, but on the 8086/8088 it functions as a 2 byte NOP. If SP has changed the function
//was executed and the CPU is a V20/V30. I really would like to see a better algorithm. One could also
//use the AAD instruction with a different second byte, which the NEC ignores.
//
//The 8086/8088 can be differentiated from the 80C86/80C88 by the fact that the original 8086/8088
//loses multiple prefixes during an interrupt. THE DETECTION OF THIS SUCKS! If we do a REP ES: MOVS the
//REP will be 'lost' during an interrupt. CX will be non-zero in that case. We have to make sure an
//interrupt occures however, which can take a looong time (0.05s). I believe the original 8086/8088
// supported the POP CS (0Fh) instruction, while the 80C86/80C88 doesn't. (Note to me: Search Google)
int identifyCPU0(void)
{
/*	int prefetchQueueSize = 0;
	
	asm mov ax, 0;
	asm mov byte [CodePointer], 0x90;
	asm nop;
	asm nop;
	asm nop;
	asm nop;
	asm CodePointer:
	asm inc ax;
	asm mov PrefetchqueueSize, ax;

	//Differentiate between the 8086/8088/V20/V30 and the 80186/80188
	asm mov ax, 1;			//This is just a random no-zero value we're going to shift.
	asm mov cl, 32;			//Loop 32 times, that is on a 8086/8088/V20/30
	asm shl ax, cl;			//Do the shift
	asm cmp ax, 0;			//According the the IA32SDM the flags aren't affected if we shifted 0
	asm jz DetectedModel0;	//If the awnser was 0 it was a 8086/8088/V20/V30
	asm mov Main8086Class, 2;	//It's an 80186/80188
	asm jmp Finished;

	//Differentiate between the 8086/8088 and the V20/V30
	asm DetectedModel0:
	asm mov ax, sp;		//Save SP so we can compare it later
	asm pusha;			//PUSHA will work on the V20/V30, but wil NOP on an 8086/8088
	asm nop;				//The 8086/8088 will ignore this byte, so make sure it doesn't do anything
	asm cmp ax, sp;		//Compare the new SP with the old SP
	asm jz Detected8086;	//If they are the same it's an 8086/8088
	asm popa;				//Recover the stack
	asm mov Main8086Class, 3;
	asm jmp Finished;

	//Differentiate between the 8086/8088 and the 80C86/80C88
	asm Detected8086:
	asm mov cx, 4096;
	asm TestLoop:
	asm mov ax, cx;
	asm lea si, TestBuffer;
	asm lea di, TestBuffer;
	asm mov cx, 4096;
	asm rep es movsb;	/*********** DOesn't work in inline assembler **********************/
/*	asm cmp cx, 0;
	asm jnz DetectedOriginal8086;	//If CX != 0 the REP was 'lost' to it's and original 8086/8088
	asm mov cx, ax;
	asm loop TestLoop;
	asm mov Main8086Class, 1;		//The REP wasn't lost after quite a while so assume a 80C86/80C88
	asm jmp Finished;

	asm DetectedOriginal8086:
	asm mov Main8086Class, 0;
	asm jmp Finished;

	asm Finished:*/
	return i8086;
}

int identifyCPU2(void)
{
	return i286;
}

unsigned identifyFPU(void)
{
	unsigned scratch = 0x55AA;

	asm	{
		fninit;
		fnstsw scratch;
		cmp byte ptr scratch, 0;
		jne fpuNone;

		fnstcw scratch;
		mov ax, scratch;
		and ax, 0x0103;
		cmp ax, 0x0003;
		jne fpuNone;

		and scratch, 0xFF7F;
		fldcw scratch;
		fdisi;
		fstcw scratch;
		test scratch, 0x0080;
		jnz fpu8087;

		finit;
		fld1;
		fldz;
		fdiv;
		fld st;
		fcompp;
		fstsw scratch;
		mov ax, scratch;
		sahf;
		je fpu287;
		jmp fpu387;
	}

	fpuNone:
		return 0xFFFF;
	fpu8087:
		return 0x0000;
	fpu287:
		return 0x2002;
	fpu387:
		return 0x3003;
}



/*void switchA20(void)
{
	r:
		asm jmp kx1;
	kx1:
		asm in al,0x60;
	kbd:
		asm jmp kx2;
	kx2:
		asm in al,0x64;
		asm test al,1;
		asm jnz kbdw0;
		asm test al,2;
		asm jnz kbd;
		asm ret;

	a20chk:
		asm call near ptr r;
		asm mov al,0xD1;
		asm out 0x64,al;
		asm call kbd;
		asm mov al,0xDF;
		asm out 0x60,al;
		asm call kbd;

	kbdw0:
		asm jmp short $+2;
		asm in al,0x60;
}

void keyboardWait(void)
{

} */