void discardable sysInit(void)
{
    asm ("outb %%al,%%dx"::"a" (0x16),"d" (0x43));     //MACRO!!!
    asm ("outb %%al,%%dx"::"a" (119),"d" (0x40));     //MACRO!!!
}
