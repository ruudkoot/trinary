void* memcpy(void* s, const void* t, unsigned n)
{
        void * ret = s;

        while (n--)
		{
                *(char *)s = *(char *)t;
                s = (char *)s + 1;
                t = (char *)t + 1;
        }

        return(ret);
}
