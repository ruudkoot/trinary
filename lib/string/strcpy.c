char* strcpy(char* s, const char* t)
{
	while (*t) *s++ = *t++;
	return s;
}