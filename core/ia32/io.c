unsigned char ioReadByte(unsigned a)
{
	unsigned short p = a;
	unsigned char v;

	_asm mov dx, p;
	_asm in al, dx;
	_asm mov v, al;
	
	return v;
}

unsigned short ioReadWord(unsigned a)
{
	unsigned short p = a;
	unsigned short v;

	_asm mov dx, p;
	_asm in ax, dx;
	_asm mov v, ax;
	
	return v;
}

unsigned ioReadDword(unsigned a)
{
	unsigned short p = a;
	unsigned v;

	_asm mov dx, p;
	_asm in eax, dx;
	_asm mov v, eax;
	
	return v;
}