;******************************************************************************;
;* Scheduler                                                                  *;
;* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       *;
;*                                                                            *;
;* This program is free software; you can redistribute it and/or modify       *;
;* it under the terms of the GNU General Public License as published by       *;
;* the Free Software Foundation; either version 2 of the License, or          *;
;* (at your option) any later version.                                        *;
;******************************************************************************;

bits 32

global _sched_arch_switch_wrapper

extern _sched_arch_switch

;******************************************************************************;
;* sched_arch_switch_wrapper - Scheduler Switch Wrapper                       *;
;*                                                                            *;
;* After a long time of tinking I decided that switching task wasn't more     *;
;* difficult than switching kernel stacks. As long a you make sure that the   *;
;* that gets switched out has all the register popped on and the kernel stack *;
;* that gets switched in has all the registers ready to be popped of.         *;
;*                                                                            *;
;* It might be cleaner to store the registers in the thread struct, but       *;
;* locating it in memory requires some register to be loaded, which means we  *;
;* to push them on the stack, so we have to store them twice, resulting in    *;
;* slower scheduling. I don't think the loss of speed will be devesating so I *;
;* might decide to store them in a thread struct in the future, anyway.       *;
;*                                                                            *;
;* CURRENT IMPLEMENTATION: The wrapper pushes all registers onto the kernel   *;
;* stack. After that is pushed the stack pointer on the stack, as a parameter *;
;* to the high level language switching function, which saves the pointer in  *;
;* the thread stucture and returns the value of the new stack. The wrapper    *;
;* changes the kernel stack and pop the registers for the new thread off.     *;
;* Finally it IRETDs popping the last registers of (EFLAGS and CS for a       *;
;* kernel thread and EFLAGS, CS, the user mode SS and the user mode ESP for a *;
;* user mode thread). It it also important to note that the ESP pushed on the *;
;* stack as a parameter doesn't need to be popped of, because it is pushed on *;
;* the stack before it is decemented, and there fore doesn't point to itself  *;
;* but the value pushed before.                                               *;
;******************************************************************************;
_sched_arch_switch_wrapper:
    ;push eax
    ;push ebx
    ;push ecx
    ;push edx
    ;push esi
    ;push edi
    ;push ebp
    pushad

    mov edx, 0x20
    mov eax, 0x20
    out dx, al

    push esp
    call _sched_arch_switch
    mov esp, eax

    popad
    ;pop ebp
    ;pop edi
    ;pop esi
    ;pop edx
    ;pop ecx
    ;pop ebx
    ;pop eax
    iretd