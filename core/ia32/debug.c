#include <debug.h>

#include <mem.h>
#include <string.h>

void panic(char* message)
{
	memset((char*)0xB8000, 0, 8000);
	char* b = "T\x02""H\x02""E\x02"" \x02""M\x02""A\x02""T\x02""R\x02""I\x02""X\x02"" \x02""H\x02""A\x02""S\x02"" \x02""Y\x02""O\x02""U\x02""\xDB\x82";
	memcpy((char*)0xB8000+160*12+60, b, strlen(b));
	
	_asm cli;
	_asm hlt;
}