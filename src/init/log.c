/******************************************************************************/
/* Boot Log                                                                   */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void logScroll(void);
void logItem(unsigned char* description);
void logStatus(unsigned);
void displayString(unsigned char* output, unsigned char color);

const unsigned logSuccess = 0;

void logScroll(void)
{
    int i;
    unsigned source, destination;
    
    for (i = 0; i < 22; i++)
    {
        source        = 0xB8000 + 160 * i + 488;
        destination    = 0xB8000 + 160 * i + 328;

        _memcpy((void*)destination, (void*)source, 148);
    }
}

void logItem(unsigned char* description)
{
    char output[75];
    strcpy(output, "[ ][.....................................................................]");
    strnpst(output + 4, description, 69);
    logScroll();
    displayString(output, 0x0F);
}

void logSubItem(unsigned char* property, unsigned char* value)
{
    char output[75];
    strcpy(output, "   [.....................................................................]");
    strnpst(output + 4, property, 66);
    strnpst(output + max(73 - strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logHex(unsigned char* property, unsigned number)
{
    char value[20];
    char output[75];

    _u32toa(number, value, 16);

    _strcpy(output, "   [.....................................................................]");
    _strnpst(output + 4, property, 66);
    _strnpst(output + _max(73 - _strlen(value), 4), value, 66);
    logScroll();
    displayString(output, 0x07);
}

void logDec(unsigned char* property, unsigned number)
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

void logBin(unsigned char* property, unsigned number)
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

void logMessage(unsigned char* message)
{
    char output[75];
    strcpy(output, "[........................................................................]");
    strnpst(output + 1, message, 72);
    logScroll();
    displayString(output, 0x02);
}

void logNote(unsigned char* note)
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

void displayString(unsigned char* output, unsigned char color)
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
