char* strcpy(char* s, const char* t, unsigned n)
{
	while (*t && n--) *s++ = *t++;
	return s;
}