void* memcpybw(void* s, void* t, unsigned n)
{
        void * ret = s;

        while (n--)
		{
                *(char *)s = *(char *)t;
                s = (char *)s + 2;
                t = (char *)t + 1;
        }

        return(ret);
}
