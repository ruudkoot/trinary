/******************************************************************************/
/* Symetric Multi-Processing support for the IA-32 Architecture               */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* THE smp_arch_* CODE CONTAINS SOME SERIOUS BUGS, ALTHOUGH MOST SYSTEMS ARE  */
/* NOT AFFECTED:                                                              */
/*     - POINTERS IN THE MPFPS COULD POINT TO MEMORY ABOVE THE FIRST (FOUR)   */
/*       MEGABYTES OF MEMORY, WHICH IS NOT MAPPED IN TO THE ADRESS SPACE!     */
/*                                                                            */
/* WE CAN INCREASE CHECKSUMMING SPEED BY USING 32-BIT STORES THAT ARE MODDED  */
/*                                                                            */
/* REMEMBER THE BSB (IN smp_arch_bspapicid OR cpu_list)                       */
/******************************************************************************/

void smp_init(void);

void smp_arch_init(void);
void* smp_arch_findmpfps(void);

typedef struct
{
    char        signature[4];
    void*       configuration;
    unt8        lenght;
    unt8        revision;
    unt8        checksum;
    unt8        feature1;
    unt8        feature2;
    unt8        feature3;
    unt8        feature4;
    unt8        feature5;
} smp_arch_mpfps __attribute__ ((packed));

typedef struct
{
    char        signature[4];
    unt16       lenght;
    unt8        revision;
    unt8        checksum;
    char        oemid[8];
    char        productid[12];
    void*       oemtable;
    unt16       oemtablesize;
    unt16       entrycount;
    void*       localapicaddress;
    unt16       extendedtablelenght;
    unt8        extendedtablechecksum;
    unt8        reserved;
    unt8        configuration[0];
} smp_arch_mpct __attribute__ ((packed));

/******************************************************************************/
/* smp_int - Initialize SMP Management                                        */
/*                                                                            */
/* SMP Management is initialized by searching for the MP Floating Pointer     */
/* Structure and, if applicable, the MP Configuration Table. Next, the Local  */
/* APIC and I/O APICs are configured. The AP booted using trampoline code.    */
/* OS structures are updated to reflect the system configuration and control  */
/* is returned to the system.                                                 */
/******************************************************************************/
void smp_init(void)
{
    smp_arch_init();
}

void smp_arch_init(void)
{
    smp_arch_mpfps  *mpfps;
    smp_arch_mpct   *mpct;
    unt8            *mpect;
    unt8            *mpoem;

    unt8 checksum;
    unt8* j;
        
    mpfps = smp_arch_findmpfps();
    
    logSubItem("MP Revision", mpfps->revision == 4 ? "1.4" :
                              mpfps->revision == 1 ? "1.1" :
                                                     "Unknown");

    logSubItem("Legacy PIC Mode", mpfps->feature2 & 0x80 ? "PIC" :
                                                           "Virtual Wire");

    switch (mpfps->feature1)
    {
        case 0:
        {
            if (mpfps->configuration)
            {
                /* If this is a valid structure, the signature field should   *
                 * be "PCMP".                                                 */
                if (!memcmp(mpfps->configuration, "PCMP", 4))
                {
                    /* If this is a valid structure, the lenght field should  *
                     * be larger than 0.                                      */
                    if ((*(unt8*)(mpfps->configuration+4)) != 0)
                    {
                        /* If this is a valid structure, the checksum should  *
                         * be 0.                                              */
                        checksum = 0;
                        for (j = ((unt8*)(mpfps->configuration)); j < ((unt8*)(mpfps->configuration + (*(unt16*)(mpfps->configuration+4)) )); j++)
                            checksum += *j;

                        if (checksum == 0)
                        {
                            /* This is a valid structure. We can now copy it to       *
                             * kernel memory, so we can use it, when boot memory is   *
                             * longer available.                                      */

                            logHex("MP Configuration Table Address", ((unt32)(mpfps->configuration)) );
                            logDec("MP Configuration Table Size", (*(unt16*)(mpfps->configuration+4)));
                    
                            mpct = heap_alloc((*(unt8*)(mpfps->configuration+4)));
                            memcpy(mpct, ((void*)(mpfps->configuration)), (*(unt16*)(mpfps->configuration+4)));

                            logDec("MP Configuration Table Extended Entry Count", mpct->entrycount);
                            logHex("Address of Local APIC", ((unt32)(mpct->localapicaddress)));

                            /* WE HAVE TO ADD CHECKS HERE, TO MAKE SURE WE    */
                            /* DON'T PASS THE BOUNDARY OF THE STRUCTURE!      */

                            

                        }
                    }
                }
            }
            else
            {
                panic("MP Configuration Table Missing");
            }

            break;
        }
        case 1:
        {
        }
        default:
        {
        }
    }

    
}

/******************************************************************************/
/* smp_arch_findmpfps - Find the MP Floating Pointer Structure                */
/*                                                                            */
/* This function locates the MP Floating Pointer Structure by searching for   */
/* it's signature in the BIOS (F0000 - FFFF0), the first kilobyte of the      */
/* EBDA (Extended BIOS Data Area), or the last kilobyte of conventional       */
/* memory is there is no EBDA. Note that he MP Floating Pointer Structure     */
/* must be aligned on a 16 byte boundary. If a signature is found a chucksum  */
/* is performed to validate it.                                               */
/******************************************************************************/
void* smp_arch_findmpfps(void)
{
    unsigned ebda;
    unsigned i;
    unt8* j;
    unt8 checksum;
    void* mpfps;

    ebda = *((unt16*)(0x8040E)) * 16;
    if (ebda == 0) ebda = (*((unt16*)(0x80413)) - 1) * 1024;

    for (i = ebda; i < 0xFFFFF; i += 16)
    {
        /* If we have searched either the EBDA or the last kilobyte of        *
         * memory, start searching the BIOS.                                  */
        if (i == ebda + 1024) i = 0xF0000;

        if (!memcmp((void*)i, "_MP_", 4))
        {
            /* If this is a valid structure, the lenght field should be       *
             * than 0.                                                        */
            if ((*(unt8*)(i+8)) != 0)
            {
                /* If this is a valid structure, the checksum should be 0.    */
                checksum = 0;
                for (j = ((unt8*)(i)); j < ((unt8*)(i+(*(unt8*)(i+8))*16)); j++)
                    checksum += *j;

                if (checksum == 0)
                {
                    /* This is a valid structure. We can now copy it to       *
                     * kernel memory, so we can use it, when boot memory is   *
                     * longer available.                                      */

                    logHex("MP Floating Pointer Structure Address", i);
                    logDec("MP Floating Pointer Structure Size", (*(unt8*)(i+8)) * 16);
                    
                    mpfps = heap_alloc((*(unt8*)(i+8)) * 16);
                    memcpy(mpfps, ((void*)(i)), (*(unt8*)(i+8)) * 16);
                    return mpfps;
                }
            }
        }
    }

    logNote("SMP is not supported on this machine!");
}
