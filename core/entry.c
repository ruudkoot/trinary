void main(void);

void entry(void)
{
	main();

	_asm cli;
	_asm hlt;
}