int strcmp(const char* s, const char* t)
{
	while (*s++ == *t++);
	return *s - *t;
}