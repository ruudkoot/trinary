#include <mem.h>
#include <string.h>
#include <bootlog.h>


int stringLength(const char* source)
{
	int length = 0;
	while (*(source++)) length++;
	return length;
}

char* stringPaste(char* destination, const char* source, int start, int lenght)
{
	destination += start;

	while (*source && lenght)
	{
		*destination++ = *source++;
		lenght--;
	}

	return destination;
}

int min(int f, int g)
{
	return f < g ? f : g;
}

int max(int f, int g)
{
	return f > g ? f : g;
}

/*****************************************************************************/

void logStatus(unsigned short status)
{
	short* m = (short*)0xB8E6A;
	*m = status;
}

void logMessage(char* message)
{
	char output[80];
	displayString(message, 0x1F);
}

void logSubItem(char* description, char* value)
{
	logScroll();
	char output[80];
	strcpy(output, "   [.....................................................................]");
	strpst(output+4, description);
	strpst(output+73-strlen(value), value);
	displayString(output, 0x07);
}

void logNote(char* description)
{
	logScroll();
	char output[80];
	strcpy(output, "   [.....................................................................]");
	strpst(output+4, description);
	displayString(output, 0x03);
}

void logScroll(void)
{
	int i;
	unsigned source, destination;
	
	for (i = 0; i < 22; i++)
	{
		source		= 0xB8000 + 160 * i + 488;
		destination	= 0xB8000 + 160 * i + 328;

		memcpy((void*)destination, (void*)source, 148);
	}
}

void displayString(char* output, unsigned char color)
{
	char* m = (char*)0xB8E68;

	while (*output)
	{
		*m = *output;
		m++;
		*m = color;
		m++;
		output++;
	}
}

/******************************************************************/

void blItem(const char* item)
{
	char output[80];
	strcpy(output, "[ ][.....................................................................]");
	strpst(output + 4, item);
	displayString(output, 0x0F);
}