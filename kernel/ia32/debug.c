#include <debug.h>

#include <mem.h>
#include <string.h>

void panic(char* message)
{
	memset((char*)0xB8000, 0x31, 8000);
	//memcpy((char*)(0xB8720 + ((160 - strlen(message)) / 2)), message, strlen(message));

	_asm cli;
	_asm hlt;
}