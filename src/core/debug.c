void panic(char* title);
void panicWrite(unsigned r, unsigned c, char* s);
void panicHalt(void);

void panic(char* title)
{
    unsigned char* v;
    unsigned i;

    //for (i = 1; i <= 24; i++)
    //{
        //v = (unsigned char*)(0xB8000 + 160 * i + 4);
        //memsetw(v, 0x0F00, 78);
    //}

    panicWrite(2, 41 - strlen(title) / 2, title);
    //panicWrite(23, 15, "SYSTEM HALTED! PRESS [RESET] TO REBOOT YOUR COMUTER.");

    panicHalt();
}

void panicWrite(unsigned r, unsigned c, char* s)
{
    unsigned char* v;
    v = (unsigned char*)(0xB8000 + 160 * r + 2 * c);
    //Write a special strcpy() for this!
    memcpybw(v, s, strlen(s));
}

void panicHalt(void)
{
    asm ("cli");
    asm ("hlt");
}
