void* memcpy(void* s, void* t, unsigned n)
{
	while (n)
	{
		(*(char*)s) = (*(char*)t);
		s = (char*)s + 1;
		t = (char*)t + 1;
		n--;
	}
	return s;
}
