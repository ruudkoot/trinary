void discardable sysInit(void)
{
    asm ("outb %%al,%%dx"::"a" (0x26),"d" (0x43));     //MACRO!!!
    asm ("outb %%al,%%dx"::"a" (15),"d" (0x40));     //MACRO!!!
}
