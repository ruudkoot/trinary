void logScroll(void);
void logItem(string description);
void logStatus(unsigned);
void displayString(char* output, unsigned char color);

const unsigned logSuccess = 0;

void logScroll(void)
{
    int i;
    unsigned source, destination;
    
    for (i = 2; i < 22; i++)
    {
        source        = 0xB8000 + 160 * i + 488;
        destination    = 0xB8000 + 160 * i + 328;

        memcpy((void*)destination, (void*)source, 148);
    }
}

void logItem(string description)
{
    char output[75];
    strcpy(output, "[ ][.....................................................................]");
    strnpst(output + 4, description, 69);
    logScroll();
    displayString(output, 0x0F);
}

void logSubItem(string property, string value)
{
    char output[75];
    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logHex(string property, unsigned number)
{
    char value[20];    
    char output[75];

    u32toa(number, value, 16);

    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logDec(string property, unsigned number)
{
    char value[20];    
    char output[75];

    u32toa(number, value, 10);

    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logBin(string property, unsigned number)
{
    char value[20];    
    char output[75];

    u32toa(number, value, 2);

    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logMessage(string message)
{
    char output[75];
    strcpy(output, "[........................................................................]");
    strnpst(output + 1, message, 72);
    logScroll();
    displayString(output, 0x02);
}

void logNote(string note)
{
    char output[75];
    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, note, 69);
    logScroll();
    displayString(output, 0x03);
}

void logStatus(unsigned status)
{
    unsigned short* tmpVideo = (unsigned short*)0xB8E6A;
    *tmpVideo = 0x0AFB;
}

void displayString(char* output, unsigned char color)
{
    char* m = (char*)0xB8E68;

    while (*output)
    {
        *m = *output;
        m++;
        *m = color;
        m++;
        output++;
    }
}
