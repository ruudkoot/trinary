void* memset(void* s, char i, unsigned n)
{
	while (n)
	{
		*((char*)s) = i;
		n--;
	}
	return s;
}