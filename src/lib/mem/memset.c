void* memset(void* s, char i, unsigned n)
{
        void *start = s;

        while (n--) {
                *(char *)s = (char)i;
                s = (char *)s + 1;
        }

        return(start);
}
