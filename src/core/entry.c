void entry(void)
{
	main();
    asm ("cli");
    asm ("hlt");
}