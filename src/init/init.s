;******************************************************************************;
;* System Initialization                                                      *;
;* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       *;
;*                                                                            *;
;* This program is free software; you can redistribute it and/or modify       *;
;* it under the terms of the GNU General Public License as published by       *;
;* the Free Software Foundation; either version 2 of the License, or          *;
;* (at your option) any later version.                                        *;
;******************************************************************************;

;******************************************************************************;
;* THIS MODULE IS OUTDATED AND WILL BE FADED OUT! ONLY                        *;
;******************************************************************************;

[bits 32]
[global _Aye]

_Aye:

	mov ax, 0x18
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Rescue the BDA before the page dirctory tramples it.
	mov esi, 0
	mov edi, 0x80000
	mov ecx, 0x4000
	rep movsd

    ;Move Core, Root, Test, Ping and Pong to 1MB.
    mov esi, 0x10000
	mov edi, 0x100000
	mov ecx, 0x80000
	rep movsd


 	;Create the Page Directory
	mov esi, 0
	mov edi, 0
	mov ecx, 0x1600
	mov eax, 0
	rep stosd

	mov dword [0x00000000], 0x00001007	;Page Table @ 0x00001000 (R/W, Supervisor, Present) [Direct Mapped]
	mov dword [0x00000C00], 0x00006007  ;Page Table @ 0x00006000 (R/W, Supervisor, Present) [Thread Control Blocks]
    mov dword [0x00000FF0], 0x00005007  ;Page Table @ 0x00005000 (R/W, Supervisor, Present) [User Page Tables]
    mov dword [0x00000FF4], 0x00002007	;Page Table @ 0x00002000 (R/W, Supervisor, Present) [Kernel Heap]
    mov dword [0x00000FF8], 0x00003007	;Page Table @ 0x00003000 (R/W, Supervisor, Present) [Kernel CDS]
    mov dword [0x00000FFC], 0x00004007	;Page Table @ 0x00004000 (R/W, Supervisor, Present) [Kernel Page Tables]

	;Create Page Table 1 [Direct Mapped]
    mov ecx, 0x0400
	PageTable1:
		mov ebx, ecx
		dec ebx
		shl ebx, 2
		add ebx, 0x1000
		xor eax, eax
		mov eax, ecx
		dec eax
		shl eax, 12
		add eax, 7
		mov [ebx], eax
	loop PageTable1

	mov ecx, 0x0400
	PageTable2:
		mov ebx, ecx
		dec ebx
		shl ebx, 2
		add ebx, 0x2000
		xor eax, eax
		mov eax, ecx
		dec eax
		shl eax, 12
        add eax, 0x00500007
		mov [ebx], eax
	loop PageTable2

	mov ecx, 0x0400
	PageTable3:
		mov ebx, ecx
		dec ebx
		shl ebx, 2
		add ebx, 0x3000
		xor eax, eax
		mov eax, ecx
		dec eax
		shl eax, 12
        add eax, 0x00100007
		mov [ebx], eax
	loop PageTable3

    mov ecx, 0x0400
	PageTable3:
		mov ebx, ecx
		dec ebx
		shl ebx, 2
		add ebx, 0x3000
		xor eax, eax
		mov eax, ecx
		dec eax
		shl eax, 12
        add eax, 0x00900007
		mov [ebx], eax
	loop PageTable3

    ;Create the Page Table 4
    mov dword [0x00004000], 0x00000007  ;Page Direc @ 0x00000000 (R/W, Supervisor, Present)
    mov dword [0x00004004], 0x00001007	;Page Table @ 0x00001000 (R/W, Supervisor, Present) [Direct Mapped]
	mov dword [0x00004C00], 0x00006007	;Page Table @ 0x00006000 (R/W, Supervisor, Present) [Thread Control Blocks]
    mov dword [0x00004FF0], 0x00005007	;Page Table @ 0x00002000 (R/W, Supervisor, Present) [User Page Tabels]
    mov dword [0x00004FF4], 0x00002007	;Page Table @ 0x00002000 (R/W, Supervisor, Present) [Kernel Heap]
    mov dword [0x00004FF8], 0x00003007	;Page Table @ 0x00003000 (R/W, Supervisor, Present) [Kernel CDS]
    mov dword [0x00004FFC], 0x00004007	;Page Table @ 0x00004000 (R/W, Supervisor, Present) [Page Tables]


	xor eax, eax
	mov cr3, eax
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

	;Life's beautiful isn't it. Protected Mode is enabled. Paging is online. Nothing crashes. And it
	;only took me two days to get it to this point. (That's 48 hours, better get some more sleep now ;-)

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	xor esi, esi
	xor edi, edi
	xor ebp, ebp
	mov esp, 0xFFC00000
	clc
	cld

	;STUPID FUCKING ORG!!!! YOU RUINED AN HOUR OF MY LIFE!!!!
	;REMEMBER: BIN/ELF = 0x10:FF800000 (need to strip header)
    ;          PECOFF  = 0x10:FF801000
    ;ANOTER THING TO REMEBER: REMBER THE THINGS TO REMEMBER!
    ;IT COST ME ANOTHER HOUR... I GET SO TIRED SOMETIMES
	jmp 0x10:0xFF800000


	;Should we somehow get here (i don't think it's possible because we f*cked up the stack) DIE.
	;but don't use cli / hlt, because horrible things might happen. Almost as horrible as burning
	;out the processor (well no, but I'm hoping these lines won't). O, yeah the horrible thing:
    ;CLI might cause an exeption when IOCT == 3, which occurs if that caused the kernel to crash
    ;in the first place.

	abc:
          hlt
	jmp abc