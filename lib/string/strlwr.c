char* strlwr(char* s)
{
	while (*s++) if (*s >= 'A' && *s <= 'Z') *s += 'a' - 'A';
	return s;
}