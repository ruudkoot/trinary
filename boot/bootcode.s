[BITS 16]
[ORG 0x1000]

LoadBootCode:

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
		mov ah, 0x02
		mov al, [BootCodeSize]

		mov dx, 0x9000
		mov es, dx

		mov bx, 0x0000
		mov cx, 0x0001
		mov dh, 0x01
		mov dl, 0	;!!!
		int 0x13
		jnc Succes
	jmp LoadBootCodeLoop

Succes:

	mov sp, 0xFFFF
	mov ax, 0x1000
	mov es, ax
	mov ss, ax
	mov ds, ax

	jmp 0x9000:0x0000

	BootCodeSize db 18

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
	jmp CursorDo
CursorOff:
	mov cx, 0x2000
CursorDo:
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

	Message db '[ ][Starting Init', 0
	Right db ']', 0

	times 8192-($-$$) db 0xCC