/******************************************************************************/
/* Signal Handling                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This modules handles signals, better known as interrupts. To make things   */
/* clear: this module does NOT handle UNIX style signals.                     */
/******************************************************************************/

#include "arch/ia32/signal.c"

void sig_init(void)
{
    logItem("Initializing Signal Management");
    sig_arch_init();
    logStatus(logSuccess);
}
