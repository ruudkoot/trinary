char* strupr(char* s)
{
	char* c;
	while (*s++) if (*s >= 'a' && *s <= 'z') *s += 'A' - 'a';
	return c;
}