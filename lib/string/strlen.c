unsigned strlen(const char* s)
{
	const char* c = s;
	while (*c++);
	return (unsigned)(c - s - 1);
}