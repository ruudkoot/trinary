;******************************************************************************;
;* Signal Wrapper                                                             *;
;* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       *;
;*                                                                            *;
;* This program is free software; you can redistribute it and/or modify       *;
;* it under the terms of the GNU General Public License as published by       *;
;* the Free Software Foundation; either version 2 of the License, or          *;
;* (at your option) any later version.                                        *;
;******************************************************************************;

;******************************************************************************;
;* I HAVE TO ALIGN THE CODE!!! 8  /  32 / 64 ??? max (2^n) <= codesize!!!     *;
;******************************************************************************;

bits 32

global sig_arch_interrupt_wrapper

sig_arch_interrupt_wrapper:
    iretd

;******************************************************************************;
;* _sig_exception#_wrapper - Exception Wrapper                                *;
;******************************************************************************;

%macro sig_arch_exception_x_wrapper 1

    global sig_arch_exception_%1_wrapper
    extern sig_arch_exception_%1

    sig_arch_exception_%1_wrapper:

        pushad
        push ds
        push es
        push fs
        push gs

        call sig_arch_exception_%1

        pop gs
        pop fs
        pop es
        pop ds
        popad

        iretd

%endmacro

sig_arch_exception_x_wrapper divideerror
sig_arch_exception_x_wrapper debug
sig_arch_exception_x_wrapper nmi
sig_arch_exception_x_wrapper breakpoint
sig_arch_exception_x_wrapper overflow
sig_arch_exception_x_wrapper bounds
sig_arch_exception_x_wrapper opcode
sig_arch_exception_x_wrapper device
sig_arch_exception_x_wrapper double
sig_arch_exception_x_wrapper overrun
sig_arch_exception_x_wrapper tss
sig_arch_exception_x_wrapper segment
sig_arch_exception_x_wrapper stack
sig_arch_exception_x_wrapper protection
sig_arch_exception_x_wrapper page
sig_arch_exception_x_wrapper reserved
sig_arch_exception_x_wrapper math
sig_arch_exception_x_wrapper alignment
sig_arch_exception_x_wrapper machine
sig_arch_exception_x_wrapper sse
sig_arch_exception_x_wrapper unknown14
sig_arch_exception_x_wrapper unknown15
sig_arch_exception_x_wrapper unknown16
sig_arch_exception_x_wrapper unknown17
sig_arch_exception_x_wrapper unknown18
sig_arch_exception_x_wrapper unknown19
sig_arch_exception_x_wrapper unknown1a
sig_arch_exception_x_wrapper unknown1b
sig_arch_exception_x_wrapper unknown1c
sig_arch_exception_x_wrapper unknown1d
sig_arch_exception_x_wrapper unknown1e
sig_arch_exception_x_wrapper unknown1f

;******************************************************************************;
;* _sig_irq#_wrapper - Hardware Interrupt Wrapper                             *;
;*                                                                            *;
;* These functions save the registers on the kernel stack associated with the *;
;* running thread. This work if the thread was in user mode and if the thread *;
;* was in supervisor mode when the hardware interrupt occured. After that it  *;
;* calls the high level language handler and restores the registers when it   *;
;* finishes.                                                                  *;
;*                                                                            *;
;* To makes sure every thing wroks perfectly we have to make sure wwe use     *;
;* kernel segments. At the moment it sets DS, ES, FG and GS, but I think we   *;
;* can do with just DS and ES or maybe just DS. I'll have to disassemble the  *;
;* core to be sure.                                                           *;
;*                                                                            *;
;* At the moment it does not save and restore the FPU, MMX and SSE register   *;
;* so you can't use those instuctions in the high level language handler.     *;
;* Because I plan to implement defered interrupt handling this should not be  *;
;* neccesary. This means the actual interrupt handling (bottom halves or you  *;
;* Linux hackers here) are run as seperate run by the scheduler. Another      *;
;* option would be to disable the FPU on entering the interrupt handler so    *;
;* using FPU, MMX, 3DNow! or SSE instruction would cause an exception at      *;
;* which point their contents could be saved.                                 *;
;*                                                                            *;
;* I have given each interrupt a dedicated high level function to increase    *;
;* the performance. Using a single function with parameter doesn't make it    *;
;* make it portable, because the the handler is architecture specific anyway. *;
;******************************************************************************;

%macro sig_arch_irqx_wrapper 1

    global sig_arch_irq%1_wrapper
    extern sig_arch_irq%1

    sig_arch_irq%1_wrapper:

        pushad
        push ds
        push es
        push fs
        push gs

        call sig_arch_irq%1

        pop gs
        pop fs
        pop es
        pop ds
        popad

        iretd

%endmacro

sig_arch_irqx_wrapper 0
sig_arch_irqx_wrapper 1
sig_arch_irqx_wrapper 2
sig_arch_irqx_wrapper 3
sig_arch_irqx_wrapper 4
sig_arch_irqx_wrapper 5
sig_arch_irqx_wrapper 6
sig_arch_irqx_wrapper 7
sig_arch_irqx_wrapper 8
sig_arch_irqx_wrapper 9
sig_arch_irqx_wrapper 10
sig_arch_irqx_wrapper 11
sig_arch_irqx_wrapper 12
sig_arch_irqx_wrapper 13
sig_arch_irqx_wrapper 14
sig_arch_irqx_wrapper 15
