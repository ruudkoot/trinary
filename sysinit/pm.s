[BITS 16]
[GLOBAL _enterPM]
[SECTION CODE CLASS=CODE]

_enterPM:
	sti

	mov cx, 10

	LoadBootCodeLoop:
		push cx
		mov ah, 0x00
		mov dl, 0	;!!!!
	
		int 0x13
		;;;; CHECK FOR ERRORS!!! ;;;	
		mov ah, 0x02
		mov al, [BootCodeSize]

		mov dx, 0x0000
		mov es, dx

		mov bx, 0x1000
		mov cx, 0x0101
		mov dh, 0x00
		mov dl, 0	;!!!
		int 0x13

		jnc Start
		pop cx
	loop LoadBootCodeLoop

Start:

	cli
	mov ax, 0
	mov ds, ax
	mov si, 0x1000
	mov di, 0x0000
	mov cx, 0x8000
	rep movsb
	mov ax, cs
	mov ds, ax
	lidt [idt48]
	lgdt [gdt48]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	mov ax, 0x10
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	jmp 0x0008:0x0000

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
	dw	gdt,0x1		; gdt base = 0X9xxxx

	BootCodeSize db 60