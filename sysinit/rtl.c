#include "rtl.h"

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