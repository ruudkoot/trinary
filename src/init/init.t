/******************************************************************************/
/* System Initialization : Entry Point                                        */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.arch i386, jumps;
.code16gcc;
.text;
.globl entry_start;

/******************************************************************************/
/* entry_start -                                                              */
/*                                                                            */
/* This function setups up the environment, and checks if we really have a    */
/* 32-bit processor.                                                          */
/******************************************************************************/

entry_start:

    /* Setup a real-mode stack, so interrupt can occur safely.                */
    cli;
    movw %cs, %ax;
    movw %ax, %ss;
    xorw %sp, %sp;
    sti;

    movw %ax, %ds;
    movw %ax, %es;

    /* Check if really heave a 32-bit processor. We do this by checking if we *
     * can modify the IOPL bits in the FLAGS register.                        */
    pushf;
    popw %ax;
    orw $0x3000, %ax;
    push %ax;
    popf;
    pushf;
    popw %ax;
    test $0x3000, %ax;
    jz entry_not32bit;

    /* Setup all the segments and the 32-bit stack.                           */
    movw %cs, %ax;
    movw %ax, %fs;
    movw %ax, %gs;
    xorl %esp, %esp;
    xorl %ebp, %ebp;

    /* And finally enter the real System Initializer.                         */
    call entry;

    /* If we somehow return from the function halt the system.                */
    1:
        hlt;
    jmp 1b;

/******************************************************************************/
/* not32bit - Not a 32-bit Processor                                          */
/*                                                                            */
/* We don't have a 32-bit processor. Print a message and halt the system.     */
/******************************************************************************/
entry_not32bit:

    /* Print the error message.                                               */
    movw $entry_error, %si;
    call entry_write;

    /* Wait until the user presses a key.                                     */
    xorb %ah, %ah;
    int $0x16;

    /* And reboot.                                                            */
    1:
        int $0x19;
    jmp 1b;

/******************************************************************************/
/* entry_write - Write String                                                 */
/*                                                                            */
/* This functions displays a string on the screen. We have to use a dedicated */
/* function, because the existing one uses 32-bit code, while we want to use  */
/* this function on 16-bit machines.                                          */
/******************************************************************************/
entry_write:
    cld;
    1:
                lodsb;
                orb %al, %al;
                jz 1f;
                movb $0x0E, %ah;
                movw $0x000F, %bx;
                int $0x10;
                jmp 1b;
    1:
                ret;

.data

entry_error: .ascii "This Operating System requires a 32-bit processor!\n\r\x7";
             .asciz "Press any key to reboot...\n\r";
	.file	"init.c"
	.text
.globl isalnum
	.type	isalnum, @function
isalnum:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	.L4
	leal	-97(%edx), %eax
	cmpb	$25, %al
	ja	.L2
.L4:
	movl	$1, %eax
	jmp	.L5
.L2:
	leal	-49(%edx), %eax
	cmpb	$8, %al
	setbe	%al
	movzbl	%al, %eax
.L5:
	popl	%ebp
	ret
	.size	isalnum, .-isalnum
.globl isalpha
	.type	isalpha, @function
isalpha:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	leal	-65(%eax), %edx
	cmpb	$25, %dl
	setbe	%dl
	subl	$97, %eax
	cmpb	$25, %al
	setbe	%al
	orl	%edx, %eax
	andl	$1, %eax
	ret
	.size	isalpha, .-isalpha
.globl iscsym
	.type	iscsym, @function
iscsym:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	.L12
	leal	-97(%edx), %eax
	cmpb	$25, %al
	ja	.L10
.L12:
	movl	$1, %eax
	jmp	.L13
.L10:
	leal	-48(%edx), %eax
	cmpb	$9, %al
	setbe	%al
	cmpb	$95, %dl
	sete	%dl
	orl	%edx, %eax
	movzbl	%al, %eax
.L13:
	popl	%ebp
	ret
	.size	iscsym, .-iscsym
.globl iscsymf
	.type	iscsymf, @function
iscsymf:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	.L18
	leal	-97(%edx), %eax
	cmpb	$25, %al
	ja	.L16
.L18:
	movl	$1, %eax
	jmp	.L19
.L16:
	xorl	%eax, %eax
	cmpb	$95, %dl
	sete	%al
.L19:
	popl	%ebp
	ret
	.size	iscsymf, .-iscsymf
.globl isctrl
	.type	isctrl, @function
isctrl:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$32, %eax
	cmpb	$94, %al
	seta	%al
	movzbl	%al, %eax
	ret
	.size	isctrl, .-isctrl
.globl isdigit
	.type	isdigit, @function
isdigit:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$48, %eax
	cmpb	$9, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.size	isdigit, .-isdigit
.globl islowwer
	.type	islowwer, @function
islowwer:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$97, %eax
	cmpb	$25, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.size	islowwer, .-islowwer
.globl isprint
	.type	isprint, @function
isprint:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$32, %eax
	cmpb	$94, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.size	isprint, .-isprint
.globl ispunct
	.type	ispunct, @function
ispunct:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-33(%edx), %eax
	cmpb	$14, %al
	jbe	.L30
	leal	-58(%edx), %eax
	cmpb	$6, %al
	jbe	.L30
	leal	-91(%edx), %eax
	cmpb	$5, %al
	jbe	.L30
	leal	-123(%edx), %eax
	cmpb	$3, %al
	setbe	%al
	movzbl	%al, %eax
	jmp	.L33
.L30:
	movl	$1, %eax
.L33:
	popl	%ebp
	ret
	.size	ispunct, .-ispunct
.globl isspace
	.type	isspace, @function
isspace:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	cmpb	$32, %al
	sete	%dl
	subl	$9, %eax
	cmpb	$4, %al
	setbe	%al
	orl	%edx, %eax
	andl	$1, %eax
	ret
	.size	isspace, .-isspace
.globl isupper
	.type	isupper, @function
isupper:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$65, %eax
	cmpb	$25, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.size	isupper, .-isupper
.globl isxdigit
	.type	isxdigit, @function
isxdigit:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-48(%edx), %eax
	cmpb	$9, %al
	jbe	.L42
	leal	-97(%edx), %eax
	cmpb	$5, %al
	ja	.L40
.L42:
	movl	$1, %eax
	jmp	.L43
.L40:
	leal	-65(%edx), %eax
	cmpb	$5, %al
	setbe	%al
	movzbl	%al, %eax
.L43:
	popl	%ebp
	ret
	.size	isxdigit, .-isxdigit
.globl tolower
	.type	tolower, @function
tolower:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	leal	-65(%edx), %eax
	cmpl	$25, %eax
	ja	.L46
	addl	$32, %edx
.L46:
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	tolower, .-tolower
.globl toupper
	.type	toupper, @function
toupper:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	leal	-97(%edx), %eax
	cmpl	$25, %eax
	ja	.L50
	subl	$32, %edx
.L50:
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	toupper, .-toupper
.globl i16toa
	.type	i16toa, @function
i16toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %eax
	movb	16(%ebp), %dl
	testw	%si, %si
	movl	%eax, %edi
	movb	%dl, -13(%ebp)
	jns	.L56
	movb	$45, (%eax)
	leal	1(%eax), %edi
	negl	%esi
.L56:
	movl	%edi, %ebx
.L57:
	movzbl	-13(%ebp), %edx
	movswl	%si,%eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	leal	1(%ebx), %ecx
	cmpb	$9, %dl
	movl	%eax, %esi
	jle	.L58
	leal	55(%edx), %eax
	jmp	.L69
.L58:
	leal	48(%edx), %eax
.L69:
	testw	%si, %si
	movb	%al, (%ebx)
	movl	%ecx, %ebx
	jg	.L57
	movb	$0, (%ecx)
	leal	-1(%ecx), %ebx
	movl	%edi, %ecx
.L62:
	movb	(%ebx), %dl
	movb	(%ecx), %al
	movb	%al, (%ebx)
	decl	%ebx
	movb	%dl, (%ecx)
	incl	%ecx
	cmpl	%ebx, %ecx
	jb	.L62
	popl	%eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	i16toa, .-i16toa
.globl i32toa
	.type	i32toa, @function
i32toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$8, %esp
	movl	8(%ebp), %ebx
	movl	12(%ebp), %eax
	movb	16(%ebp), %dl
	testl	%ebx, %ebx
	movl	%eax, %esi
	movb	%dl, -13(%ebp)
	jns	.L73
	movb	$45, (%eax)
	leal	1(%eax), %esi
	negl	%ebx
.L73:
	movl	%esi, %ecx
.L74:
	movzbl	-13(%ebp), %edx
	movl	%ebx, %eax
	movl	%edx, %edi
	cltd
	idivl	%edi
	cmpb	$9, %dl
	movl	%eax, -20(%ebp)
	movb	%dl, %al
	movl	-20(%ebp), %ebx
	leal	1(%ecx), %edx
	jle	.L75
	addl	$55, %eax
	jmp	.L86
.L75:
	addl	$48, %eax
.L86:
	movb	%al, (%ecx)
	movl	%edx, %ecx
	cmpl	$0, -20(%ebp)
	jg	.L74
	movb	$0, (%edx)
	leal	-1(%edx), %ebx
	movl	%esi, %ecx
.L79:
	movb	(%ebx), %dl
	movb	(%ecx), %al
	movb	%al, (%ebx)
	decl	%ebx
	movb	%dl, (%ecx)
	incl	%ecx
	cmpl	%ebx, %ecx
	jb	.L79
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	i32toa, .-i32toa
.globl u16toa
	.type	u16toa, @function
u16toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %edi
	movb	16(%ebp), %al
	movl	8(%ebp), %esi
	movl	%edi, %ebx
	movb	%al, -13(%ebp)
.L88:
	movzbl	-13(%ebp), %edx
	movzwl	%si, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	leal	1(%ebx), %ecx
	cmpb	$9, %dl
	movl	%eax, %esi
	jle	.L89
	leal	55(%edx), %eax
	jmp	.L100
.L89:
	leal	48(%edx), %eax
.L100:
	testw	%si, %si
	movb	%al, (%ebx)
	movl	%ecx, %ebx
	jne	.L88
	movb	$0, (%ecx)
	leal	-1(%ecx), %ebx
	movl	%edi, %ecx
.L93:
	movb	(%ebx), %dl
	movb	(%ecx), %al
	movb	%al, (%ebx)
	decl	%ebx
	movb	%dl, (%ecx)
	incl	%ecx
	cmpl	%ebx, %ecx
	jb	.L93
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	u16toa, .-u16toa
.globl u32toa
	.type	u32toa, @function
u32toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %esi
	movb	16(%ebp), %al
	movl	%esi, %ecx
	movb	%al, -13(%ebp)
.L102:
	movzbl	-13(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %edi
	xorl	%edx, %edx
	divl	%edi
	movl	%eax, %ebx
	cmpb	$9, %dl
	movb	%dl, %al
	movl	%ebx, 8(%ebp)
	leal	1(%ecx), %edx
	jle	.L103
	addl	$55, %eax
	jmp	.L114
.L103:
	addl	$48, %eax
.L114:
	testl	%ebx, %ebx
	movb	%al, (%ecx)
	movl	%edx, %ecx
	jne	.L102
	movb	$0, (%edx)
	leal	-1(%edx), %ebx
	movl	%esi, %ecx
.L107:
	movb	(%ebx), %dl
	movb	(%ecx), %al
	movb	%al, (%ebx)
	decl	%ebx
	movb	%dl, (%ecx)
	incl	%ecx
	cmpl	%ebx, %ecx
	jb	.L107
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	u32toa, .-u32toa
.globl abs
	.type	abs, @function
abs:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	ret
	.size	abs, .-abs
.globl max
	.type	max, @function
max:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jge	.L118
	movl	8(%ebp), %eax
.L118:
	popl	%ebp
	ret
	.size	max, .-max
.globl min
	.type	min, @function
min:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	.L121
	movl	8(%ebp), %eax
.L121:
	popl	%ebp
	ret
	.size	min, .-min
.globl rotl
	.type	rotl, @function
rotl:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	andl	$31, %ecx
	jmp	.L134
.L125:
	movl	%edx, %eax
	addl	%edx, %edx
	andl	$-2147483648, %eax
	testl	%eax, %eax
	je	.L134
	orl	$1, %edx
.L134:
	decl	%ecx
	cmpl	$-1, %ecx
	jne	.L125
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	rotl, .-rotl
.globl rotr
	.type	rotr, @function
rotr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	andl	$31, %ecx
	jmp	.L146
.L137:
	movl	%edx, %eax
	andl	$1, %eax
	shrl	%edx
	testl	%eax, %eax
	je	.L146
	orl	$-2147483648, %edx
.L146:
	decl	%ecx
	cmpl	$-1, %ecx
	jne	.L137
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	rotr, .-rotr
.globl memccpy
	.type	memccpy, @function
memccpy:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	pushl	%ebx
	movl	20(%ebp), %ecx
	movl	12(%ebp), %ebx
	jmp	.L148
.L149:
	decl	%ecx
.L148:
	testl	%ecx, %ecx
	jne	.L150
	xorl	%edx, %edx
	jmp	.L152
.L150:
	incl	%ebx
	incl	%edx
	movb	-1(%ebx), %al
	movb	%al, -1(%edx)
	cmpb	16(%ebp), %al
	jne	.L149
.L152:
	popl	%ebx
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	memccpy, .-memccpy
.globl memchr
	.type	memchr, @function
memchr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	jmp	.L155
.L156:
	incl	%eax
	decl	%edx
.L155:
	testl	%edx, %edx
	jne	.L157
	xorl	%eax, %eax
	jmp	.L159
.L157:
	cmpb	%cl, (%eax)
	jne	.L156
.L159:
	popl	%ebp
	ret
	.size	memchr, .-memchr
.globl memcmp
	.type	memcmp, @function
memcmp:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movl	16(%ebp), %edx
	pushl	%esi
	movl	12(%ebp), %esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	testl	%edx, %edx
	je	.L165
	jmp	.L170
.L166:
	incl	%ebx
	incl	%esi
.L170:
	decl	%edx
	je	.L167
	movb	(%ebx), %al
	cmpb	(%esi), %al
	je	.L166
.L167:
	movzbl	(%ebx), %ecx
	movzbl	(%esi), %eax
	subl	%eax, %ecx
.L165:
	popl	%ebx
	movl	%ecx, %eax
	popl	%esi
	popl	%ebp
	ret
	.size	memcmp, .-memcmp
.globl memcpy
	.type	memcpy, @function
memcpy:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	16(%ebp), %ebx
	jmp	.L172
.L173:
	movb	-1(%ecx), %al
	movb	%al, -1(%edx)
.L172:
	decl	%ebx
	incl	%edx
	incl	%ecx
	cmpl	$-1, %ebx
	jne	.L173
	movl	8(%ebp), %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	memcpy, .-memcpy
.globl memcpybw
	.type	memcpybw, @function
memcpybw:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	jmp	.L177
.L178:
	movb	-1(%ebx), %al
	movb	%al, -2(%edx)
.L177:
	decl	%ecx
	addl	$2, %edx
	incl	%ebx
	cmpl	$-1, %ecx
	jne	.L178
	movl	8(%ebp), %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	memcpybw, .-memcpybw
.globl _memicmp
	.type	_memicmp, @function
_memicmp:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%edi
	movl	12(%ebp), %edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	movl	16(%ebp), %ebx
	jmp	.L182
.L183:
	movl	8(%ebp), %ecx
	movb	(%ecx), %dl
	movb	(%edi), %cl
	cmpb	%cl, %dl
	je	.L184
	leal	-65(%edx), %eax
	cmpb	$25, %al
	ja	.L186
	movzbl	%dl, %eax
	leal	32(%eax), %esi
	jmp	.L188
.L186:
	movzbl	%dl, %esi
.L188:
	leal	-65(%ecx), %eax
	cmpb	$25, %al
	ja	.L189
	movzbl	%cl, %eax
	addl	$32, %eax
	jmp	.L191
.L189:
	movzbl	%cl, %eax
.L191:
	cmpl	%eax, %esi
	jne	.L192
.L184:
	incl	8(%ebp)
	incl	%edi
.L182:
	decl	%ebx
	cmpl	$-1, %ebx
	jne	.L183
.L192:
	subl	%eax, %esi
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	_memicmp, .-_memicmp
.globl memmove
	.type	memmove, @function
memmove:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	pushl	%esi
	movl	8(%ebp), %esi
	pushl	%ebx
	movl	16(%ebp), %edx
	cmpl	%ecx, %esi
	jbe	.L195
	leal	(%ecx,%edx), %eax
	cmpl	%eax, %esi
	jb	.L197
.L195:
	movl	%ecx, %ebx
	movl	%esi, %ecx
	jmp	.L198
.L199:
	movb	-1(%ebx), %al
	movb	%al, -1(%ecx)
.L198:
	decl	%edx
	incl	%ecx
	incl	%ebx
	cmpl	$-1, %edx
	jne	.L199
	jmp	.L200
.L197:
	movl	%eax, %ebx
	leal	(%esi,%edx), %ecx
	jmp	.L201
.L202:
	movb	(%ebx), %al
	movb	%al, (%ecx)
.L201:
	decl	%edx
	decl	%ebx
	decl	%ecx
	cmpl	$-1, %edx
	jne	.L202
.L200:
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	memmove, .-memmove
.globl memset
	.type	memset, @function
memset:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	pushl	%ebx
	movl	16(%ebp), %ecx
	movl	12(%ebp), %ebx
	movl	%eax, %edx
	jmp	.L205
.L206:
	movb	%bl, -1(%edx)
.L205:
	decl	%ecx
	incl	%edx
	cmpl	$-1, %ecx
	jne	.L206
	popl	%ebx
	popl	%ebp
	ret
	.size	memset, .-memset
.globl memsetw
	.type	memsetw, @function
memsetw:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	jmp	.L210
.L211:
	movw	%ax, -2(%edx)
.L210:
	decl	%ecx
	addl	$2, %edx
	cmpl	$-1, %ecx
	jne	.L211
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	memsetw, .-memsetw
.globl swab
	.type	swab, @function
swab:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	12(%ebp), %ecx
	pushl	%ebx
	movl	16(%ebp), %esi
	movl	8(%ebp), %ebx
	jmp	.L215
.L216:
	movb	-2(%ebx), %dl
	subl	$2, %esi
	movb	-1(%ebx), %al
	movb	%dl, -1(%ecx)
	movb	%al, -2(%ecx)
.L215:
	addl	$2, %ebx
	addl	$2, %ecx
	cmpl	$1, %esi
	jg	.L216
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	swab, .-swab
.globl strcat
	.type	strcat, @function
strcat:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	jmp	.L220
.L221:
	incl	%edx
.L220:
	cmpb	$0, (%edx)
	jne	.L221
.L225:
	movb	(%ecx), %al
	incl	%ecx
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	jne	.L225
	movl	8(%ebp), %eax
	popl	%ebp
	ret
	.size	strcat, .-strcat
.globl strncat
	.type	strncat, @function
strncat:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
.L229:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L229
	decl	%edx
	jmp	.L231
.L232:
	movb	(%ebx), %al
	testb	%al, %al
	movb	%al, (%edx)
	je	.L233
	incl	%edx
	incl	%ebx
.L231:
	decl	%ecx
	cmpl	$-1, %ecx
	jne	.L232
	movb	$0, (%edx)
.L233:
	movl	8(%ebp), %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	strncat, .-strncat
.globl strchr
	.type	strchr, @function
strchr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	jmp	.L240
.L241:
	incl	%edx
.L240:
	movb	(%edx), %al
	testb	%al, %al
	je	.L242
	cmpb	%cl, %al
	jne	.L241
	jmp	.L244
.L242:
	xorl	%eax, %eax
	testb	%cl, %cl
	jne	.L246
.L244:
	movl	%edx, %eax
.L246:
	popl	%ebp
	ret
	.size	strchr, .-strchr
.globl strcmp
	.type	strcmp, @function
strcmp:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %ebx
	jmp	.L249
.L250:
	incl	%ebx
	incl	%ecx
.L249:
	movzbl	(%ecx), %eax
	movzbl	(%ebx), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	jne	.L251
	cmpb	$0, (%ecx)
	jne	.L250
	jmp	.L253
.L251:
	sarl	$31, %eax
	orl	$1, %eax
.L253:
	popl	%ebx
	popl	%ebp
	ret
	.size	strcmp, .-strcmp
.globl strcpy
	.type	strcpy, @function
strcpy:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
.L259:
	movb	(%ecx), %al
	incl	%ecx
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	jne	.L259
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	strcpy, .-strcpy
.globl strcspn
	.type	strcspn, @function
strcspn:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
.L265:
	movb	$0, -40(%ebp,%eax)
	incl	%eax
	cmpl	$32, %eax
	jne	.L265
	movl	12(%ebp), %ebx
	jmp	.L267
.L268:
	movb	%dl, %al
	movl	%edx, %ecx
	shrb	$3, %al
	andl	$7, %ecx
	movzbl	%al, %eax
	movl	$1, %edx
	sall	%cl, %edx
	incl	%ebx
	orb	%dl, -40(%ebp,%eax)
.L267:
	movb	(%ebx), %dl
	testb	%dl, %dl
	jne	.L268
	orb	$1, -40(%ebp)
	xorl	%edx, %edx
	jmp	.L270
.L271:
	incl	%edx
.L270:
	movb	(%edx,%esi), %cl
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-40(%ebp,%eax), %eax
	sarl	%cl, %eax
	testb	$1, %al
	je	.L271
	addl	$32, %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strcspn, .-strcspn
.globl stricmp
	.type	stricmp, @function
stricmp:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %ebx
.L278:
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$64, %eax
	jle	.L279
	cmpl	$90, %eax
	jg	.L279
	addl	$32, %eax
.L279:
	movzbl	(%ecx), %edx
	cmpl	$64, %edx
	jle	.L282
	cmpl	$90, %edx
	jg	.L282
	addl	$32, %edx
.L282:
	testl	%eax, %eax
	je	.L285
	cmpl	%edx, %eax
	jne	.L285
	incl	%ecx
	jmp	.L278
.L285:
	popl	%ebx
	subl	%edx, %eax
	popl	%ebp
	ret
	.size	stricmp, .-stricmp
.globl strlen
	.type	strlen, @function
strlen:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	%ecx, %edx
.L289:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L289
	popl	%ebp
	subl	%ecx, %edx
	leal	-1(%edx), %eax
	ret
	.size	strlen, .-strlen
.globl strlwr
	.type	strlwr, @function
strlwr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	jmp	.L305
.L296:
	movb	(%edx), %cl
	leal	-65(%ecx), %eax
	cmpb	$25, %al
	ja	.L305
	leal	32(%ecx), %eax
	movb	%al, (%edx)
.L305:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L296
	popl	%ebp
	movl	%edx, %eax
	ret
	.size	strlwr, .-strlwr
.globl strncmp
	.type	strncmp, @function
strncmp:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movl	16(%ebp), %edx
	pushl	%esi
	movl	12(%ebp), %esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	testl	%edx, %edx
	je	.L309
	jmp	.L315
.L310:
	incl	%ebx
	incl	%esi
.L315:
	decl	%edx
	je	.L311
	movb	(%ebx), %al
	testb	%al, %al
	je	.L311
	cmpb	(%esi), %al
	je	.L310
.L311:
	movzbl	(%ebx), %ecx
	movzbl	(%esi), %eax
	subl	%eax, %ecx
.L309:
	popl	%ebx
	movl	%ecx, %eax
	popl	%esi
	popl	%ebp
	ret
	.size	strncmp, .-strncmp
.globl strncpy
	.type	strncpy, @function
strncpy:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	jmp	.L317
.L318:
	incl	%ebx
	decl	%ecx
.L317:
	testl	%ecx, %ecx
	je	.L319
	movb	(%ebx), %al
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	jne	.L318
	movl	%edx, %eax
	jmp	.L322
.L323:
	movb	$0, -1(%eax)
.L322:
	incl	%eax
	decl	%ecx
	jne	.L323
.L319:
	movl	8(%ebp), %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	strncpy, .-strncpy
.globl strnicmp
	.type	strnicmp, @function
strnicmp:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	pushl	%esi
	movl	8(%ebp), %esi
	pushl	%ebx
	movl	12(%ebp), %ebx
	testl	%ecx, %ecx
	je	.L328
.L339:
	movzbl	(%esi), %eax
	incl	%esi
	cmpl	$64, %eax
	jle	.L329
	cmpl	$90, %eax
	jg	.L329
	addl	$32, %eax
.L329:
	movzbl	(%ebx), %edx
	cmpl	$64, %edx
	jle	.L332
	cmpl	$90, %edx
	jg	.L332
	addl	$32, %edx
.L332:
	decl	%ecx
	je	.L335
	testl	%eax, %eax
	je	.L335
	cmpl	%edx, %eax
	jne	.L335
	incl	%ebx
	jmp	.L339
.L335:
	subl	%edx, %eax
.L328:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strnicmp, .-strnicmp
.globl strnpst
	.type	strnpst, @function
strnpst:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	pushl	%ebx
	jmp	.L341
.L342:
	movb	%bl, (%eax)
	incl	%ecx
	incl	%eax
	decl	%edx
.L341:
	movb	(%ecx), %bl
	testb	%bl, %bl
	je	.L344
	testl	%edx, %edx
	jne	.L342
.L344:
	popl	%ebx
	popl	%ebp
	ret
	.size	strnpst, .-strnpst
.globl _strnset
	.type	_strnset, @function
_strnset:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	jmp	.L347
.L348:
	movb	%bl, -1(%edx)
.L347:
	decl	%ecx
	cmpl	$-1, %ecx
	je	.L349
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L348
.L349:
	movl	8(%ebp), %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	_strnset, .-_strnset
.globl strpbrk
	.type	strpbrk, @function
strpbrk:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
.L353:
	movb	$0, -40(%ebp,%eax)
	incl	%eax
	cmpl	$32, %eax
	jne	.L353
	movl	12(%ebp), %ebx
	jmp	.L355
.L356:
	movb	%dl, %al
	movl	%edx, %ecx
	shrb	$3, %al
	andl	$7, %ecx
	movzbl	%al, %eax
	movl	$1, %edx
	sall	%cl, %edx
	incl	%ebx
	orb	%dl, -40(%ebp,%eax)
.L355:
	movb	(%ebx), %dl
	testb	%dl, %dl
	jne	.L356
	jmp	.L366
.L358:
	movb	%dl, %al
	movl	%edx, %ecx
	shrb	$3, %al
	andl	$7, %ecx
	movzbl	%al, %eax
	movzbl	-40(%ebp,%eax), %eax
	sarl	%cl, %eax
	testb	$1, %al
	je	.L359
	movl	%esi, %eax
	jmp	.L361
.L359:
	incl	%esi
.L366:
	movb	(%esi), %dl
	testb	%dl, %dl
	jne	.L358
	xorl	%eax, %eax
.L361:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strpbrk, .-strpbrk
.globl strpst
	.type	strpst, @function
strpst:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	jmp	.L368
.L369:
	movb	%cl, (%eax)
	incl	%edx
	incl	%eax
.L368:
	movb	(%edx), %cl
	testb	%cl, %cl
	jne	.L369
	popl	%ebp
	ret
	.size	strpst, .-strpst
.globl strrchr
	.type	strrchr, @function
strrchr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	pushl	%ebx
	movl	12(%ebp), %ebx
	movl	%ecx, %edx
.L373:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L373
.L375:
	decl	%edx
	cmpl	%ecx, %edx
	je	.L376
	cmpb	%bl, (%edx)
	je	.L378
	jmp	.L375
.L376:
	xorl	%eax, %eax
	cmpb	%bl, (%ecx)
	jne	.L380
.L378:
	movl	%edx, %eax
.L380:
	popl	%ebx
	popl	%ebp
	ret
	.size	strrchr, .-strrchr
.globl _strrev
	.type	_strrev, @function
_strrev:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	8(%ebp), %esi
	pushl	%ebx
	movl	%esi, %edx
.L386:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	.L386
	leal	-2(%edx), %ebx
	movl	%esi, %ecx
	jmp	.L388
.L389:
	movb	(%ebx), %al
	movb	-1(%ecx), %dl
	movb	%al, -1(%ecx)
	movb	%dl, (%ebx)
	decl	%ebx
.L388:
	movl	%ecx, %eax
	incl	%ecx
	cmpl	%ebx, %eax
	jb	.L389
	movl	%esi, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	_strrev, .-_strrev
.globl _strset
	.type	_strset, @function
_strset:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	%eax, %edx
	jmp	.L395
.L396:
	movb	%cl, (%edx)
	incl	%edx
.L395:
	cmpb	$0, (%edx)
	jne	.L396
	popl	%ebp
	ret
	.size	_strset, .-_strset
.globl strspn
	.type	strspn, @function
strspn:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %esi
.L400:
	movb	$0, -40(%ebp,%eax)
	incl	%eax
	cmpl	$32, %eax
	jne	.L400
	movl	12(%ebp), %ebx
	jmp	.L402
.L403:
	movb	%dl, %al
	movl	%edx, %ecx
	shrb	$3, %al
	andl	$7, %ecx
	movzbl	%al, %eax
	movl	$1, %edx
	sall	%cl, %edx
	incl	%ebx
	orb	%dl, -40(%ebp,%eax)
.L402:
	movb	(%ebx), %dl
	testb	%dl, %dl
	jne	.L403
	xorl	%eax, %eax
	xorl	%edx, %edx
	cmpb	$0, (%esi)
	jne	.L408
	jmp	.L407
.L409:
	incl	%edx
.L408:
	movb	(%edx,%esi), %cl
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-40(%ebp,%eax), %eax
	sarl	%cl, %eax
	testb	$1, %al
	jne	.L409
	movl	%edx, %eax
.L407:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	strspn, .-strspn
.globl strstr
	.type	strstr, @function
strstr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	12(%ebp), %edi
	pushl	%esi
	movl	8(%ebp), %eax
	pushl	%ebx
	cmpb	$0, (%edi)
	jne	.L417
	jmp	.L418
.L419:
	movb	(%edi), %dl
	movl	%edi, %ebx
	movl	%eax, %esi
	jmp	.L420
.L421:
	movb	1(%esi), %cl
	incl	%ebx
	testb	%cl, %cl
	je	.L422
	movb	(%ebx), %dl
	incl	%esi
	testb	%dl, %dl
	je	.L418
.L420:
	cmpb	%dl, %cl
	je	.L421
	jmp	.L424
.L422:
	cmpb	$0, (%ebx)
	je	.L418
.L424:
	incl	%eax
.L417:
	movb	(%eax), %cl
	testb	%cl, %cl
	jne	.L419
	xorl	%eax, %eax
.L418:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	strstr, .-strstr
.globl strupr
	.type	strupr, @function
strupr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	jmp	.L438
.L429:
	incl	%edx
	movb	(%edx), %cl
	leal	-97(%ecx), %eax
	cmpb	$25, %al
	ja	.L438
	leal	-32(%ecx), %eax
	movb	%al, (%edx)
.L438:
	cmpb	$0, (%edx)
	jne	.L429
	popl	%ebp
	ret
	.size	strupr, .-strupr
.globl srand
	.type	srand, @function
srand:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	movl	%eax, holdrand
	ret
	.size	srand, .-srand
.globl rand
	.type	rand, @function
rand:
	imull	$214013, holdrand, %eax
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	addl	$2531011, %eax
	movl	%eax, holdrand
	sarl	$16, %eax
	andl	$32767, %eax
	ret
	.size	rand, .-rand
.globl mem_zero
	.type	mem_zero, @function
mem_zero:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	pushl	%edi
	movl	8(%ebp), %edi
	shrl	$2, %ecx
#APP
	rep stosl;
#NO_APP
	popl	%edi
	popl	%ebp
	ret
	.size	mem_zero, .-mem_zero
.globl heap_init
	.type	heap_init, @function
heap_init:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	popl	%ebp
	movl	%eax, heap_pointer
	leal	(%eax,%ecx), %edx
	movl	%edx, heap_end
	jmp	mem_zero
	.size	heap_init, .-heap_init
.globl heap_alloc
	.type	heap_alloc, @function
heap_alloc:
	movl	heap_pointer, %eax
	pushl	%ebp
	movl	%esp, %ebp
	movl	%eax, %edx
	addl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, heap_pointer
	ret
	.size	heap_alloc, .-heap_alloc
.globl repository_init
	.type	repository_init, @function
repository_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	repository_init, .-repository_init
.globl repository_register
	.type	repository_register, @function
repository_register:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	repository_register, .-repository_register
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"[ ][.....................................................................]"
	.text
.globl log_item
	.type	log_item, @function
log_item:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$80, %esp
	pushl	$.LC0
	leal	-81(%ebp), %esi
	pushl	%esi
	call	strcpy
	leal	-77(%ebp), %eax
	pushl	8(%ebp)
	pushl	%eax
	call	strpst
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	addl	$16, %esp
	movl	-4(%ebp), %esi
	leave
	ret
	.size	log_item, .-log_item
	.section	.rodata.str1.1
.LC1:
	.string	"   [.....................................................................]"
	.text
.globl log_subitem
	.type	log_subitem, @function
log_subitem:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$80, %esp
	pushl	$.LC1
	leal	-81(%ebp), %esi
	pushl	%esi
	call	strcpy
	leal	-77(%ebp), %eax
	pushl	8(%ebp)
	pushl	%eax
	call	strpst
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	addl	$16, %esp
	movl	-4(%ebp), %esi
	leave
	ret
	.size	log_subitem, .-log_subitem
.globl log_number
	.type	log_number, @function
log_number:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$100, %esp
	pushl	$10
	leal	-28(%ebp), %eax
	pushl	%eax
	pushl	12(%ebp)
	leal	-103(%ebp), %esi
	movl	%eax, -108(%ebp)
	call	u32toa
	pushl	$.LC1
	pushl	%esi
	call	strcpy
	leal	-99(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	strnpst
	movl	-108(%ebp), %edi
	addl	$32, %esp
	pushl	$66
	orl	$-1, %ecx
	leal	-28(%ebp), %eax
	cld
	pushl	%eax
	xorl	%eax, %eax
	repnz
	scasb
	movl	$74, %eax
	notl	%ecx
	subl	%ecx, %eax
	cmpl	$4, %eax
	jge	.L458
	movl	$4, %eax
.L458:
	leal	(%esi,%eax), %eax
	pushl	%eax
	call	strnpst
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	addl	$12, %esp
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	log_number, .-log_number
.globl log_dec
	.type	log_dec, @function
log_dec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$100, %esp
	pushl	$10
	leal	-28(%ebp), %eax
	pushl	%eax
	pushl	12(%ebp)
	leal	-103(%ebp), %esi
	movl	%eax, -108(%ebp)
	call	u32toa
	pushl	$.LC1
	pushl	%esi
	call	strcpy
	leal	-99(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	strnpst
	movl	-108(%ebp), %edi
	addl	$32, %esp
	pushl	$66
	orl	$-1, %ecx
	leal	-28(%ebp), %eax
	cld
	pushl	%eax
	xorl	%eax, %eax
	repnz
	scasb
	movl	$74, %eax
	notl	%ecx
	subl	%ecx, %eax
	cmpl	$4, %eax
	jge	.L461
	movl	$4, %eax
.L461:
	leal	(%esi,%eax), %eax
	pushl	%eax
	call	strnpst
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	addl	$12, %esp
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	log_dec, .-log_dec
	.section	.rodata.str1.1
.LC2:
	.string	"   [.............................................................0000000h]"
	.text
.globl log_hex
	.type	log_hex, @function
log_hex:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$100, %esp
	pushl	$16
	leal	-28(%ebp), %eax
	pushl	%eax
	pushl	12(%ebp)
	leal	-103(%ebp), %esi
	movl	%eax, -108(%ebp)
	call	u32toa
	pushl	$.LC2
	pushl	%esi
	call	strcpy
	leal	-99(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	strnpst
	movl	-108(%ebp), %edi
	addl	$32, %esp
	pushl	$66
	orl	$-1, %ecx
	leal	-28(%ebp), %eax
	cld
	pushl	%eax
	xorl	%eax, %eax
	repnz
	scasb
	movl	$73, %eax
	notl	%ecx
	subl	%ecx, %eax
	cmpl	$4, %eax
	jge	.L464
	movl	$4, %eax
.L464:
	leal	(%esi,%eax), %eax
	pushl	%eax
	call	strnpst
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	addl	$12, %esp
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	log_hex, .-log_hex
.globl log_status
	.type	log_status, @function
log_status:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	pushl	%ebx
	movl	%eax, %ebx
	shrl	$8, %ebx
#APP
	movb $0x02, %ah;xorb %bh, %bh;movw $0x1705, %dx;int $0x10;movb $0x09, %ah;xorb %bh, %bh;movw $1, %cx;int $0x10;
#NO_APP
	popl	%ebx
	popl	%ebp
	ret
	.size	log_status, .-log_status
.globl log_writestring
	.type	log_writestring, @function
log_writestring:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	8(%ebp), %esi
#APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
#NO_APP
	popl	%esi
	popl	%ebp
	ret
	.size	log_writestring, .-log_writestring
	.section	.rodata.str1.1
.LC3:
	.string	"Initializing BIOS Disk Access"
.LC4:
	.string	"Successful Completion"
.LC5:
	.string	"Invalid Function or Parameter"
.LC6:
	.string	"Address Mark Not Found"
.LC7:
	.string	"Disk Write-Protected"
.LC8:
	.string	"Sector Not Found / Read Error"
.LC9:
	.string	"Reset Failed"
.LC10:
	.string	"Disk Changed"
.LC11:
	.string	"Drive Parameter Activity Failed"
.LC12:
	.string	"DMA Overrun"
.LC13:
	.string	"Data Boundary Error"
.LC14:
	.string	"Bad Sector Detected"
.LC15:
	.string	"Bad Track Detected"
.LC16:
	.string	"Unsupported Track or Invalid Media"
.LC17:
	.string	"Invalid Number of Sectors on Format"
.LC18:
	.string	"Control Data Address Mark Detected"
.LC19:
	.string	"DMA Arbitration Level Out of Range"
.LC20:
	.string	"Uncorrectable CRC or ECC Error Detected"
.LC21:
	.string	"Data ECC Corrected"
.LC22:
	.string	"Controller Failure"
.LC23:
	.string	"No Media In Drive"
.LC24:
	.string	"Invalid Drive Type Stored in CMOS"
.LC25:
	.string	"Seek Failed"
.LC26:
	.string	"Timeout"
.LC27:
	.string	"Drive Not Ready"
.LC28:
	.string	"Volume Not Locked in Drive"
.LC29:
	.string	"Volume Locked in Drive"
.LC30:
	.string	"Volume Not Removable"
.LC31:
	.string	"Volume In Use"
.LC32:
	.string	"Lock Count Exceded"
.LC33:
	.string	"Valid Eject Request Failed"
.LC34:
	.string	"Volume Present but Read Protected"
.LC35:
	.string	"Undefined Error"
.LC36:
	.string	"Write Fault"
.LC37:
	.string	"Status Register Error"
.LC38:
	.string	"Sense Operation Failed"
.LC39:
	.string	"Floppy Drives"
.LC40:
	.string	"Hard Drives"
	.text
.globl disk_init
	.type	disk_init, @function
disk_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	$temp_bda, %edi
	pushl	$.LC3
	call	log_item
#APP
	xorw %ax, %ax;movw %ax, %ds;movw $0x0100, %cx;movw $0x0400, %si;rep movsb;movw %es, %ax;movw %ax, %ds;
#NO_APP
	movl	$.LC4, disk_errorcodes
	movl	$.LC5, disk_errorcodes+4
	movl	$.LC6, disk_errorcodes+8
	movl	$.LC7, disk_errorcodes+12
	movl	$.LC8, disk_errorcodes+16
	movl	$.LC9, disk_errorcodes+20
	movl	$.LC10, disk_errorcodes+24
	movl	$.LC11, disk_errorcodes+28
	movl	$.LC12, disk_errorcodes+32
	movl	$.LC13, disk_errorcodes+36
	movl	$.LC14, disk_errorcodes+40
	movl	$.LC15, disk_errorcodes+44
	movl	$.LC16, disk_errorcodes+48
	movl	$.LC17, disk_errorcodes+52
	movl	$.LC18, disk_errorcodes+56
	movl	$.LC19, disk_errorcodes+60
	movl	$.LC20, disk_errorcodes+64
	movl	$.LC21, disk_errorcodes+68
	movl	$.LC22, disk_errorcodes+128
	movl	$.LC23, disk_errorcodes+196
	movl	$.LC24, disk_errorcodes+200
	movl	$.LC25, disk_errorcodes+256
	movl	$.LC26, disk_errorcodes+512
	movl	$.LC27, disk_errorcodes+680
	movl	$.LC28, disk_errorcodes+704
	movl	$.LC29, disk_errorcodes+708
	movl	$.LC30, disk_errorcodes+712
	movl	$.LC31, disk_errorcodes+716
	movl	$.LC32, disk_errorcodes+720
	movl	$.LC33, disk_errorcodes+724
	movl	$.LC34, disk_errorcodes+728
	movl	$.LC35, disk_errorcodes+748
	movl	$.LC36, disk_errorcodes+816
	movl	$.LC37, disk_errorcodes+896
	movl	temp_bda+16, %eax
	movl	$.LC38, disk_errorcodes+1020
	popl	%edi
	testb	$1, %al
	je	.L471
	shrl	$6, %eax
	andl	$3, %eax
	incl	%eax
	movl	%eax, disk_arch_floppydrives
	jmp	.L473
.L471:
	movl	$0, disk_arch_floppydrives
.L473:
	pushl	log_status_success
	movzbl	temp_bda+117, %eax
	movl	%eax, disk_arch_harddrives
	call	log_status
	pushl	disk_arch_floppydrives
	pushl	$.LC39
	call	log_number
	pushl	disk_arch_harddrives
	pushl	$.LC40
	call	log_number
	addl	$20, %esp
	movl	-4(%ebp), %edi
	leave
	ret
	.size	disk_init, .-disk_init
.globl disk_readblock
	.type	disk_readblock, @function
disk_readblock:
	pushl	%ebp
	movl	$513, %eax
	movl	%esp, %ebp
	xorl	%ecx, %ecx
	pushl	%ebx
	xorl	%edx, %edx
	movl	16(%ebp), %ebx
#APP
	stc;int $0x13;sti;
#NO_APP
	popl	%ebx
	popl	%ebp
	ret
	.size	disk_readblock, .-disk_readblock
.globl sys_arch_io_read8
	.type	sys_arch_io_read8, @function
sys_arch_io_read8:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
#APP
	inb %dx, %al;
#NO_APP
	movzbl	%al, %eax
	ret
	.size	sys_arch_io_read8, .-sys_arch_io_read8
.globl sys_arch_io_read16
	.type	sys_arch_io_read16, @function
sys_arch_io_read16:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
#APP
	inw %dx, %ax;
#NO_APP
	movzwl	%ax, %eax
	ret
	.size	sys_arch_io_read16, .-sys_arch_io_read16
.globl sys_arch_io_read32
	.type	sys_arch_io_read32, @function
sys_arch_io_read32:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
#APP
	inl %dx, %eax;
#NO_APP
	ret
	.size	sys_arch_io_read32, .-sys_arch_io_read32
.globl sys_arch_io_write8
	.type	sys_arch_io_write8, @function
sys_arch_io_write8:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movb	12(%ebp), %al
#APP
	outb %al, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_io_write8, .-sys_arch_io_write8
.globl sys_arch_io_write16
	.type	sys_arch_io_write16, @function
sys_arch_io_write16:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
#APP
	outw %ax, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_io_write16, .-sys_arch_io_write16
.globl sys_arch_io_write32
	.type	sys_arch_io_write32, @function
sys_arch_io_write32:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
#APP
	outl %eax, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_io_write32, .-sys_arch_io_write32
.globl sys_arch_kbc_sendcommand
	.type	sys_arch_kbc_sendcommand, @function
sys_arch_kbc_sendcommand:
	pushl	%ebp
	movl	$100, %edx
	movl	%esp, %ebp
	movzbl	8(%ebp), %eax
#APP
	outb %al, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_kbc_sendcommand, .-sys_arch_kbc_sendcommand
.globl sys_arch_kbc_senddata
	.type	sys_arch_kbc_senddata, @function
sys_arch_kbc_senddata:
	pushl	%ebp
	movl	$96, %edx
	movl	%esp, %ebp
	movzbl	8(%ebp), %eax
#APP
	outb %al, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_kbc_senddata, .-sys_arch_kbc_senddata
.globl sys_arch_kbc_readdata
	.type	sys_arch_kbc_readdata, @function
sys_arch_kbc_readdata:
	pushl	%ebp
	movl	$96, %edx
	movl	%esp, %ebp
	popl	%ebp
#APP
	inb %dx, %al;
#NO_APP
	movzbl	%al, %eax
	ret
	.size	sys_arch_kbc_readdata, .-sys_arch_kbc_readdata
.globl sys_arch_kbc_waitsend
	.type	sys_arch_kbc_waitsend, @function
sys_arch_kbc_waitsend:
	pushl	%ebp
	movl	%esp, %ebp
.L497:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L497
	popl	%ebp
	ret
	.size	sys_arch_kbc_waitsend, .-sys_arch_kbc_waitsend
.globl sys_arch_kbc_waitread
	.type	sys_arch_kbc_waitread, @function
sys_arch_kbc_waitread:
	pushl	%ebp
	movl	%esp, %ebp
.L504:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$1, %al
	jne	.L504
	popl	%ebp
	ret
	.size	sys_arch_kbc_waitread, .-sys_arch_kbc_waitread
.globl sys_arch_sig_disable
	.type	sys_arch_sig_disable, @function
sys_arch_sig_disable:
	pushl	%ebp
	movl	%esp, %ebp
#APP
	cli;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_sig_disable, .-sys_arch_sig_disable
.globl sys_arch_sig_enable
	.type	sys_arch_sig_enable, @function
sys_arch_sig_enable:
	pushl	%ebp
	movl	%esp, %ebp
#APP
	sti;
#NO_APP
	popl	%ebp
	ret
	.size	sys_arch_sig_enable, .-sys_arch_sig_enable
.globl a20_test
	.type	a20_test, @function
a20_test:
	pushl	%ebp
#APP
	movb $0x55, 0xFFEF;movw $0xFFFF, %ax;movw %ax, %ds;movb $0xAA, 0xFFFF;xorw %ax, %ax;movw %ax, %ds;movb 0xFFEF, %al;
#NO_APP
	movl	%esp, %ebp
	cmpl	$85, %eax
	popl	%ebp
	sete	%al
	movzbl	%al, %eax
	ret
	.size	a20_test, .-a20_test
.globl a20_enable_vectra
	.type	a20_enable_vectra, @function
a20_enable_vectra:
	pushl	%ebp
	movl	%esp, %ebp
.L516:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L516
	movb	$-83, %al
#APP
	outb %al, %dx;
#NO_APP
.L518:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L518
	movb	$-33, %al
#APP
	outb %al, %dx;
#NO_APP
.L520:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L520
	movb	$-82, %al
#APP
	outb %al, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	a20_enable_vectra, .-a20_enable_vectra
	.section	.rodata.str1.1
.LC41:
	.string	"Enabling A20"
.LC42:
	.string	"Keyboard Controller #1"
.LC43:
	.string	"Vectra"
	.text
.globl a20_enable
	.type	a20_enable, @function
a20_enable:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$.LC41
	call	log_item
#APP
	movb $0x55, 0xFFEF;movw $0xFFFF, %ax;movw %ax, %ds;movb $0xAA, 0xFFFF;xorw %ax, %ax;movw %ax, %ds;movb 0xFFEF, %al;
#NO_APP
	cmpl	$85, %eax
	popl	%edx
	je	.L538
	pushl	$.LC42
	call	log_subitem
#APP
	A20:call empty8042;movb $0xD1, %al;outb %al, $0x64;call empty8042;movb $0xDF, %al;outb %al ,$0x60;call empty8042;jmp argq;empty8042:inb $0x64, %al;testb $0x02, %al;jnz empty8042;ret;argq:
#NO_APP
	movl	$.LC43, (%esp)
	call	log_subitem
	call	a20_enable_vectra
	popl	%eax
	jmp	.L529
.L538:
	pushl	log_status_success
	call	log_status
	popl	%eax
	movl	$1, %eax
.L529:
	leave
	ret
	.size	a20_enable, .-a20_enable
.globl a20_enable_ps2
	.type	a20_enable_ps2, @function
a20_enable_ps2:
	pushl	%ebp
	movl	%esp, %ebp
#APP
	movl $0x2401, %eax; int $0x15;
#NO_APP
	popl	%ebp
	ret
	.size	a20_enable_ps2, .-a20_enable_ps2
.globl a20_enable_kbc1
	.type	a20_enable_kbc1, @function
a20_enable_kbc1:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	a20_enable_kbc1, .-a20_enable_kbc1
	.section	.rodata.str1.1
.LC44:
	.string	"AX"
	.text
.globl memory_detect_0088
	.type	memory_detect_0088, @function
memory_detect_0088:
	movl	$136, %edx
	pushl	%ebp
	movl	%edx, %eax
#APP
	stc;int $0x15;movl $0, %ecx;jnc 1f;movl $1, %ecx;1:
#NO_APP
	testl	%ecx, %ecx
	movl	%esp, %ebp
	jne	.L547
	andl	$65535, %eax
	pushl	%eax
	pushl	$.LC44
	call	log_hex
	popl	%ecx
	popl	%eax
	jmp	.L546
.L547:
	xorl	%eax, %eax
.L546:
	leave
	ret
	.size	memory_detect_0088, .-memory_detect_0088
	.section	.rodata.str1.1
.LC45:
	.string	"BX"
.LC46:
	.string	"CL"
	.text
.globl memory_detect_da88
	.type	memory_detect_da88, @function
memory_detect_da88:
	pushl	%ebp
	movl	$55944, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
#APP
	stc;int $0x15;movl $0, %eax;jnc 1f;movl $1, %eax;1:
#NO_APP
	testl	%eax, %eax
	movl	%ecx, %esi
	jne	.L552
	movzwl	%bx,%eax
	pushl	%eax
	pushl	$.LC45
	call	log_hex
	movl	%esi, %eax
	andl	$255, %eax
	pushl	%eax
	pushl	$.LC46
	call	log_hex
	addl	$16, %esp
	jmp	.L551
.L552:
	xorl	%eax, %eax
.L551:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	memory_detect_da88, .-memory_detect_da88
	.section	.rodata.str1.1
.LC47:
	.string	"DX"
	.text
.globl memory_detect_008a
	.type	memory_detect_008a, @function
memory_detect_008a:
	pushl	%ebp
	movl	$138, %ecx
	movl	%esp, %ebp
	movl	%ecx, %eax
	pushl	%esi
	pushl	%ebx
	xorl	%ebx, %ebx
	movl	%ebx, %edx
#APP
	stc;int $0x15;movl $0, %ecx;jnc 1f;movl $1, %ecx;1:
#NO_APP
	testl	%ecx, %ecx
	movl	%edx, %ebx
	jne	.L557
	andl	$65535, %eax
	pushl	%eax
	pushl	$.LC44
	call	log_hex
	movzwl	%bx,%eax
	pushl	%eax
	pushl	$.LC47
	call	log_hex
	addl	$16, %esp
	jmp	.L556
.L557:
	xorl	%eax, %eax
.L556:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	memory_detect_008a, .-memory_detect_008a
	.section	.rodata.str1.1
.LC48:
	.string	"C7"
	.text
.globl memory_detect_00c7
	.type	memory_detect_00c7, @function
memory_detect_00c7:
	pushl	%ebp
	movl	$192, %eax
	movl	%esp, %ebp
	pushl	%esi
	subl	$48, %esp
#APP
	stc;int $0x15;movl $0, %eax;jc 2f;testb $10, %es:6(%bx);jnc 2f;1:movl $1, %eax;2:
#NO_APP
	testl	%eax, %eax
	je	.L559
	movl	$199, %eax
	leal	-46(%ebp), %esi
#APP
	clc;int $0x15;movl $0, %eax;jnc 1f;movl $1, %eax;1:
#NO_APP
	testl	%eax, %eax
	jne	.L559
	movzbl	-46(%ebp), %eax
	pushl	%eax
	pushl	$.LC48
	call	log_hex
	jmp	.L558
.L559:
	xorl	%eax, %eax
.L558:
	movl	-4(%ebp), %esi
	leave
	ret
	.size	memory_detect_00c7, .-memory_detect_00c7
	.section	.rodata.str1.1
.LC49:
	.string	"CX"
	.text
.globl memory_detect_e801
	.type	memory_detect_e801, @function
memory_detect_e801:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	$59393, %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	subl	$8, %esp
	movl	%esi, %eax
	movl	%ebx, %ecx
	movl	%ebx, %edx
#APP
	stc;int $0x15;movl $0, -16(%ebp);jnc 1f;movl $1, -16(%ebp);1:
#NO_APP
	cmpl	$0, -16(%ebp)
	movl	%edx, %edi
	movl	%ecx, %esi
	movl	%eax, -20(%ebp)
	jne	.L567
	andl	$65535, %eax
	pushl	%eax
	pushl	$.LC44
	call	log_hex
	movzwl	%bx,%eax
	pushl	%eax
	pushl	$.LC45
	call	log_hex
	movl	%esi, %eax
	andl	$65535, %eax
	pushl	%eax
	pushl	$.LC49
	call	log_hex
	movl	%edi, %eax
	andl	$65535, %eax
	pushl	%eax
	pushl	$.LC47
	call	log_hex
	addl	$32, %esp
	jmp	.L566
.L567:
	xorl	%eax, %eax
.L566:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	memory_detect_e801, .-memory_detect_e801
	.section	.rodata.str1.1
.LC50:
	.string	"Detecting Memory"
.LC51:
	.string	"E820 NOT SUPPORTED! SYSTEM HALTED!"
.LC52:
	.string	"Identifier"
.LC53:
	.string	"  Base"
.LC54:
	.string	"  Lenght"
.LC55:
	.string	"  Type"
	.text
.globl memory_detect_e820
	.type	memory_detect_e820, @function
memory_detect_e820:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	pushl	$.LC50
	call	log_item
	leal	-32(%ebp), %edi
	xorl	%eax, %eax
	cld
	stosl
	stosl
	stosl
	stosl
	stosl
	movl	$0, -48(%ebp)
	popl	%eax
.L569:
	movl	$59424, %eax
	movl	$20, %ecx
	movl	-48(%ebp), %ebx
	movl	$1397571920, %edx
	leal	-32(%ebp), %edi
#APP
	clc;int $0x15;movl $0, %edi;jnc 1f;movl $1, %edi;1:
#NO_APP
	testl	%edi, %edi
	je	.L570
	andl	$65280, %eax
	cmpl	$34304, %eax
	jne	.L572
	pushl	$.LC51
	call	log_item
	popl	%eax
.L574:
	jmp	.L574
.L570:
	pushl	-48(%ebp)
	pushl	$.LC52
	call	log_hex
	pushl	-32(%ebp)
	pushl	$.LC53
	call	log_hex
	pushl	-24(%ebp)
	pushl	$.LC54
	call	log_hex
	pushl	-16(%ebp)
	pushl	$.LC55
	call	log_hex
	addl	$32, %esp
	movl	%ebx, -48(%ebp)
.L572:
	orl	-48(%ebp), %edi
	jne	.L569
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	memory_detect_e820, .-memory_detect_e820
	.section	.rodata.str1.1
.LC56:
	.string	"Found ROM"
.LC57:
	.string	"Size"
	.text
.globl memory_findroms
	.type	memory_findroms, @function
memory_findroms:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	$49152, %esi
	pushl	%ebx
.L580:
	movl	%esi, %eax
#APP
	movw %ax, %es;movl %es:0, %edx;movw %ds, %ax;movw %ax, %es;
#NO_APP
	cmpw	$-21931, %dx
	movl	%edx, %ebx
	jne	.L581
	pushl	%esi
	shrl	$7, %ebx
	pushl	$.LC56
	andl	$130560, %ebx
	call	log_hex
	pushl	%ebx
	pushl	$.LC57
	call	log_dec
	addl	$16, %esp
.L581:
	subl	$-128, %esi
	cmpl	$65536, %esi
	jne	.L580
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	memory_findroms, .-memory_findroms
	.section	.rodata.str1.1
.LC58:
	.string	"E820"
.LC59:
	.string	"E801"
.LC60:
	.string	"008A"
.LC61:
	.string	"DA88"
.LC62:
	.string	"0088"
.LC63:
	.string	"00C7"
.LC64:
	.string	"IN12"
	.text
.globl memory_detect
	.type	memory_detect, @function
memory_detect:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$.LC58
	call	log_item
	call	memory_detect_e820
	pushl	$.LC59
	call	log_item
	call	memory_detect_e801
	pushl	$.LC60
	call	log_item
	call	memory_detect_008a
	pushl	$.LC61
	call	log_item
	call	memory_detect_da88
	pushl	$.LC62
	call	log_item
	call	memory_detect_0088
	pushl	$.LC63
	call	log_item
	call	memory_detect_00c7
	pushl	$.LC64
	call	log_item
	call	memory_findroms
	xorl	%eax, %eax
	leave
	ret
	.size	memory_detect, .-memory_detect
.globl ibm_init
	.type	ibm_init, @function
ibm_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	ibm_init, .-ibm_init
.globl trifs_init
	.type	trifs_init, @function
trifs_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	trifs_init, .-trifs_init
.globl fat_init
	.type	fat_init, @function
fat_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	fat_init, .-fat_init
.globl ext2_init
	.type	ext2_init, @function
ext2_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	ext2_init, .-ext2_init
.globl disk_read
	.type	disk_read, @function
disk_read:
	pushl	%ebp
	movl	$36, %ecx
	movl	%esp, %ebp
	xorl	%edx, %edx
	pushl	%edi
	movl	$513, %edi
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ebx
	divl	%ecx
	movb	$18, %cl
	movl	%eax, %esi
	movl	%edx, %eax
	xorl	%edx, %edx
	divl	%ecx
	sall	$8, %esi
	leal	1(%edx,%esi), %ecx
	movl	16(%ebp), %edx
	sall	$8, %eax
	movl	%eax, -16(%ebp)
	addl	%edx, %eax
	movl	%eax, %edx
	movl	%edi, %eax
#APP
	stc;int $0x13;sti;jnc disk_read_done;xorw $0, %ax;disk_read_done:
#NO_APP
	popl	%edx
	movl	%eax, %ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	shrl	$8, %ecx
	movl	%ecx, %eax
	ret
	.size	disk_read, .-disk_read
	.section	.rodata.str1.1
.LC65:
	.string	"Loading Core"
.LC66:
	.string	"Loading Root"
.LC67:
	.string	"Loading Test"
.LC68:
	.string	"Loading Ping"
.LC69:
	.string	"Loading Pong"
	.text
.globl trifs_load
	.type	trifs_load, @function
trifs_load:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	$.LC65
	call	log_item
	movb	trifs_buffer+56, %bl
	xorl	%edx, %edx
	popl	%esi
	jmp	.L600
.L601:
	andl	$255, %edi
	movl	$256, %ecx
	movl	$trifs_buffer, %esi
	sall	$9, %edi
#APP
	movw $0x2000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
#NO_APP
.L600:
	movzbl	%bl, %eax
	movl	%edx, %edi
	incl	%eax
	incl	%edx
	cmpl	%eax, %edx
	jne	.L601
	pushl	log_status_success
	call	log_status
	pushl	$.LC66
	call	log_item
	movb	trifs_buffer+88, %bl
	xorl	%edx, %edx
	popl	%eax
	popl	%ecx
	jmp	.L603
.L604:
	andl	$255, %edi
	movl	$256, %ecx
	movl	$trifs_buffer, %esi
	sall	$9, %edi
#APP
	movw $0x6000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
#NO_APP
.L603:
	movzbl	%bl, %eax
	movl	%edx, %edi
	incl	%eax
	incl	%edx
	cmpl	%eax, %edx
	jne	.L604
	pushl	log_status_success
	call	log_status
	pushl	$.LC67
	call	log_item
	movb	trifs_buffer+120, %bl
	xorl	%edx, %edx
	popl	%esi
	popl	%edi
	jmp	.L606
.L607:
	andl	$255, %edi
	movl	$256, %ecx
	movl	$trifs_buffer, %esi
	sall	$9, %edi
#APP
	movw $0x7000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
#NO_APP
.L606:
	movzbl	%bl, %eax
	movl	%edx, %edi
	incl	%eax
	incl	%edx
	cmpl	%eax, %edx
	jne	.L607
	pushl	log_status_success
	call	log_status
	pushl	$.LC68
	call	log_item
	movb	trifs_buffer+152, %bl
	xorl	%edx, %edx
	popl	%eax
	popl	%ecx
	jmp	.L609
.L610:
	andl	$255, %edi
	movl	$256, %ecx
	movl	$trifs_buffer, %esi
	sall	$9, %edi
#APP
	movw $0x8000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
#NO_APP
.L609:
	movzbl	%bl, %eax
	movl	%edx, %edi
	incl	%eax
	incl	%edx
	cmpl	%eax, %edx
	jne	.L610
	pushl	log_status_success
	call	log_status
	pushl	$.LC69
	call	log_item
	movb	trifs_buffer+184, %bl
	xorl	%edx, %edx
	popl	%esi
	popl	%edi
	jmp	.L612
.L613:
	andl	$255, %edi
	movl	$256, %ecx
	movl	$trifs_buffer, %esi
	sall	$9, %edi
#APP
	movw $0x8800, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
#NO_APP
.L612:
	movzbl	%bl, %eax
	movl	%edx, %edi
	incl	%eax
	incl	%edx
	cmpl	%eax, %edx
	jne	.L613
	pushl	log_status_success
	call	log_status
	popl	%ecx
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	trifs_load, .-trifs_load
	.section	.rodata.str1.1
.LC70:
	.string	"Disk Contents"
	.text
.globl trifs_list
	.type	trifs_list, @function
trifs_list:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	$trifs_buffer, %ebx
	pushl	$.LC70
	call	log_item
	pushl	log_status_success
	call	log_status
	popl	%eax
	popl	%edx
.L617:
	cmpb	$0, (%ebx)
	je	.L618
	pushl	%ebx
	call	log_subitem
	popl	%eax
.L618:
	addl	$32, %ebx
	cmpl	$trifs_buffer+512, %ebx
	jne	.L617
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	trifs_list, .-trifs_list
.globl init8259
	.type	init8259, @function
init8259:
	pushl	%ebp
	movl	%esp, %ebp
#APP
	mov $0x11, %al;out %al, $0x20;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA0;/*jmp .+2;*//*jmp .+2;*/mov $0x20, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x28, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x04, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x02, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x01, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x00, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/
#NO_APP
	popl	%ebp
	ret
	.size	init8259, .-init8259
	.section	.rodata.str1.1
.LC71:
	.string	"Initializing Repository"
.LC72:
	.string	"Trinary File System"
.LC73:
	.string	"FAT12 / FAT16 / FAT32"
.LC74:
	.string	"Ext2 FS"
	.text
.globl entry
	.type	entry, @function
entry:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$.LC71
	call	log_item
	pushl	log_status_success
	call	log_status
	pushl	$.LC72
	call	log_subitem
	pushl	$.LC73
	call	log_subitem
	pushl	$.LC74
	call	log_subitem
	pushl	$4096
	pushl	$53248
	call	heap_init
	call	disk_init
	call	trifs_list
	call	trifs_load
	call	memory_detect
#APP
	movw $0x03F2, %dx;xorb %al, %al;outb %al, %dx;cli;
#NO_APP
	pushl	$0
	call	a20_enable
#APP
	mov $0x11, %al;out %al, $0x20;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA0;/*jmp .+2;*//*jmp .+2;*/mov $0x20, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x28, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x04, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x02, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x01, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x00, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/
#NO_APP
	movw	$-21555, idt48
	movl	$305419896, idt48+2
	movw	$2048, gdt48
	movl	$gdt, gdt48+2
	movb	$0, gdt+4
	movb	$0, gdt+7
	movw	$0, gdt+2
	movw	$0, gdt
	movb	$0, gdt+5
	movb	$0, gdt+6
	movb	$0, gdt+20
	movb	$0, gdt+23
	movw	$0, gdt+18
	movw	$-1, gdt+16
	movb	$-102, gdt+21
	movb	$-49, gdt+22
	movb	$0, gdt+28
	movb	$0, gdt+31
	movw	$0, gdt+26
	movw	$-1, gdt+24
	movb	$-110, gdt+29
	movb	$-49, gdt+30
#APP
	lidt idt48;lgdt gdt48;
#NO_APP
	movl	$Aye, %edx
#APP
	movl %edx, code32start;xorl %eax, %eax;movl %eax, %cr3;movl %cr0, %eax;orl $0x00000001, %eax;movl %eax, %cr0;jmp flush;flush:.byte 0x66, 0xea;code32start: .long 0x10000;.word 0x0010;cli; hlt;
#NO_APP
	addl	$32, %esp
	leave
	ret
	.size	entry, .-entry
.globl heap_allocaligned
	.type	heap_allocaligned, @function
heap_allocaligned:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%ebx
	movl	heap_pointer, %ebx
	movl	%ebx, %eax
	divl	12(%ebp)
	testl	%edx, %edx
	je	.L629
	leal	(%ebx,%edx), %eax
	movl	%eax, heap_pointer
.L629:
	movl	8(%ebp), %eax
	addl	%eax, heap_pointer
	popl	%ebx
	popl	%ebp
	ret
	.size	heap_allocaligned, .-heap_allocaligned
.globl a20_enable_kbc2
	.type	a20_enable_kbc2, @function
a20_enable_kbc2:
	pushl	%ebp
	movl	%esp, %ebp
.L633:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L633
	movb	$-83, %al
#APP
	outb %al, %dx;
#NO_APP
.L635:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L635
	movb	$-48, %al
#APP
	outb %al, %dx;
#NO_APP
.L637:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$1, %al
	jne	.L637
	movb	$96, %dl
#APP
	inb %dx, %al;
#NO_APP
	movzbl	%al, %ecx
.L639:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L639
	movb	$-47, %al
#APP
	outb %al, %dx;
#NO_APP
.L641:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L641
	orl	$2, %ecx
	movb	$96, %dl
	movb	%cl, %al
#APP
	outb %al, %dx;
#NO_APP
.L643:
	movl	$100, %edx
#APP
	inb %dx, %al;
#NO_APP
	testb	$2, %al
	jne	.L643
	movb	$-82, %al
#APP
	outb %al, %dx;
#NO_APP
	popl	%ebp
	ret
	.size	a20_enable_kbc2, .-a20_enable_kbc2
.globl log_status_success
	.data
	.align 4
	.type	log_status_success, @object
	.size	log_status_success, 4
log_status_success:
	.long	2811
	.align 4
	.type	holdrand, @object
	.size	holdrand, 4
holdrand:
	.long	1
	.comm	heap_pointer,4,4
	.comm	heap_end,4,4
	.comm	disk_errorcodes,1024,32
	.comm	disk_arch_harddrives,4,4
	.comm	disk_arch_floppydrives,4,4
	.comm	temp_bda,256,32
	.comm	disk_idlist,1024,32
	.comm	trifs_buffer,512,32
	.comm	idt48,6,1
	.comm	gdt48,6,1
	.comm	gdt,24,1
	.comm	debugdata,8,8
	.ident	"GCC: (GNU) 4.1.3 20070929 (prerelease) (Ubuntu 4.1.2-16ubuntu2)"
	.section	.note.GNU-stack,"",@progbits
