/******************************************************************************/
/* System Call Interface                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module contains the implementation of the Trinary's system calls.     */
/* Even though Trinary supports the same set of system calls on each          */
/* platform, their implementation and calling conventions are highly          */
/* architecture dependant. As Trinary is a microkernel, you will only find a  */
/* few system calls here. There are no calls to support a virutal file        */
/* system, for example. Only minimal documentation about the use of the       */
/* system calls is provided here. Look at the external documentation for more */
/* information.                                                               */
/******************************************************************************/

extern void syscall_arch_ipc_wrapper(void);
extern void asm_ipc(void);

void discardable syscall_arch_init(void)
{
    sig_arch_setinterruptgateu(0xC0, asm_ipc);
}
