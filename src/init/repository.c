/******************************************************************************/
/* System Initialization : Repository                                         */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module implements a limited version of the Repository, to make the    */
/* user experience more pleasant.                                             */
/******************************************************************************/

typedef struct
{
    unsigned (*listfiles)(char*);
    unsigned (*listdirectories)(char*);
    unsigned (*read)(char*);
} repository_register_t;

void repository_init(void)
{
    return;
}

void repository_register(void)
{
    return;
}
