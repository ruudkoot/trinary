/******************************************************************************/
/* IA-32 Application Programming Interface                                    */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

unt32 arch_space_id;

void arch_api_init(void)
{
    arch_space_id = 0;
}

unt32 arch_api_spacecontrol(void)
{
    word pdp, pdv;

    pdv = vm_alloc();
    pdp = vm_phys(pdv);

    logHex("pdv", pdv);
    logHex("pdp", pdp);

    memcpy( ((void*)(pdv)), ((unsigned*)(0xFFC00C00)), 1024 );

    return ( pdv );
}

void arch_api_threadcontrol(unt32 space_id, unt32 map_data)
{
    word this_id;


    this_id = space_getid();

    logHex("this_id", this_id);
    logHex("space_id", space_id);
    logHex("map_data", map_data);

    space_map( ((word*)(0xFF000000 + arch_space_id * 0x2000)), 0x80000000);

    space_switch(space_id);

    memcpy((void*)0x80000000, (void*)map_data, 8192);

    space_switch(this_id);

    arch_space_id++;
}

void arch_api_threadstart(word thread)
{
    ipc_threadstate[thread] = 1;
}
