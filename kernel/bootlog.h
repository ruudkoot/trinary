enum log {
	succes	= 0x0AFB,	/* Green Checkmark		*/
	fail	= 0x0458,	/* Red Cross			*/
	skip	= 0x0E2D,	/* Yellow Bar			*/
	abort	= 0x0441,	/* Red 'A'				*/
	retry	= 0x0452,	/* Red 'R'				*/
	ignore	= 0x0449,	/* Red 'I'				*/
	unknown	= 0x0E3F,	/* Yellow Questionmark	*/
};

void logStatus(unsigned short status);
void logItem(char* description);
void logSubItem(char* description, char* value);
void logMessage(char* message);
void logScroll(void);

void displayString(char* output, unsigned char color);

/*******************************/

void blItem(const char* item);
void logNote(char* description);