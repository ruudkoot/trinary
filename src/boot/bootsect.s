;Boot Sector for TriFS Disks
;Copyright (c) 2002, Rudy Koot (Trinary Technologies)
;
;Compile using NASM 0.98.35 or higher

;TODO
;  Compact Code
;    PUSH/POP
;    JMP SHORT
;  Beautify Code
;* Color/Monocrome support
;* Auto Reboot
;  Add code to load from different places from disk
;  Add 13X support
;  Add debug support
;  Better Bad Disk Recovery
;* Bettter RESET
;* REDESING ERROR QUESTION
;  Redisign Previous Boot
;  BPB Compatibility
;  Improve BIOS Call Stability
;  Add nice things like a clock
;  CRC Check
;  Prevouis Boot Parameters
;* COLD BOOT CODE
;  Cheack the Load Address
;  Move the stack
;  Memory Test

[bits 16]
[org 0x7C00]


	jmp 0:Start
	Title		db 'Trinary Operating System', 0
Start:
	; Set Segments ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7FFF
	mov bp, 0x0800
	sti

	; Store Values ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov [bp+2], dl

	; Check Previous Boot ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov si, 0xAA55
	cmp [bp], si
	jz ContinueBoot
	mov [bp], si

	; Detect the Videocard ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	int 0x11
	test al, 0x30
	mov word [bp+4], 0x0070
	mov ax, 0x0007
	je SetVideo
	mov byte [bp+4], 0x1F
	mov al, 0x03
SetVideo:
	int 0x10

	; Draw the Screen ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call CursorOff

	mov cx, bp
	call Blue

	mov ax, 0x0600
	mov bh, 0x0F
	mov cx, 0x0102
	mov dx, 0x184F
	int 0x10

	mov dx, 0x001C
	call SetCursorPosition
	mov si, Title
	call WriteString

ContinueBoot:
	mov word [bp], 0x6699

	; Write the Message ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call ScrollUp
	mov dx, 0x1704
	call SetCursorPosition
	mov ax, 0x092E
	mov bx, 0x000F
	mov cx, 74
	int 0x10

	mov si, MessageLoadBoot
	call WriteString

	mov dx, 0x174D
	call SetCursorPosition
	mov si, ImageRight
	call WriteString

	mov dx, 0x1705
	call SetCursorPosition

	; Load Boot Code ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LoadBootCode:

	mov cx, 10

	LoadBootCodeLoop:
		push cx
		mov ah, 0x00
		mov dl, [bp+2]
		int 0x13
		;;;; CHECK FOR ERRORS!!! ;;;	
		mov ah, 0x02
		mov al, [BootCodeSize]
		mov bx, 0x1000
		mov cx, 0x0003
		mov dh, 0x00
		mov dl, [bp+2]
		int 0x13
		jnc Succes
		pop cx
	loop LoadBootCodeLoop

Failure:
	call CursorOn

	mov ah, 0x00
	int 0x1A
	mov si, dx
	mov di, cx

	ReadKey:
		mov ah, 0x00
		int 0x1A
		sub dx, si
		sbb cx, di

		cmp dx, 182	; 10 seconds
		jae JustAbort

		mov ah, 0x01
		int 0x16
		jz ReadKey
		mov ah, 0x00
		int 0x16
		push ax
		call CursorOff		; Move it for better FXs
		pop ax

	mov bl, 0x04
	and al, 0xDF		;capitalize
	cmp al, 'A'
	jnz TestRetry
JustAbort:
	call WriteChar
	xor si, si
	mov word [bp], si
	mov word [0x0472], si
	jmp 0xF000:0xFFF0
TestRetry:
	cmp al, 'R'
	jnz TestIgnore
	call WriteChar
	jmp ContinueBoot
TestIgnore:
	cmp al, 'I'
	jnz IllegalKey
	call WriteChar
	jmp short StartBooting		;FUCK!
IllegalKey:
	mov ax, 0x0E07
	mov bx, 0x0007
	int 0x10
	jmp short Failure
Succes:
;	mov al, 0xFB
;	mov bl, 0x0A	;MONO???
;	call WriteChar
StartBooting:
	jmp 0x1000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

WriteString:
	cld
	LoopWriteMessage:
                lodsb
                or al,al
                jz DoneWriteMessage
                mov ah,0x0E
                mov bx,0x000F
                int 0x10
                jmp short LoopWriteMessage
	DoneWriteMessage:
                ret
CursorOn:
	mov cx, 0x0020
	jmp short CursorDo
CursorOff:
	mov cx, 0x2000
CursorDo:
	mov ah, 0x01
	jmp short int10
SetCursorPosition:
	mov ah, 0x02
	mov bh, 0x00
	jmp short int10
WriteChar:
	mov ah, 0x09
	mov bh, 0x00
	mov cx, 1
	jmp short int10
ScrollUp:
	mov ax, 0x0601
	mov bh, 0x0F
	mov cx, 0x0202
	mov dx, 0x184F
	jmp short int10
Blue:
	mov ax, 0x0900
	mov bx, [bp+4]
int10:
	int 0x10
	ret

	MessageLoadBoot db '[ ][Starting Boot', 0
	ImageRight db ']', 0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	times 445-($-$$) db 0
	BootCodeSize	db 12
	times 64 db 0xCC
        dw 0xAA55
	times 512 db 0

	