/******************************************************************************/
/* System Call Interface                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

extern void syscall_arch_ipc_wrapper(void);

void discardable syscall_arch_init(void)
{
    sig_arch_settrapgate(0xC0, syscall_arch_ipc_wrapper);
}

/******************************************************************************/
/* syscall_arch_ipc - Inter Process Communication                             */
/*                                                                            */
/******************************************************************************/
void syscall_arch_ipc(void)
{

}


/******************************************************************************/
/* syscall_arch_createtask - Create Task                                      */
/******************************************************************************/

/******************************************************************************/
/* syscall_arch_destroytask - Destroy Task                                    */
/******************************************************************************/

/******************************************************************************/
/* syscall_arch_createthread - Create Thread                                  */
/******************************************************************************/

/******************************************************************************/
/* syscall_arch_destroythread - Destroy Thread                                */
/******************************************************************************/