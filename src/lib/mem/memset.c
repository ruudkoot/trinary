void* memset(void* s, int i, unsigned n)
{
        void *start = s;

        while (n--) {
                *(char *)s = (char)i;
                s = (char *)s + 1;
        }

        return(start);
}
