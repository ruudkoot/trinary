
void* memsetw(void* s, short i, unsigned n)
{
        void *start = s;

        while (n--) {
                *(short *)s = (short)i;
                s = (short *)s + 1;
        }

        return(start);
}

