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
	mov eax, 0
	mov cr3, eax
	mov eax, cr0
	or eax, 0x00000001
	mov cr0, eax
	mov ax, 0x10
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp dword 8:0x11000

[bits 32]

Aye:



	;xor eax, eax
	;mov cr3, eax
	;mov eax, cr0
	;or eax, 0x80000000
	;mov cr0, eax
	
	jmp 0x11000

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

idt48	dw	0			; idt limit=0
	dw	0,0			; idt base=0L

gdt48	dw	0x800		; gdt limit=2048, 256 GDT entries
	dw	gdt,0x9		; gdt base = 0X9xxxx

	BootCodeSize db 18

	Message	db '[ ][Starting Core',0
	Right		db ']',0

	messageLoadingCore	db 'Loading Core', 0
	messageInitializingMemory	db 'Initializing Memory Management', 0


times (9216)-($-$$) db 0
