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

#define word int

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
    space_t *space;

    space = heap_alloc(sizeof(space_t));

    space->handle = space_arch_create();
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
    word    *pd;
    
    /* Allocate memory for a new page directory. I assume heap_alloc          *
     * allocates aligned data, but I don't know if this will hold true in the *
     * future.                                                                */
    pd = heap_alloc(4096);

    logHex("New Page Directory Created @", pd);

    /* The page directory will not contain any mappings in user space space,  *
     * must map the kernel. We just copy this information from a template.    */
    memcpy(pd, pdtemplate, 4096);
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
