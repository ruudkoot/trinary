enum log {
	succes	= 0x0AFB,	/* Green Checkmark		*/
	fail	= 0x0458,	/* Red Cross			*/
	skip	= 0x0E2D,	/* Yellow Bar			*/
	abort	= 0x0441,	/* Red 'A'				*/
	retry	= 0x0452,	/* Red 'R'				*/
	ignore	= 0x0449,	/* Red 'I'				*/
	unknown	= 0x0E3F,	/* Yellow Questionmark	*/
};

void logStatus(unsigned int status);
void logItem(const char* description);
void logSubItem(const char* description, const char* value);
void logMessage(const char* message);
void logScroll(void);

void displayString(const char* output, unsigned char color);