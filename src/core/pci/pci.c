/******************************************************************************/
/* PCI Bus Server                                                             */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "arch/ia32.c"

void pci_probe(void)
{
   unsigned data;
   unsigned b, d, f;
   char z[20], w[20];
   unsigned last;

   data = 0x89ABCDEF;

   logItem("Probing PCI Bus");

   last = 0xFFFFFFFF;       /* !!! */
   
   for (b = 0; b < 256; b++)
   {
       for (d = 0; d < 32; d++)
       {
           for (f = 0; f < 8; f++)
           {
                data = pci_readConfig(b, d, f, 0);

                if (data != last && data != 0xFFFFFFFF)
                {
                    last = data;
                    itoa(data, z, 16);
                    itoa(b * 256 * 256 * 256 + d * 256 * 256 + f * 256, w, 16);
                    logSubItem(w, z);
                }
           }
       }
   }
}
