unsigned strlen(const char* s)
{
	int i = 0;
	while (*s++) i++;
	return i;

	//char* t = s;
	//while (*s++);
	//return s - t;
}