[BITS 16]
[ORG 0x0000]

_enterPM:

	mov ax, 0x9000
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0xFFFF

	mov dx, 0x1705
	call SetCursorPosition

	mov al, 0xFB
	mov bl, 0x0A
	call WriteChar

	call ScrollUp

	mov dx, 0x1704
	call SetCursorPosition

	mov ax, 0x092E
	mov bx, 0x000F
	mov cx, 74
	int 0x10

	mov si, Message
	call WriteString

	mov dx, 0x174D
	call SetCursorPosition

	mov si, Right
	call WriteString

	LoadBootCodeLoop:
		mov ah, 0x00
		mov dl, 0	;!!!!
		int 0x13
		;;;; CHECK FOR ERRORS!!! ;;;	
		mov dx, 0x1000
		mov es, dx

		mov ax, 0x0212
		mov bx, 0
		mov cx, 0x0101
		mov dh, 0x00
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 9216
		mov cx, 0x0101
		mov dh, 0x01
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 18432
		mov cx, 0x0201
		mov dh, 0x00
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 27648
		mov cx, 0x0201
		mov dh, 0x01
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 36864
		mov cx, 0x0301
		mov dh, 0x00
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 46080
		mov cx, 0x0301
		mov dh, 0x01
		mov dl, 0	;!!!
		int 0x13

		mov ax, 0x0212
		mov bx, 55296
		mov cx, 0x0401
		mov dh, 0x00
		mov dl, 0	;!!!
		int 0x13

		jnc Start
	jmp LoadBootCodeLoop

Start:

	mov dx, 0x3f2
	mov al, 0
	out dx, al

	cli

	xor ax, ax
	mov es, ax
	mov ds, ax
	xor si, si
	xor di, di
	mov cx, 0xFFFF
	rep stosw

	mov word [0x0000], 0x00E3
	mov word [0x0002], 0x0000
	mov word [0x0C00], 0x2003
	
	mov cx, 0x0400
	Loop1:
		mov bx, cx
		shl bx, 2
		sub bx, 4
		add bx, 0x1000
		
		

;	mov ax, 0x0000
;	mov es, ax
;	mov ax, 0x1000
;	mov ds, ax
;	mov si, 0x0000
;	mov di, 0x0000
;	mov cx, 0xFFFF
;	cld
;	rep movsb

	mov ax, cs
	mov ds, ax
	mov es, ax

	lidt [idt48]
	lgdt [gdt48]

	call A20
	call init8259

	mov eax, 0
	mov cr3, eax
	mov eax, cr0
	or eax, 0x00000001
	mov cr0, eax
	jmp dword 8:Aye+0x90000

[bits 32]

Aye:

	mov ax, 0x10
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov esi, 0
	mov edi, 0
	mov ecx, 0x4000
	mov eax, 0
	rep stosd

	mov dword [0x00000000], 0x00001003	;Page Table @ 0x00001000 (R/W, Supervisor, Present) [Direct Mapped]
	mov dword [0x00000C00], 0x00002003	;Page Table @ 0x00002000 (R/W, Supervisor, Present) [Kernel Code + Data]
	mov dword [0x00000FFC], 0x00003003	;Page Table @ 0x00003000 (R/W, Supervisor, Present) [Kernel Stack]

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
		add eax, 3
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
		add eax, 0x00010003
		mov [ebx], eax
	loop PageTable2

	mov ecx, 16
	PageTable3:
		mov ebx, ecx
		add ebx, 0x3F0
		dec ebx
		shl ebx, 2
		add ebx, 0x3000
		xor eax, eax
		mov eax, ecx
		dec eax
		shl eax, 12
		add eax, 0x00090003
		mov [ebx], eax
	loop PageTable3

	xor eax, eax
	mov cr3, eax
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

	;Life's beutiful isn't it. Protected Mode is enabled. Paging is only. Nothing crashes. And it
	;only took me two days to get it to this point. (That's 48 hours, better get some more sleep now ;-)

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	xor esi, esi
	xor edi, edi
	mov ebp, 0xFFFFFFFF
	mov esp, 0xFFFFFFFF
	clc
	cld
	
	;STUPID FUCKING ORG!!!! YOU RUINED AN HOUR OF MY LIFE!!!!
	jmp 8:0xC0001000


	;Should we some how get here (i don't think it's possible because we f*cked up the stack) DIE.
	;but don't use cli / hlt, because horrible things might happen. Almost as horrible as burning
	;out the processor. (well no, but I'm hoping these lines won't)

	abc:
	jmp abc

[bits 16]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

WriteString:
	cld
	LoopWriteMessage:
                lodsb
                or al,al
                jz DoneWriteMessage
                mov ah,0x0E
                mov bx,0x000F
                int 0x10
                jmp LoopWriteMessage
	DoneWriteMessage:
                ret
CursorOn:
	mov cx, 0x0020
	mov ah, 0x01
	int 0x10
	ret
CursorOff:
	mov cx, 0x2000
	mov ah, 0x01
	int 0x10
	ret
SetCursorPosition:
	mov ah, 0x02
	mov bh, 0x00
	int 0x10
	ret
WriteChar:
	mov ah, 0x09
	mov bh, 0x00
	mov cx, 1
	int 0x10
	ret
ScrollUp:
	mov ax, 0x0601
	mov bh, 0x0F
	mov cx, 0x0202
	mov dx, 0x184F
	int 0x10
	ret
LogStatus:
	call ScrollUp

	mov dx, 0x1707
	call SetCursorPosition

	mov ax, 0x092E
	mov bx, 0x0007
	mov cx, 71
	int 0x10

	mov al, '['
	mov bl, 0x07
	call WriteChar

	mov dx, 0x174D
	call SetCursorPosition

	mov al, ']'
	mov bl, 0x07
	call WriteChar

	mov dx, 0x1708
	call SetCursorPosition

	call WriteString

	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

gdt:
	dw	0,0,0,0		; dummy

	dw 0FFFFh
	dw 0
	db 0
	db 9Ah			; present, ring 0, code, non-conforming, readable
	db 0CFh			; page-granular, 32-bit
	db 0

	dw 0FFFFh
	dw 0
	db 0
	db 92h			; present, ring 0, data, expand-up, writable
	db 0CFh			; page-granular, 32-bit
	db 0

idt48	dw	0xCDEF			; idt limit=0
	dw	0x5678,0x1234			; idt base=0L

gdt48	dw	0x800		; gdt limit=2048, 256 GDT entries
	dw	gdt,0x9		; gdt base = 0X9xxxx

	BootCodeSize db 18

	Message	db '[ ][Starting Core',0
	Right		db ']',0

A20:
	call empty8042
	mov al, 0xD1
	out 0x64, al
	call empty8042
	mov al, 0xDF
	out 0x60, al
	call empty8042
	ret

empty8042:
	jmp $+2
	jmp $+2
	in al, 0x64
	test al, 0x02
	jnz empty8042
	ret

init8259:

	;;;;;;;;;;;;;;;;;;;;;;;;;
		ret
	;;;;;;;;;;;;;;;;;;;;;;;;


	mov al, 0x11
	out 0x20, al
	jmp $+2
	jmp $+2

	out 0xA0, al
	jmp $+2
	jmp $+2

	mov al, 0x20
	out 0x21, al
	jmp $+2
	jmp $+2

	mov al, 0x28
	out 0xA1, al
	jmp $+2
	jmp $+2

	mov al, 0x04
	out 0x21, al
	jmp $+2
	jmp $+2

	mov al, 0x02
	out 0xA1, al
	jmp $+2
	jmp $+2

	mov al, 0x01
	out 0x21, al
	jmp $+2
	jmp $+2

	out 0xA1, al
	jmp $+2
	jmp $+2

	mov al, 0xFF
	out 0x21, al
	jmp $+2
	jmp $+2

	out 0xA1, al
	jmp $+2
	jmp $+2

	ret

times (9216)-($-$$) db 0
