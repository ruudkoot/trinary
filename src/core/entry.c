extern void cmain(void);

void entry(void)
{
    cmain();
    asm ("cli");
    asm ("hlt");
}
