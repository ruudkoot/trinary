int strncmp(const char* s, const char* t, unsigned n)
{
	while ((*s++ == *t++) && n--);
	return *s - *t;
}