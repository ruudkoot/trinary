#include "rtl.h"
#include "log.h"

void logStatus(unsigned int status)
{
	asm push ds;
	asm mov ax, 0xB800;
	asm mov ds, ax;
	asm mov ax, status;
	asm mov word [0x0E6A], ax;
	asm pop ds;
}

void logItem(const char* description)
{
	char* image = "[ ][.....................................................................]";
	stringPaste(image, description, 4, 66);
	logScroll();
	displayString(image, 0x0F);
}

void logSubItem(const char* description, const char* value)
{
	int length;
	char* image = "   [.....................................................................]";
	length = min(stringLength(value), 63);
	stringPaste(image, description, 4, 62 - length);
	stringPaste(image, value, 73 - length, 63 - length);
	logScroll();
	displayString(image, 0x07);
}

void logMessage(const char* message)
{
	char* image = "[                                                                        ]";
	stringPaste(image, message, 1, 72);
	logScroll();
	displayString(image, 0x03);
}

void logScroll(void)
{
	int i;
	unsigned source, destination;
	
	for (i = 0; i < 22; i++)
	{
		source		= 160 * i + 488;
		destination	= 160 * i + 328;

		asm push si;
		asm push di;
		asm mov si, source;
		asm mov di, destination;
		asm push ds;
		asm push es;
		asm mov ax, 0xB800;
		asm mov ds, ax;
		asm mov es, ax;
		asm mov cx, 74;
		asm rep movsw;
		asm pop es;
		asm pop ds;
		asm pop di;
		asm pop si;
	}
}

void displayString(const char* output, unsigned char color)
{
	asm push es;
	asm mov ax, 0xB800;
	asm mov es, ax;

	asm cld;
	asm mov si, output;
	asm mov di, 0x0E68;
	asm mov ah, color;

	LoopWriteMessage:
		asm lodsb;
		asm or al,al;
		asm jz DoneWriteMessage;
		asm stosw;
		asm jmp LoopWriteMessage;
	DoneWriteMessage:

	asm pop es;
}