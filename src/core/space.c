/******************************************************************************/
/* Space Management                                                           */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module manages address spaces.                                        */
/******************************************************************************/

#define word unsigned int

word space_arch_create(void);
word space_arch_switch(word id);

unsigned pageholder = 0;
unsigned* pageholdertable = ((unsigned*)(0xFFFFC000));

typedef struct
{
    word    id;
    void*   handle;
} space_t;

unsigned pdtemplate[1024];

/******************************************************************************/
/* space_init - Initialize Address Space Management                           */
/******************************************************************************/
void space_init(void)
{
    /* Create the pdtemplate.                                                 */

    unsigned* cpd;

    logItem("Initializing Space Management");

    asm("movl %%cr3, %%eax;" : "=a" (cpd));

    logStatus(logSuccess);

    logHex("Kernel Page Directory Address", cpd);
    logHex("Kernel Page Directory Data #0", cpd[0]);
    logHex("Kernel Page Directory Data #1", cpd[1]);
    logHex("Kernel Page Directory Data #FF8", cpd[0xFF8/4]);
    logHex("Kernel Page Directory Data #FFC", cpd[0xFFC/4]);

    memcpy(pdtemplate, cpd, 4096);
}

/******************************************************************************/
/* space_create - Create an Address Space                                     */
/*                                                                            */
/* This function creates a new address space.                                 */
/******************************************************************************/
void space_create(word id)
{
    logHex("Creating Address Space", id);
    
    space_t *space;

    space = heap_alloc(sizeof(space_t));

    space->handle = space_arch_create();

    logHex("Created Address Space", id);
}

void space_map(word* d, unsigned a)
{
    unsigned pt, pagetab;
    unsigned pf;
    
    if (d[a / (4096 * 1024)] == 0x00000000)
    {
//        logItem("Hmmm... there's no page table yet!");

        pt = mmPhysicalAlloc() * 4096;
        d[a / (4096 * 1024)] = pt | 7;
        pageholdertable[pageholder] = pt | 7;
        pagetab = ((unsigned*)(0xFF000000 + pageholder * 4096));

        pageholder++;

//        logHex("New Page Table Created @ Physical Address", pt);
//        logHex("New Page Table Created @ Virtual Address", pagetab);

        pf = mmPhysicalAlloc() * 4096;

//        logHex("New Page Frame Created @ Physical Address", pf);
//        logHex("New Page Frame Created @ Virtual Address", a);

        ((unsigned*)(pagetab))[(a & 0x003FFFFF) / 4096] = pf | 7;

        a += 4096;
        pf = mmPhysicalAlloc() * 4096;

//        logHex("New Page Frame Created @ Physical Address", pf);
//        logHex("New Page Frame Created @ Virtual Address", a);

        ((unsigned*)(pagetab))[(a & 0x003FFFFF) / 4096] = pf | 7;

        a += 4096;
        pf = mmPhysicalAlloc() * 4096;

//        logHex("New Page Frame Created @ Physical Address", pf);
//        logHex("New Page Frame Created @ Virtual Address", a);

        ((unsigned*)(pagetab))[(a & 0x003FFFFF) / 4096] = pf | 7;

        a += 4096;
        pf = mmPhysicalAlloc() * 4096;

//        logHex("New Page Frame Created @ Physical Address", pf);
//        logHex("New Page Frame Created @ Virtual Address", a);

        ((unsigned*)(pagetab))[(a & 0x003FFFFF) / 4096] = pf | 7;


        return;
    }

    panic("CRAP: space_map() ISN't CORRECTLY IMPLEMENTED YET!");
}

/******************************************************************************/
/* space_arch_create - Create an Address Space                                */
/*                                                                            */
/* In order to create a new address space on the IA-32 we need to:            */
/*     * Create a new page directory.                                         */
/*     * Initialize the page directory.                                       */
/******************************************************************************/
word space_arch_create(void)
{
    word    pd;
    unsigned* pagedir;
    
    pd = mmPhysicalAlloc() * 4096;
    logHex("New Page Directory Created @ Physical Address", pd);
    pageholdertable[pageholder] = pd | 0x00000003;

    pagedir = ((unsigned*)(0xFF000000 + pageholder * 4096));
    logHex("New Page Directory Created @ Virtual Address", pagedir);

    pageholder++;

    memcpy(pagedir, ((unsigned*)(0xFFC00000)), 4096);

    
    

    return pd;
}

/******************************************************************************/
/* space_switch - Create an Address Space                                     */
/*                                                                            */
/* This function switches to another address space.                           */
/******************************************************************************/
void space_switch(word id)
{
    space_arch_switch(id);
}

word space_getid(void)
{
    word id;
    
    asm
    (
        "movl %%cr3, %%eax"
        :
        "=a" (id)
    );

    return id;
}

/******************************************************************************/
/* space_arch_create - Create an Address Space                                */
/*                                                                            */
/******************************************************************************/
word space_arch_switch(word id)
{
    asm
    (
        "movl %%eax, %%cr3"
        :
        :
        "a" (id)
    );
}
