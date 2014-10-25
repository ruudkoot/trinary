	.file	"init.c"
	.text
	.align 2
.globl _isalnum
	.def	_isalnum;	.scl	2;	.type	32;	.endef
_isalnum:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	L3
	leal	-97(%edx), %eax
	cmpb	$25, %al
	jbe	L3
	leal	-49(%edx), %eax
	cmpb	$8, %al
	ja	L2
L3:
	movl	$1, %ecx
L2:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _isalpha
	.def	_isalpha;	.scl	2;	.type	32;	.endef
_isalpha:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	L6
	leal	-97(%edx), %eax
	cmpb	$25, %al
	ja	L5
L6:
	movl	$1, %ecx
L5:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _iscsym
	.def	_iscsym;	.scl	2;	.type	32;	.endef
_iscsym:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	L9
	leal	-97(%edx), %eax
	cmpb	$25, %al
	jbe	L9
	leal	-48(%edx), %eax
	cmpb	$9, %al
	jbe	L9
	cmpb	$95, %dl
	je	L9
L8:
	movl	%ecx, %eax
	popl	%ebp
	ret
L9:
	movl	$1, %ecx
	jmp	L8
	.align 2
.globl _iscsymf
	.def	_iscsymf;	.scl	2;	.type	32;	.endef
_iscsymf:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	jbe	L12
	leal	-97(%edx), %eax
	cmpb	$25, %al
	jbe	L12
	cmpb	$95, %dl
	je	L12
L11:
	movl	%ecx, %eax
	popl	%ebp
	ret
L12:
	movl	$1, %ecx
	jmp	L11
	.align 2
.globl _isctrl
	.def	_isctrl;	.scl	2;	.type	32;	.endef
_isctrl:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$32, %eax
	cmpb	$94, %al
	seta	%al
	movzbl	%al, %eax
	ret
	.align 2
.globl _isdigit
	.def	_isdigit;	.scl	2;	.type	32;	.endef
_isdigit:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$48, %eax
	cmpb	$9, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.align 2
.globl _islowwer
	.def	_islowwer;	.scl	2;	.type	32;	.endef
_islowwer:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$97, %eax
	cmpb	$25, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.align 2
.globl _isprint
	.def	_isprint;	.scl	2;	.type	32;	.endef
_isprint:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$32, %eax
	cmpb	$94, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.align 2
.globl _ispunct
	.def	_ispunct;	.scl	2;	.type	32;	.endef
_ispunct:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-33(%edx), %eax
	cmpb	$14, %al
	jbe	L19
	leal	-58(%edx), %eax
	cmpb	$6, %al
	jbe	L19
	leal	-91(%edx), %eax
	cmpb	$5, %al
	jbe	L19
	leal	-123(%edx), %eax
	cmpb	$3, %al
	ja	L18
L19:
	movl	$1, %ecx
L18:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _isspace
	.def	_isspace;	.scl	2;	.type	32;	.endef
_isspace:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	movb	8(%ebp), %al
	cmpb	$32, %al
	je	L22
	subl	$9, %eax
	cmpb	$4, %al
	ja	L21
L22:
	movl	$1, %edx
L21:
	movl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _isupper
	.def	_isupper;	.scl	2;	.type	32;	.endef
_isupper:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %al
	popl	%ebp
	subl	$65, %eax
	cmpb	$25, %al
	setbe	%al
	movzbl	%al, %eax
	ret
	.align 2
.globl _isxdigit
	.def	_isxdigit;	.scl	2;	.type	32;	.endef
_isxdigit:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-48(%edx), %eax
	cmpb	$9, %al
	jbe	L26
	leal	-97(%edx), %eax
	cmpb	$5, %al
	jbe	L26
	leal	-65(%edx), %eax
	cmpb	$5, %al
	ja	L25
L26:
	movl	$1, %ecx
L25:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _tolower
	.def	_tolower;	.scl	2;	.type	32;	.endef
_tolower:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	leal	-65(%edx), %eax
	cmpl	$25, %eax
	ja	L28
	addl	$32, %edx
L28:
	movl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _toupper
	.def	_toupper;	.scl	2;	.type	32;	.endef
_toupper:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	leal	-97(%edx), %eax
	cmpl	$25, %eax
	ja	L30
	subl	$32, %edx
L30:
	movl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _i16toa
	.def	_i16toa;	.scl	2;	.type	32;	.endef
_i16toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%edx
	movl	8(%ebp), %ebx
	movb	16(%ebp), %al
	testw	%bx, %bx
	movb	%al, -9(%ebp)
	movl	12(%ebp), %ecx
	js	L44
L32:
	movl	%ecx, %esi
L33:
	movswl	%bx,%eax
	movzbl	-9(%ebp), %edx
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	movl	%eax, %ebx
	cmpb	$9, %dl
	leal	55(%edx), %eax
	jg	L43
	leal	48(%edx), %eax
L43:
	movb	%al, (%ecx)
	incl	%ecx
	testw	%bx, %bx
	jg	L33
	movb	$0, (%ecx)
	decl	%ecx
L39:
	movb	(%ecx), %dl
	movb	(%esi), %al
	movb	%al, (%ecx)
	decl	%ecx
	movb	%dl, (%esi)
	incl	%esi
	cmpl	%ecx, %esi
	jb	L39
	popl	%eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L44:
	movb	$45, (%ecx)
	incl	%ecx
	negl	%ebx
	jmp	L32
	.align 2
.globl _i32toa
	.def	_i32toa;	.scl	2;	.type	32;	.endef
_i32toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	8(%ebp), %edx
	movb	16(%ebp), %al
	movb	%al, -9(%ebp)
	movl	12(%ebp), %ecx
	testl	%edx, %edx
	js	L58
L46:
	movl	%ecx, %ebx
L47:
	movl	%edx, %eax
	movzbl	-9(%ebp), %esi
	cltd
	idivl	%esi
	movl	%eax, %esi
	movb	%dl, %al
	cmpb	$9, %al
	movl	%esi, %edx
	jle	L50
	addl	$55, %eax
L57:
	movb	%al, (%ecx)
	incl	%ecx
	testl	%esi, %esi
	jg	L47
	movb	$0, (%ecx)
	decl	%ecx
L53:
	movb	(%ecx), %dl
	movb	(%ebx), %al
	movb	%al, (%ecx)
	decl	%ecx
	movb	%dl, (%ebx)
	incl	%ebx
	cmpl	%ecx, %ebx
	jb	L53
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L50:
	addl	$48, %eax
	jmp	L57
L58:
	movb	$45, (%ecx)
	incl	%ecx
	negl	%edx
	jmp	L46
	.align 2
.globl _u16toa
	.def	_u16toa;	.scl	2;	.type	32;	.endef
_u16toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movb	16(%ebp), %al
	movl	12(%ebp), %ecx
	movl	8(%ebp), %ebx
	movb	%al, -9(%ebp)
	movl	%ecx, %esi
L60:
	movzwl	%bx, %eax
	movzbl	-9(%ebp), %edx
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	movl	%eax, %ebx
	cmpb	$9, %dl
	leal	55(%edx), %eax
	jg	L70
	leal	48(%edx), %eax
L70:
	movb	%al, (%ecx)
	incl	%ecx
	testw	%bx, %bx
	jne	L60
	movb	$0, (%ecx)
	decl	%ecx
L66:
	movb	(%ecx), %dl
	movb	(%esi), %al
	movb	%al, (%ecx)
	decl	%ecx
	movb	%dl, (%esi)
	incl	%esi
	cmpl	%ecx, %esi
	jb	L66
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _u32toa
	.def	_u32toa;	.scl	2;	.type	32;	.endef
_u32toa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movb	16(%ebp), %al
	movl	12(%ebp), %ecx
	movb	%al, -13(%ebp)
	movl	%ecx, %ebx
L72:
	movzbl	-13(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %edi
	xorl	%edx, %edx
	divl	%edi
	movl	%eax, %esi
	cmpb	$9, %dl
	movb	%dl, %al
	movl	%esi, 8(%ebp)
	jle	L75
	addl	$55, %eax
L82:
	movb	%al, (%ecx)
	incl	%ecx
	testl	%esi, %esi
	jne	L72
	movb	$0, (%ecx)
	decl	%ecx
L78:
	movb	(%ecx), %dl
	movb	(%ebx), %al
	movb	%al, (%ecx)
	decl	%ecx
	movb	%dl, (%ebx)
	incl	%ebx
	cmpl	%ecx, %ebx
	jb	L78
	popl	%eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L75:
	addl	$48, %eax
	jmp	L82
	.align 2
.globl _abs
	.def	_abs;	.scl	2;	.type	32;	.endef
_abs:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	js	L85
L84:
	popl	%ebp
	ret
L85:
	negl	%eax
	jmp	L84
	.align 2
.globl _max
	.def	_max;	.scl	2;	.type	32;	.endef
_max:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jge	L87
	movl	8(%ebp), %eax
L87:
	popl	%ebp
	ret
	.align 2
.globl _min
	.def	_min;	.scl	2;	.type	32;	.endef
_min:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	L89
	movl	8(%ebp), %eax
L89:
	popl	%ebp
	ret
	.align 2
.globl _rotl
	.def	_rotl;	.scl	2;	.type	32;	.endef
_rotl:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	andl	$31, %edx
	decl	%edx
	cmpl	$-1, %edx
	je	L97
L95:
	movl	%ecx, %eax
	addl	%ecx, %ecx
	andl	$-2147483648, %eax
	testl	%eax, %eax
	je	L91
	orl	$1, %ecx
L91:
	decl	%edx
	cmpl	$-1, %edx
	jne	L95
L97:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _rotr
	.def	_rotr;	.scl	2;	.type	32;	.endef
_rotr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	andl	$31, %edx
	decl	%edx
	cmpl	$-1, %edx
	je	L105
L103:
	movl	%ecx, %eax
	shrl	%ecx
	andl	$1, %eax
	testl	%eax, %eax
	je	L99
	orl	$-2147483648, %ecx
L99:
	decl	%edx
	cmpl	$-1, %edx
	jne	L103
L105:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _memccpy
	.def	_memccpy;	.scl	2;	.type	32;	.endef
_memccpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	20(%ebp), %ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	testl	%ebx, %ebx
	je	L112
	incl	%ecx
	incl	%edx
	movb	-1(%ecx), %al
	movb	%al, -1(%edx)
	cmpb	16(%ebp), %al
	je	L108
L111:
	decl	%ebx
	je	L112
	incl	%ecx
	incl	%edx
	movb	-1(%ecx), %al
	movb	%al, -1(%edx)
	cmpb	16(%ebp), %al
	jne	L111
L108:
	movl	%edx, %eax
	testl	%ebx, %ebx
	jne	L113
L112:
	xorl	%eax, %eax
L113:
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _memchr
	.def	_memchr;	.scl	2;	.type	32;	.endef
_memchr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %edx
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	testl	%edx, %edx
	je	L121
	cmpb	%cl, (%eax)
	je	L117
L120:
	incl	%eax
	decl	%edx
	je	L121
	cmpb	%cl, (%eax)
	jne	L120
L117:
	testl	%edx, %edx
	jne	L122
L121:
	xorl	%eax, %eax
L122:
	popl	%ebp
	ret
	.align 2
.globl _memcmp
	.def	_memcmp;	.scl	2;	.type	32;	.endef
_memcmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	xorl	%esi, %esi
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx
	testl	%edx, %edx
	je	L124
	decl	%edx
	je	L127
	movb	(%ebx), %al
	cmpb	%al, (%ecx)
	je	L130
L127:
	movzbl	(%ecx), %esi
	movzbl	(%ebx), %eax
	subl	%eax, %esi
L124:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
L130:
	incl	%ecx
	incl	%ebx
	decl	%edx
	je	L127
	movb	(%ebx), %al
	cmpb	%al, (%ecx)
	je	L130
	jmp	L127
	.align 2
.globl _memcpy
	.def	_memcpy;	.scl	2;	.type	32;	.endef
_memcpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	decl	%edx
	movl	12(%ebp), %ebx
	movl	%ecx, %esi
	cmpl	$-1, %edx
	je	L138
L136:
	movb	(%ebx), %al
	decl	%edx
	movb	%al, (%ecx)
	incl	%ebx
	incl	%ecx
	cmpl	$-1, %edx
	jne	L136
L138:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _memcpybw
	.def	_memcpybw;	.scl	2;	.type	32;	.endef
_memcpybw:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	decl	%edx
	movl	12(%ebp), %ebx
	movl	%ecx, %esi
	cmpl	$-1, %edx
	je	L145
L143:
	movb	(%ebx), %al
	decl	%edx
	movb	%al, (%ecx)
	incl	%ebx
	addl	$2, %ecx
	cmpl	$-1, %edx
	jne	L143
L145:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl __memicmp
	.def	__memicmp;	.scl	2;	.type	32;	.endef
__memicmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%ecx
	movl	16(%ebp), %ecx
	movl	8(%ebp), %edi
	decl	%ecx
	movl	12(%ebp), %esi
	movl	$0, -16(%ebp)
	cmpl	$-1, %ecx
	je	L148
L155:
	movb	(%edi), %al
	movb	(%esi), %dl
	cmpb	%dl, %al
	je	L151
	movzbl	%al, %ebx
	subl	$65, %eax
	cmpb	$25, %al
	ja	L152
	addl	$32, %ebx
L152:
	movzbl	%dl, %eax
	movl	%eax, -16(%ebp)
	leal	-65(%edx), %eax
	cmpb	$25, %al
	ja	L153
	addl	$32, -16(%ebp)
L153:
	cmpl	-16(%ebp), %ebx
	jne	L148
L151:
	decl	%ecx
	incl	%edi
	incl	%esi
	cmpl	$-1, %ecx
	jne	L155
L148:
	subl	-16(%ebp), %ebx
	popl	%edx
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _memmove
	.def	_memmove;	.scl	2;	.type	32;	.endef
_memmove:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	12(%ebp), %ecx
	movl	8(%ebp), %ebx
	movl	16(%ebp), %edx
	movl	%ebx, %esi
	cmpl	%ecx, %ebx
	jbe	L159
	leal	(%edx,%ecx), %eax
	cmpl	%eax, %ebx
	jb	L158
L159:
	decl	%edx
	cmpl	$-1, %edx
	je	L164
L163:
	movb	(%ecx), %al
	decl	%edx
	movb	%al, (%ebx)
	incl	%ecx
	incl	%ebx
	cmpl	$-1, %edx
	jne	L163
L164:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
L158:
	leal	-1(%edx,%ebx), %ebx
	leal	-1(%edx,%ecx), %ecx
	decl	%edx
	cmpl	$-1, %edx
	je	L164
L168:
	movb	(%ecx), %al
	decl	%edx
	movb	%al, (%ebx)
	decl	%ecx
	decl	%ebx
	cmpl	$-1, %edx
	jne	L168
	jmp	L164
	.align 2
.globl _memset
	.def	_memset;	.scl	2;	.type	32;	.endef
_memset:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	decl	%edx
	movl	12(%ebp), %ebx
	movl	%ecx, %eax
	cmpl	$-1, %edx
	je	L177
L175:
	decl	%edx
	movb	%bl, (%ecx)
	incl	%ecx
	cmpl	$-1, %edx
	jne	L175
L177:
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _memsetw
	.def	_memsetw;	.scl	2;	.type	32;	.endef
_memsetw:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	decl	%edx
	movl	12(%ebp), %eax
	movl	%ecx, %ebx
	cmpl	$-1, %edx
	je	L184
L182:
	movw	%ax, (%ecx)
	decl	%edx
	addl	$2, %ecx
	cmpl	$-1, %edx
	jne	L182
L184:
	movl	%ebx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _swab
	.def	_swab;	.scl	2;	.type	32;	.endef
_swab:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	16(%ebp), %esi
	movl	12(%ebp), %ecx
	movl	8(%ebp), %ebx
	cmpl	$1, %esi
	jle	L191
L189:
	movb	(%ebx), %dl
	subl	$2, %esi
	incl	%ebx
	movb	(%ebx), %al
	incl	%ebx
	movb	%al, (%ecx)
	incl	%ecx
	movb	%dl, (%ecx)
	incl	%ecx
	cmpl	$1, %esi
	jg	L189
L191:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _strcat
	.def	_strcat;	.scl	2;	.type	32;	.endef
_strcat:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	%edx, %ebx
	cmpb	$0, (%edx)
	je	L197
L196:
	incl	%edx
	cmpb	$0, (%edx)
	jne	L196
L197:
	movb	(%ecx), %al
	incl	%ecx
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	jne	L197
	movl	%ebx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _strncat
	.def	_strncat;	.scl	2;	.type	32;	.endef
_strncat:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	12(%ebp), %ebx
	movl	%edx, %esi
L202:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	L202
	decl	%ecx
	decl	%edx
	cmpl	$-1, %ecx
	je	L211
L209:
	movb	(%ebx), %al
	incl	%ebx
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	je	L201
	decl	%ecx
	cmpl	$-1, %ecx
	jne	L209
L211:
	movb	$0, (%edx)
L201:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _strchr
	.def	_strchr;	.scl	2;	.type	32;	.endef
_strchr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movb	(%eax), %dl
	testb	%dl, %dl
	je	L214
	cmpb	%cl, %dl
	je	L214
L217:
	incl	%eax
	movb	(%eax), %dl
	testb	%dl, %dl
	je	L214
	cmpb	%cl, %dl
	jne	L217
L214:
	cmpb	%cl, (%eax)
	je	L212
	xorl	%eax, %eax
L212:
	popl	%ebp
	ret
	.align 2
.globl _strcmp
	.def	_strcmp;	.scl	2;	.type	32;	.endef
_strcmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	12(%ebp), %ebx
	movl	8(%ebp), %esi
	movb	(%ebx), %cl
	movzbl	%cl, %eax
	movzbl	(%esi), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	jne	L222
	testb	%cl, %cl
	je	L222
L225:
	incl	%ebx
	incl	%esi
	movb	(%ebx), %cl
	movzbl	%cl, %eax
	movzbl	(%esi), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	jne	L222
	testb	%cl, %cl
	jne	L225
L222:
	testl	%eax, %eax
	js	L230
	testl	%eax, %eax
	jle	L227
	movl	$1, %eax
L227:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L230:
	orl	$-1, %eax
	jmp	L227
	.align 2
.globl _strcpy
	.def	_strcpy;	.scl	2;	.type	32;	.endef
_strcpy:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
L232:
	movb	(%ecx), %al
	incl	%ecx
	movb	%al, (%edx)
	incl	%edx
	testb	%al, %al
	jne	L232
	movl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _strcspn
	.def	_strcspn;	.scl	2;	.type	32;	.endef
_strcspn:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %eax
	movl	%edi, %esi
	movl	%eax, %ebx
L240:
	movb	$0, -44(%ebp,%edx)
	incl	%edx
	cmpl	$31, %edx
	jle	L240
	cmpb	$0, (%eax)
	je	L252
L244:
	movb	(%ebx), %cl
	movl	$1, %eax
	movb	%cl, %dl
	incl	%ebx
	shrb	$3, %dl
	andl	$7, %ecx
	movzbl	%dl, %edx
	sall	%cl, %eax
	orb	%al, -44(%ebp,%edx)
	cmpb	$0, (%ebx)
	jne	L244
L252:
	orb	$1, -44(%ebp)
	movb	(%edi), %cl
	xorl	%edx, %edx
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-44(%ebp,%eax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	jne	L254
L248:
	incl	%esi
	incl	%edx
	movb	(%esi), %cl
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-44(%ebp,%eax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	je	L248
L254:
	addl	$32, %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _stricmp
	.def	_stricmp;	.scl	2;	.type	32;	.endef
_stricmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	12(%ebp), %ecx
	movl	8(%ebp), %ebx
L256:
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$64, %eax
	jle	L259
	cmpl	$90, %eax
	jg	L259
	addl	$32, %eax
L259:
	movzbl	(%ecx), %edx
	incl	%ecx
	cmpl	$64, %edx
	jle	L258
	cmpl	$90, %edx
	jg	L258
	addl	$32, %edx
L258:
	testl	%eax, %eax
	je	L257
	cmpl	%edx, %eax
	je	L256
L257:
	popl	%ebx
	subl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _strlen
	.def	_strlen;	.scl	2;	.type	32;	.endef
_strlen:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
	movl	%ecx, %edx
L264:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	L264
	subl	%ecx, %edx
	popl	%ebp
	leal	-1(%edx), %eax
	ret
	.align 2
.globl _strlwr
	.def	_strlwr;	.scl	2;	.type	32;	.endef
_strlwr:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	je	L274
L272:
	movb	(%edx), %cl
	leal	-65(%ecx), %eax
	cmpb	$25, %al
	ja	L268
	leal	32(%ecx), %eax
	movb	%al, (%edx)
L268:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	L272
L274:
	movl	%edx, %eax
	popl	%ebp
	ret
	.align 2
.globl _strncmp
	.def	_strncmp;	.scl	2;	.type	32;	.endef
_strncmp:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%ebx
	movl	16(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx
	testl	%eax, %eax
	je	L275
	decl	%eax
	je	L278
	movb	(%ecx), %dl
	testb	%dl, %dl
	je	L278
	cmpb	(%ebx), %dl
	je	L281
L278:
	movzbl	(%ecx), %edx
	movzbl	(%ebx), %eax
	subl	%eax, %edx
L275:
	popl	%ebx
	movl	%edx, %eax
	popl	%ebp
	ret
L281:
	incl	%ecx
	incl	%ebx
	decl	%eax
	je	L278
	movb	(%ecx), %dl
	testb	%dl, %dl
	je	L278
	cmpb	(%ebx), %dl
	je	L281
	jmp	L278
	.align 2
.globl _strncpy
	.def	_strncpy;	.scl	2;	.type	32;	.endef
_strncpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	testl	%edx, %edx
	je	L289
	movb	(%ebx), %al
	leal	1(%esi), %ecx
	incl	%ebx
	movb	%al, (%esi)
	testb	%al, %al
	je	L285
L288:
	decl	%edx
	je	L289
	movb	(%ebx), %al
	incl	%ebx
	movb	%al, (%ecx)
	incl	%ecx
	testb	%al, %al
	jne	L288
L285:
	testl	%edx, %edx
	je	L289
	decl	%edx
	je	L289
L293:
	movb	$0, (%ecx)
	incl	%ecx
	decl	%edx
	jne	L293
L289:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _strnicmp
	.def	_strnicmp;	.scl	2;	.type	32;	.endef
_strnicmp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	16(%ebp), %ecx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	testl	%ecx, %ecx
	je	L297
L298:
	movzbl	(%esi), %eax
	incl	%esi
	cmpl	$64, %eax
	jle	L301
	cmpl	$90, %eax
	jg	L301
	addl	$32, %eax
L301:
	movzbl	(%ebx), %edx
	incl	%ebx
	cmpl	$64, %edx
	jle	L300
	cmpl	$90, %edx
	jg	L300
	addl	$32, %edx
L300:
	decl	%ecx
	je	L299
	testl	%eax, %eax
	je	L299
	cmpl	%edx, %eax
	je	L298
L299:
	subl	%edx, %eax
L296:
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L297:
	xorl	%eax, %eax
	jmp	L296
	.align 2
.globl _strnpst
	.def	_strnpst;	.scl	2;	.type	32;	.endef
_strnpst:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	12(%ebp), %eax
	movl	16(%ebp), %ecx
	movl	8(%ebp), %ebx
	movb	(%eax), %dl
	testb	%dl, %dl
	je	L307
	testl	%ecx, %ecx
	je	L307
L310:
	incl	%eax
	movb	%dl, (%ebx)
	decl	%ecx
	incl	%ebx
	movb	(%eax), %dl
	testb	%dl, %dl
	je	L307
	testl	%ecx, %ecx
	jne	L310
L307:
	movl	%ebx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl __strnset
	.def	__strnset;	.scl	2;	.type	32;	.endef
__strnset:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	16(%ebp), %edx
	movl	8(%ebp), %ecx
	decl	%edx
	movl	12(%ebp), %ebx
	movl	%ecx, %eax
	cmpl	$-1, %edx
	je	L314
	cmpb	$0, (%ecx)
	je	L314
L317:
	decl	%edx
	movb	%bl, (%ecx)
	incl	%ecx
	cmpl	$-1, %edx
	je	L314
	cmpb	$0, (%ecx)
	jne	L317
L314:
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _strpbrk
	.def	_strpbrk;	.scl	2;	.type	32;	.endef
_strpbrk:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %edx
	movl	%edi, %esi
	movl	%edx, %ebx
L324:
	movb	$0, -44(%ebp,%eax)
	incl	%eax
	cmpl	$31, %eax
	jle	L324
	cmpb	$0, (%edx)
	je	L337
L328:
	movb	(%ebx), %cl
	movl	$1, %eax
	movb	%cl, %dl
	incl	%ebx
	shrb	$3, %dl
	andl	$7, %ecx
	movzbl	%dl, %edx
	sall	%cl, %eax
	orb	%al, -44(%ebp,%edx)
	cmpb	$0, (%ebx)
	jne	L328
L337:
	cmpb	$0, (%edi)
	je	L339
L333:
	movb	(%esi), %cl
	movl	%esi, %edx
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-44(%ebp,%eax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	jne	L319
	incl	%esi
	cmpb	$0, (%esi)
	jne	L333
L339:
	xorl	%edx, %edx
L319:
	addl	$32, %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _strpst
	.def	_strpst;	.scl	2;	.type	32;	.endef
_strpst:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	cmpb	$0, (%edx)
	je	L346
L344:
	movb	(%edx), %al
	incl	%edx
	movb	%al, (%ecx)
	incl	%ecx
	cmpb	$0, (%edx)
	jne	L344
L346:
	movl	%ecx, %eax
	popl	%ebp
	ret
	.align 2
.globl _strrchr
	.def	_strrchr;	.scl	2;	.type	32;	.endef
_strrchr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %edx
	movl	12(%ebp), %ebx
	movl	%edx, %ecx
L348:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	L348
L351:
	decl	%edx
	cmpl	%ecx, %edx
	je	L352
	cmpb	%bl, (%edx)
	jne	L351
L352:
	cmpb	%bl, (%edx)
	je	L356
	xorl	%eax, %eax
L347:
	popl	%ebx
	popl	%ebp
	ret
L356:
	movl	%edx, %eax
	jmp	L347
	.align 2
.globl __strrev
	.def	__strrev;	.scl	2;	.type	32;	.endef
__strrev:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	%ecx, %esi
	movl	%ecx, %ebx
L358:
	movb	(%ecx), %al
	incl	%ecx
	testb	%al, %al
	jne	L358
	subl	$2, %ecx
	cmpl	%ecx, %esi
	jae	L366
L364:
	movb	(%ebx), %dl
	movb	(%ecx), %al
	movb	%al, (%ebx)
	movb	%dl, (%ecx)
	incl	%ebx
	decl	%ecx
	cmpl	%ecx, %ebx
	jb	L364
L366:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl __strset
	.def	__strset;	.scl	2;	.type	32;	.endef
__strset:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	%edx, %eax
	cmpb	$0, (%edx)
	je	L373
L371:
	movb	%cl, (%edx)
	incl	%edx
	cmpb	$0, (%edx)
	jne	L371
L373:
	popl	%ebp
	ret
	.align 2
.globl _strspn
	.def	_strspn;	.scl	2;	.type	32;	.endef
_strspn:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	subl	$32, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edi
	movl	%eax, %ebx
L379:
	movb	$0, -44(%ebp,%esi)
	incl	%esi
	cmpl	$31, %esi
	jle	L379
	cmpb	$0, (%eax)
	je	L392
L383:
	movb	(%ebx), %cl
	movl	$1, %eax
	movb	%cl, %dl
	incl	%ebx
	shrb	$3, %dl
	andl	$7, %ecx
	movzbl	%dl, %edx
	sall	%cl, %eax
	orb	%al, -44(%ebp,%edx)
	cmpb	$0, (%ebx)
	jne	L383
L392:
	movl	8(%ebp), %eax
	movb	(%eax), %dl
	testb	%dl, %dl
	je	L384
	movb	%dl, %al
	movl	%edx, %ecx
	shrb	$3, %al
	andl	$7, %ecx
	movzbl	%al, %eax
	xorl	%esi, %esi
	movzbl	-44(%ebp,%eax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	je	L394
L388:
	incl	%edi
	incl	%esi
	movb	(%edi), %cl
	movb	%cl, %al
	andl	$7, %ecx
	shrb	$3, %al
	movzbl	%al, %eax
	movzbl	-44(%ebp,%eax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	jne	L388
L394:
	movl	%esi, %eax
L374:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L384:
	xorl	%eax, %eax
	jmp	L374
	.align 2
.globl _strstr
	.def	_strstr;	.scl	2;	.type	32;	.endef
_strstr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	12(%ebp), %edi
	movl	8(%ebp), %edx
	movb	(%edi), %al
	movb	%al, -13(%ebp)
	movl	%edx, %eax
	cmpb	$0, -13(%ebp)
	je	L395
	cmpb	$0, (%edx)
	je	L408
L406:
	movb	(%edx), %al
	movl	%edx, %esi
	movl	%edi, %ecx
	testb	%al, %al
	je	L401
	cmpb	$0, -13(%ebp)
	je	L401
	cmpb	-13(%ebp), %al
	je	L404
L401:
	cmpb	$0, (%ecx)
	je	L410
	incl	%edx
	cmpb	$0, (%edx)
	jne	L406
L408:
	xorl	%eax, %eax
L395:
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L410:
	movl	%edx, %eax
	jmp	L395
L404:
	incl	%esi
	incl	%ecx
	movb	(%esi), %bl
	testb	%bl, %bl
	je	L401
	movb	(%ecx), %al
	testb	%al, %al
	je	L401
	cmpb	%al, %bl
	je	L404
	jmp	L401
	.align 2
.globl _strupr
	.def	_strupr;	.scl	2;	.type	32;	.endef
_strupr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %edx
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	je	L418
L416:
	movb	(%edx), %cl
	leal	-97(%ecx), %eax
	cmpb	$25, %al
	ja	L412
	leal	-32(%ecx), %eax
	movb	%al, (%edx)
L412:
	movb	(%edx), %al
	incl	%edx
	testb	%al, %al
	jne	L416
L418:
	movl	%ebx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.data
	.align 4
_holdrand:
	.long	1
	.text
	.align 2
.globl _srand
	.def	_srand;	.scl	2;	.type	32;	.endef
_srand:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	movl	%eax, _holdrand
	ret
	.align 2
.globl _rand
	.def	_rand;	.scl	2;	.type	32;	.endef
_rand:
	movl	_holdrand, %eax
	pushl	%ebp
	imull	$214013, %eax, %eax
	addl	$2531011, %eax
	movl	%esp, %ebp
	movl	%eax, _holdrand
	popl	%ebp
	sarl	$16, %eax
	andl	$32767, %eax
	ret
	.align 2
.globl _mem_zero
	.def	_mem_zero;	.scl	2;	.type	32;	.endef
_mem_zero:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%edi
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edi
	shrl	$2, %ecx
/APP
	rep stosl;
/NO_APP
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _heap_init
	.def	_heap_init;	.scl	2;	.type	32;	.endef
_heap_init:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	popl	%ebp
	movl	%eax, _heap_pointer
	leal	(%ecx,%eax), %edx
	movl	%edx, _heap_end
	jmp	_mem_zero
	.align 2
.globl _heap_alloc
	.def	_heap_alloc;	.scl	2;	.type	32;	.endef
_heap_alloc:
	pushl	%ebp
	movl	_heap_pointer, %eax
	movl	%esp, %ebp
	movl	%eax, %edx
	addl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, _heap_pointer
	ret
	.align 2
.globl _heap_allocaligned
	.def	_heap_allocaligned;	.scl	2;	.type	32;	.endef
_heap_allocaligned:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%esi
	movl	_heap_pointer, %esi
	pushl	%ebx
	movl	%esi, %eax
	movl	8(%ebp), %ebx
	divl	12(%ebp)
	testl	%edx, %edx
	je	L425
	leal	(%edx,%esi), %eax
	movl	%eax, _heap_pointer
L425:
	movl	%ebx, 8(%ebp)
	popl	%ebx
	popl	%esi
	popl	%ebp
	jmp	_heap_alloc
	.align 2
.globl _repository_init
	.def	_repository_init;	.scl	2;	.type	32;	.endef
_repository_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _repository_register
	.def	_repository_register;	.scl	2;	.type	32;	.endef
_repository_register:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _log_status_success
	.data
	.align 4
_log_status_success:
	.long	2811
	.text
	.align 32
LC0:
	.ascii "[ ][.....................................................................]\0"
	.align 2
.globl _log_item
	.def	_log_item;	.scl	2;	.type	32;	.endef
_log_item:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$80, %esp
	leal	-84(%ebp), %ebx
	pushl	$LC0
	pushl	%ebx
	call	_strcpy
	leal	-80(%ebp), %eax
	pushl	8(%ebp)
	pushl	%eax
	call	_strpst
	pushl	%ebx
	call	_log_writestring
	movl	-4(%ebp), %ebx
	leave
	ret
	.align 32
LC1:
	.ascii "   [.....................................................................]\0"
	.align 2
.globl _log_subitem
	.def	_log_subitem;	.scl	2;	.type	32;	.endef
_log_subitem:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$80, %esp
	leal	-84(%ebp), %ebx
	pushl	$LC1
	pushl	%ebx
	call	_strcpy
	leal	-80(%ebp), %eax
	pushl	8(%ebp)
	pushl	%eax
	call	_strpst
	pushl	%ebx
	call	_log_writestring
	movl	-4(%ebp), %ebx
	leave
	ret
	.align 2
.globl _log_number
	.def	_log_number;	.scl	2;	.type	32;	.endef
_log_number:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$112, %esp
	leal	-40(%ebp), %ebx
	leal	-120(%ebp), %esi
	pushl	$10
	pushl	%ebx
	pushl	12(%ebp)
	call	_u32toa
	pushl	$LC1
	pushl	%esi
	call	_strcpy
	leal	-116(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	_strnpst
	addl	$32, %esp
	pushl	$66
	pushl	%ebx
	pushl	$4
	pushl	%ebx
	call	_strlen
	movl	$73, %edx
	subl	%eax, %edx
	movl	%edx, (%esp)
	call	_max
	popl	%edx
	popl	%ecx
	leal	(%eax,%esi), %eax
	pushl	%eax
	call	_strnpst
	pushl	%esi
	call	_log_writestring
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _log_dec
	.def	_log_dec;	.scl	2;	.type	32;	.endef
_log_dec:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$112, %esp
	leal	-40(%ebp), %ebx
	leal	-120(%ebp), %esi
	pushl	$10
	pushl	%ebx
	pushl	12(%ebp)
	call	_u32toa
	pushl	$LC1
	pushl	%esi
	call	_strcpy
	leal	-116(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	_strnpst
	addl	$32, %esp
	pushl	$66
	pushl	%ebx
	pushl	$4
	pushl	%ebx
	call	_strlen
	movl	$73, %edx
	subl	%eax, %edx
	movl	%edx, (%esp)
	call	_max
	popl	%ebx
	popl	%edx
	leal	(%eax,%esi), %eax
	pushl	%eax
	call	_strnpst
	pushl	%esi
	call	_log_writestring
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 32
LC2:
	.ascii "   [.............................................................0000000h]\0"
	.align 2
.globl _log_hex
	.def	_log_hex;	.scl	2;	.type	32;	.endef
_log_hex:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$112, %esp
	leal	-40(%ebp), %ebx
	leal	-120(%ebp), %esi
	pushl	$16
	pushl	%ebx
	pushl	12(%ebp)
	call	_u32toa
	pushl	$LC2
	pushl	%esi
	call	_strcpy
	leal	-116(%ebp), %eax
	pushl	$66
	pushl	8(%ebp)
	pushl	%eax
	call	_strnpst
	addl	$32, %esp
	pushl	$66
	pushl	%ebx
	pushl	$4
	pushl	%ebx
	call	_strlen
	movl	$72, %edx
	subl	%eax, %edx
	movl	%edx, (%esp)
	call	_max
	popl	%ecx
	popl	%ebx
	leal	(%eax,%esi), %eax
	pushl	%eax
	call	_strnpst
	pushl	%esi
	call	_log_writestring
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
.globl _log_status
	.def	_log_status;	.scl	2;	.type	32;	.endef
_log_status:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %eax
	movl	%eax, %ebx
	shrl	$8, %ebx
/APP
	movb $0x02, %ah;xorb %bh, %bh;movw $0x1705, %dx;int $0x10;movb $0x09, %ah;xorb %bh, %bh;movw $1, %cx;int $0x10;
/NO_APP
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _log_writestring
	.def	_log_writestring;	.scl	2;	.type	32;	.endef
_log_writestring:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	8(%ebp), %esi
/APP
	movw $0x0601, %ax;movb $0x0F, %bh;movw $0x0202, %cx;movw $0x184F, %dx;int $0x10;movb $0x02, %ah;xorb %bh, %bh;movw $0x1704, %dx;int $0x10;cld;1:lodsb;orb %al, %al;jz 1f;movb $0x0E, %ah;movw $0x000F, %bx;int $0x10;jmp 1b;1:
/NO_APP
	popl	%esi
	popl	%ebp
	ret
LC3:
	.ascii "Initializing BIOS Disk Access\0"
LC4:
	.ascii "Successful Completion\0"
LC5:
	.ascii "Invalid Function or Parameter\0"
LC6:
	.ascii "Address Mark Not Found\0"
LC7:
	.ascii "Disk Write-Protected\0"
LC8:
	.ascii "Sector Not Found / Read Error\0"
LC9:
	.ascii "Reset Failed\0"
LC10:
	.ascii "Disk Changed\0"
	.align 32
LC11:
	.ascii "Drive Parameter Activity Failed\0"
LC12:
	.ascii "DMA Overrun\0"
LC13:
	.ascii "Data Boundary Error\0"
LC14:
	.ascii "Bad Sector Detected\0"
LC15:
	.ascii "Bad Track Detected\0"
	.align 32
LC16:
	.ascii "Unsupported Track or Invalid Media\0"
	.align 32
LC17:
	.ascii "Invalid Number of Sectors on Format\0"
	.align 32
LC18:
	.ascii "Control Data Address Mark Detected\0"
	.align 32
LC19:
	.ascii "DMA Arbitration Level Out of Range\0"
	.align 32
LC20:
	.ascii "Uncorrectable CRC or ECC Error Detected\0"
LC21:
	.ascii "Data ECC Corrected\0"
LC22:
	.ascii "Controller Failure\0"
LC23:
	.ascii "No Media In Drive\0"
	.align 32
LC24:
	.ascii "Invalid Drive Type Stored in CMOS\0"
LC25:
	.ascii "Seek Failed\0"
LC26:
	.ascii "Timeout\0"
LC27:
	.ascii "Drive Not Ready\0"
LC28:
	.ascii "Volume Not Locked in Drive\0"
LC29:
	.ascii "Volume Locked in Drive\0"
LC30:
	.ascii "Volume Not Removable\0"
LC31:
	.ascii "Volume In Use\0"
LC32:
	.ascii "Lock Count Exceded\0"
LC33:
	.ascii "Valid Eject Request Failed\0"
	.align 32
LC34:
	.ascii "Volume Present but Read Protected\0"
LC35:
	.ascii "Undefined Error\0"
LC36:
	.ascii "Write Fault\0"
LC37:
	.ascii "Status Register Error\0"
LC38:
	.ascii "Sense Operation Failed\0"
LC39:
	.ascii "Floppy Drives\0"
LC40:
	.ascii "Hard Drives\0"
	.align 2
.globl _disk_init
	.def	_disk_init;	.scl	2;	.type	32;	.endef
_disk_init:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	subl	$16, %esp
	movl	$_temp_bda, %edi
	pushl	$LC3
	call	_log_item
/APP
	xorw %ax, %ax;movw %ax, %ds;movw $0x0100, %cx;movw $0x0400, %si;rep movsb;movw %es, %ax;movw %ax, %ds;
/NO_APP
	movl	$LC4, _disk_errorcodes
	movl	$LC5, _disk_errorcodes+4
	movl	$LC6, _disk_errorcodes+8
	movl	$LC7, _disk_errorcodes+12
	movl	$LC8, _disk_errorcodes+16
	movl	$LC9, _disk_errorcodes+20
	movl	$LC10, _disk_errorcodes+24
	movl	$LC11, _disk_errorcodes+28
	movl	$LC12, _disk_errorcodes+32
	movl	$LC13, _disk_errorcodes+36
	movl	$LC14, _disk_errorcodes+40
	movl	$LC15, _disk_errorcodes+44
	movl	$LC16, _disk_errorcodes+48
	movl	$LC17, _disk_errorcodes+52
	movl	$LC18, _disk_errorcodes+56
	movl	$LC19, _disk_errorcodes+60
	movl	$LC20, _disk_errorcodes+64
	movl	$LC21, _disk_errorcodes+68
	movl	$LC22, _disk_errorcodes+128
	movl	$LC23, _disk_errorcodes+196
	movl	$LC24, _disk_errorcodes+200
	movl	$LC25, _disk_errorcodes+256
	movl	$LC26, _disk_errorcodes+512
	movl	$LC27, _disk_errorcodes+680
	movl	$LC28, _disk_errorcodes+704
	movl	$LC29, _disk_errorcodes+708
	movl	$LC30, _disk_errorcodes+712
	movl	$LC31, _disk_errorcodes+716
	movl	$LC32, _disk_errorcodes+720
	movl	$LC33, _disk_errorcodes+724
	movl	$LC34, _disk_errorcodes+728
	movl	$LC35, _disk_errorcodes+748
	movl	$LC36, _disk_errorcodes+816
	movl	$LC37, _disk_errorcodes+896
	movl	_temp_bda+16, %eax
	popl	%edi
	movl	$LC38, _disk_errorcodes+1020
	testl	$1, %eax
	je	L436
	shrl	$6, %eax
	andl	$3, %eax
	incl	%eax
	movl	%eax, _disk_arch_floppydrives
L437:
	movzbl	_temp_bda+117, %eax
	movl	%eax, _disk_arch_harddrives
	movl	_disk_arch_floppydrives, %edx
	xorl	%eax, %eax
	cmpl	%edx, %eax
	jae	L444
L442:
	incl	%eax
	cmpl	%edx, %eax
	jb	L442
L444:
	pushl	_log_status_success
	call	_log_status
	pushl	_disk_arch_floppydrives
	pushl	$LC39
	call	_log_number
	pushl	_disk_arch_harddrives
	pushl	$LC40
	call	_log_number
	movl	-4(%ebp), %edi
	leave
	ret
L436:
	movl	$0, _disk_arch_floppydrives
	jmp	L437
	.align 2
.globl _disk_readblock
	.def	_disk_readblock;	.scl	2;	.type	32;	.endef
_disk_readblock:
	pushl	%ebp
	movl	$513, %eax
	movl	%esp, %ebp
	xorl	%ecx, %ecx
	pushl	%ebx
	xorl	%edx, %edx
	movl	16(%ebp), %ebx
/APP
	stc;int $0x13;sti;
/NO_APP
	popl	%ebx
	popl	%ebp
	ret
	.align 2
.globl _sys_arch_io_read8
	.def	_sys_arch_io_read8;	.scl	2;	.type	32;	.endef
_sys_arch_io_read8:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
/APP
	inb %dx, %al;
/NO_APP
	movzbl	%al, %eax
	ret
	.align 2
.globl _sys_arch_io_read16
	.def	_sys_arch_io_read16;	.scl	2;	.type	32;	.endef
_sys_arch_io_read16:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
/APP
	inw %dx, %ax;
/NO_APP
	movzwl	%ax, %eax
	ret
	.align 2
.globl _sys_arch_io_read32
	.def	_sys_arch_io_read32;	.scl	2;	.type	32;	.endef
_sys_arch_io_read32:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
/APP
	inl %dx, %eax;
/NO_APP
	ret
	.align 2
.globl _sys_arch_io_write8
	.def	_sys_arch_io_write8;	.scl	2;	.type	32;	.endef
_sys_arch_io_write8:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movb	12(%ebp), %al
/APP
	outb %al, %dx;
/NO_APP
	popl	%ebp
	ret
	.align 2
.globl _sys_arch_io_write16
	.def	_sys_arch_io_write16;	.scl	2;	.type	32;	.endef
_sys_arch_io_write16:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
/APP
	outw %ax, %dx;
/NO_APP
	popl	%ebp
	ret
	.align 2
.globl _sys_arch_io_write32
	.def	_sys_arch_io_write32;	.scl	2;	.type	32;	.endef
_sys_arch_io_write32:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
/APP
	outl %eax, %dx;
/NO_APP
	popl	%ebp
	ret
	.align 2
.globl _sys_arch_kbc_sendcommand
	.def	_sys_arch_kbc_sendcommand;	.scl	2;	.type	32;	.endef
_sys_arch_kbc_sendcommand:
	pushl	%ebp
	movl	%esp, %ebp
	movzbl	8(%ebp), %eax
	pushl	%eax
	pushl	$100
	call	_sys_arch_io_write8
	leave
	ret
	.align 2
.globl _sys_arch_kbc_senddata
	.def	_sys_arch_kbc_senddata;	.scl	2;	.type	32;	.endef
_sys_arch_kbc_senddata:
	pushl	%ebp
	movl	%esp, %ebp
	movzbl	8(%ebp), %eax
	pushl	%eax
	pushl	$96
	call	_sys_arch_io_write8
	leave
	ret
	.align 2
.globl _sys_arch_kbc_readdata
	.def	_sys_arch_kbc_readdata;	.scl	2;	.type	32;	.endef
_sys_arch_kbc_readdata:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$96
	call	_sys_arch_io_read8
	movzbl	%al, %eax
	leave
	ret
	.align 2
.globl _sys_arch_kbc_waitsend
	.def	_sys_arch_kbc_waitsend;	.scl	2;	.type	32;	.endef
_sys_arch_kbc_waitsend:
	pushl	%ebp
	movl	%esp, %ebp
L456:
	pushl	$100
	call	_sys_arch_io_read8
	popl	%edx
	andl	$2, %eax
	testb	%al, %al
	jne	L456
	leave
	ret
	.align 2
.globl _sys_arch_kbc_waitread
	.def	_sys_arch_kbc_waitread;	.scl	2;	.type	32;	.endef
_sys_arch_kbc_waitread:
	pushl	%ebp
	movl	%esp, %ebp
L460:
	pushl	$100
	call	_sys_arch_io_read8
	popl	%ecx
	andl	$1, %eax
	testb	%al, %al
	jne	L460
	leave
	ret
	.align 2
.globl _sys_arch_sig_disable
	.def	_sys_arch_sig_disable;	.scl	2;	.type	32;	.endef
_sys_arch_sig_disable:
	pushl	%ebp
	movl	%esp, %ebp
/APP
	cli;
/NO_APP
	popl	%ebp
	ret
	.align 2
.globl _sys_arch_sig_enable
	.def	_sys_arch_sig_enable;	.scl	2;	.type	32;	.endef
_sys_arch_sig_enable:
	pushl	%ebp
	movl	%esp, %ebp
/APP
	sti;
/NO_APP
	popl	%ebp
	ret
LC41:
	.ascii "Enabling A20\0"
LC42:
	.ascii "Keyboard Controller #1\0"
LC43:
	.ascii "Vectra\0"
	.align 2
.globl _a20_enable
	.def	_a20_enable;	.scl	2;	.type	32;	.endef
_a20_enable:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$LC41
	call	_log_item
	call	_a20_test
	popl	%edx
	testl	%eax, %eax
	jne	L469
	pushl	$LC42
	call	_log_subitem
	call	_a20_enable_kbc1
	call	_a20_test
	popl	%ecx
	testl	%eax, %eax
	jne	L469
	pushl	$LC43
	call	_log_subitem
	call	_a20_enable_vectra
	call	_a20_test
	popl	%edx
	testl	%eax, %eax
	jne	L469
L465:
	leave
	ret
L469:
	pushl	_log_status_success
	call	_log_status
	movl	$1, %eax
	jmp	L465
	.align 2
.globl _a20_test
	.def	_a20_test;	.scl	2;	.type	32;	.endef
_a20_test:
/APP
	movb $0x55, 0xFFEF;movw $0xFFFF, %ax;movw %ax, %ds;movb $0xAA, 0xFFFF;xorw %ax, %ax;movw %ax, %ds;movb 0xFFEF, %al;
/NO_APP
	pushl	%ebp
	cmpl	$85, %eax
	movl	%esp, %ebp
	sete	%al
	movzbl	%al, %eax
	popl	%ebp
	ret
	.align 2
.globl _a20_enable_kbc2
	.def	_a20_enable_kbc2;	.scl	2;	.type	32;	.endef
_a20_enable_kbc2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	call	_sys_arch_kbc_waitsend
	pushl	$173
	call	_sys_arch_kbc_sendcommand
	call	_sys_arch_kbc_waitsend
	pushl	$208
	call	_sys_arch_kbc_sendcommand
	call	_sys_arch_kbc_waitread
	call	_sys_arch_kbc_readdata
	movb	%al, %bl
	call	_sys_arch_kbc_waitsend
	orl	$2, %ebx
	pushl	$209
	call	_sys_arch_kbc_sendcommand
	call	_sys_arch_kbc_waitsend
	movzbl	%bl, %eax
	pushl	%eax
	call	_sys_arch_kbc_senddata
	call	_sys_arch_kbc_waitsend
	pushl	$174
	call	_sys_arch_kbc_sendcommand
	movl	-4(%ebp), %ebx
	leave
	ret
	.align 2
.globl _a20_enable_vectra
	.def	_a20_enable_vectra;	.scl	2;	.type	32;	.endef
_a20_enable_vectra:
	pushl	%ebp
	movl	%esp, %ebp
	call	_sys_arch_kbc_waitsend
	pushl	$173
	call	_sys_arch_kbc_sendcommand
	call	_sys_arch_kbc_waitsend
	pushl	$223
	call	_sys_arch_kbc_sendcommand
	call	_sys_arch_kbc_waitsend
	pushl	$174
	call	_sys_arch_kbc_sendcommand
	leave
	ret
	.align 2
.globl _a20_enable_ps2
	.def	_a20_enable_ps2;	.scl	2;	.type	32;	.endef
_a20_enable_ps2:
	pushl	%ebp
	movl	%esp, %ebp
/APP
	movl $0x2401, %eax; int $0x15;
/NO_APP
	popl	%ebp
	ret
	.align 2
.globl _a20_enable_kbc1
	.def	_a20_enable_kbc1;	.scl	2;	.type	32;	.endef
_a20_enable_kbc1:
	pushl	%ebp
	movl	%esp, %ebp
/APP
	A20:call empty8042;movb $0xD1, %al;outb %al, $0x64;call empty8042;movb $0xDF, %al;outb %al ,$0x60;call empty8042;jmp argq;empty8042:inb $0x64, %al;testb $0x02, %al;jnz empty8042;ret;argq:
/NO_APP
	popl	%ebp
	ret
LC44:
	.ascii "E820\0"
LC45:
	.ascii "E801\0"
LC46:
	.ascii "008A\0"
LC47:
	.ascii "DA88\0"
LC48:
	.ascii "0088\0"
LC49:
	.ascii "00C7\0"
LC50:
	.ascii "IN12\0"
	.align 2
.globl _memory_detect
	.def	_memory_detect;	.scl	2;	.type	32;	.endef
_memory_detect:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	$LC44
	call	_log_item
	call	_memory_detect_e820
	pushl	$LC45
	call	_log_item
	call	_memory_detect_e801
	pushl	$LC46
	call	_log_item
	call	_memory_detect_008a
	pushl	$LC47
	call	_log_item
	call	_memory_detect_da88
	pushl	$LC48
	call	_log_item
	call	_memory_detect_0088
	pushl	$LC49
	call	_log_item
	call	_memory_detect_00c7
	pushl	$LC50
	call	_log_item
	call	_memory_findroms
	xorl	%eax, %eax
	leave
	ret
LC51:
	.ascii "AX\0"
	.align 2
.globl _memory_detect_0088
	.def	_memory_detect_0088;	.scl	2;	.type	32;	.endef
_memory_detect_0088:
	pushl	%ebp
	movl	$136, %edx
	movl	%edx, %eax
	movl	%esp, %ebp
	pushl	%ebx
	xorl	%ecx, %ecx
/APP
	stc;int $0x15;movl $0, %ebx;jnc 1f;movl $1, %ebx;1:
/NO_APP
	movl	%eax, %edx
	testl	%ebx, %ebx
	je	L478
L476:
	movl	%ecx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
L478:
	andl	$65535, %edx
	pushl	%edx
	pushl	$LC51
	call	_log_hex
	jmp	L476
LC52:
	.ascii "BX\0"
LC53:
	.ascii "CL\0"
	.align 2
.globl _memory_detect_da88
	.def	_memory_detect_da88;	.scl	2;	.type	32;	.endef
_memory_detect_da88:
	pushl	%ebp
	movl	$55944, %eax
	movl	%esp, %ebp
	xorl	%edx, %edx
	pushl	%esi
	pushl	%ebx
/APP
	stc;int $0x15;movl $0, %eax;jnc 1f;movl $1, %eax;1:
/NO_APP
	movl	%ecx, %esi
	testl	%eax, %eax
	je	L481
L479:
	leal	-8(%ebp), %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L481:
	andl	$65535, %ebx
	andl	$255, %esi
	pushl	%ebx
	pushl	$LC52
	call	_log_hex
	pushl	%esi
	pushl	$LC53
	call	_log_hex
	jmp	L479
LC54:
	.ascii "DX\0"
	.align 2
.globl _memory_detect_008a
	.def	_memory_detect_008a;	.scl	2;	.type	32;	.endef
_memory_detect_008a:
	pushl	%ebp
	movl	$138, %ecx
	movl	%esp, %ebp
	movl	%ecx, %eax
	pushl	%edi
	xorl	%ecx, %ecx
	pushl	%esi
	pushl	%ebx
	xorl	%ebx, %ebx
	movl	%ebx, %edx
/APP
	stc;int $0x15;movl $0, %edi;jnc 1f;movl $1, %edi;1:
/NO_APP
	movl	%edx, %ebx
	movl	%eax, %esi
	testl	%edi, %edi
	je	L484
L482:
	leal	-12(%ebp), %esp
	movl	%ecx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L484:
	andl	$65535, %esi
	andl	$65535, %ebx
	pushl	%esi
	pushl	$LC51
	call	_log_hex
	pushl	%ebx
	pushl	$LC54
	call	_log_hex
	jmp	L482
LC55:
	.ascii "C7\0"
	.align 2
.globl _memory_detect_00c7
	.def	_memory_detect_00c7;	.scl	2;	.type	32;	.endef
_memory_detect_00c7:
	pushl	%ebp
	movl	$192, %eax
	movl	%esp, %ebp
/APP
	stc;int $0x15;movl $0, %edx;jc 2f;testb $10, %es:6(%bx);jnc 2f;1:movl $1, %edx;2:
/NO_APP
	pushl	%esi
	xorl	%eax, %eax
	subl	$48, %esp
	testl	%edx, %edx
	je	L485
	movl	$199, %eax
	leal	-52(%ebp), %esi
/APP
	clc;int $0x15;movl $0, %edx;jnc 1f;movl $1, %edx;1:
/NO_APP
	xorl	%eax, %eax
	testl	%edx, %edx
	je	L488
L485:
	movl	-4(%ebp), %esi
	leave
	ret
L488:
	movzbl	-52(%ebp), %eax
	pushl	%eax
	pushl	$LC55
	call	_log_hex
	jmp	L485
LC56:
	.ascii "CX\0"
	.align 2
.globl _memory_detect_e801
	.def	_memory_detect_e801;	.scl	2;	.type	32;	.endef
_memory_detect_e801:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	$59393, %esi
	pushl	%ebx
	movl	%esi, %eax
	xorl	%ebx, %ebx
	pushl	%ecx
	pushl	%ecx
	movl	%ebx, %edx
	movl	%ebx, %ecx
/APP
	stc;int $0x15;movl $0, -20(%ebp);jnc 1f;movl $1, -20(%ebp);1:
/NO_APP
	movl	%ecx, %esi
	movl	%edx, %edi
	xorl	%ecx, %ecx
	movl	%eax, -16(%ebp)
	cmpl	$0, -20(%ebp)
	je	L491
L489:
	leal	-12(%ebp), %esp
	movl	%ecx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L491:
	andl	$65535, -16(%ebp)
	pushl	-16(%ebp)
	pushl	$LC51
	andl	$65535, %ebx
	andl	$65535, %esi
	call	_log_hex
	pushl	%ebx
	andl	$65535, %edi
	pushl	$LC52
	call	_log_hex
	pushl	%esi
	pushl	$LC56
	call	_log_hex
	pushl	%edi
	pushl	$LC54
	call	_log_hex
	jmp	L489
LC57:
	.ascii "Detecting Memory\0"
LC59:
	.ascii "Identifier\0"
LC60:
	.ascii "  Base\0"
LC61:
	.ascii "  Lenght\0"
LC62:
	.ascii "  Type\0"
	.align 32
LC58:
	.ascii "E820 NOT SUPPORTED! SYSTEM HALTED!\0"
	.align 2
.globl _memory_detect_e820
	.def	_memory_detect_e820;	.scl	2;	.type	32;	.endef
_memory_detect_e820:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	pushl	$LC57
	call	_log_item
	leal	-44(%ebp), %eax
	pushl	$20
	pushl	$0
	pushl	%eax
	call	_memset
	addl	$16, %esp
	movl	$0, -48(%ebp)
L493:
	movl	$59424, %eax
	movl	$20, %ecx
	movl	$1397571920, %edx
	leal	-44(%ebp), %edi
	movl	-48(%ebp), %ebx
/APP
	clc;int $0x15;movl $0, %edi;jnc 1f;movl $1, %edi;1:
/NO_APP
	movl	%ebx, %esi
	testl	%edi, %edi
	je	L502
	andl	$65280, %eax
	cmpl	$34304, %eax
	je	L503
	testl	%edi, %edi
	jne	L495
L502:
	pushl	-48(%ebp)
	pushl	$LC59
	call	_log_hex
	pushl	-44(%ebp)
	pushl	$LC60
	call	_log_hex
	pushl	-36(%ebp)
	pushl	$LC61
	call	_log_hex
	pushl	-28(%ebp)
	pushl	$LC62
	call	_log_hex
	addl	$32, %esp
	movl	%esi, -48(%ebp)
L495:
	cmpl	$0, -48(%ebp)
	jne	L493
	testl	%edi, %edi
	jne	L493
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L503:
	pushl	$LC58
	call	_log_item
	popl	%ebx
L497:
	jmp	L497
LC63:
	.ascii "Found ROM\0"
LC64:
	.ascii "Size\0"
	.align 2
.globl _memory_findroms
	.def	_memory_findroms;	.scl	2;	.type	32;	.endef
_memory_findroms:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	$49152, %esi
L510:
	movl	%esi, %eax
/APP
	movw %ax, %es;movl %es:0, %edx;movw %ds, %ax;movw %ax, %es;
/NO_APP
	cmpw	$-21931, %dx
	movl	%edx, %ebx
	je	L513
L507:
	subl	$-128, %esi
	cmpl	$65534, %esi
	jbe	L510
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L513:
	shrl	$7, %ebx
	pushl	%esi
	pushl	$LC63
	andl	$130560, %ebx
	call	_log_hex
	pushl	%ebx
	pushl	$LC64
	call	_log_dec
	addl	$16, %esp
	jmp	L507
	.align 2
.globl _ibm_init
	.def	_ibm_init;	.scl	2;	.type	32;	.endef
_ibm_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _trifs_init
	.def	_trifs_init;	.scl	2;	.type	32;	.endef
_trifs_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
LC65:
	.ascii "Disk Contents\0"
	.align 2
.globl _trifs_list
	.def	_trifs_list;	.scl	2;	.type	32;	.endef
_trifs_list:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	xorl	%esi, %esi
	pushl	$LC65
	xorl	%ebx, %ebx
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	pushl	_log_status_success
	call	_log_status
	addl	$20, %esp
L522:
	cmpb	$0, _trifs_buffer(%ebx)
	jne	L525
L519:
	incl	%esi
	addl	$32, %ebx
	movl	%esi, %eax
	cmpb	$15, %al
	jbe	L522
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L525:
	leal	_trifs_buffer(%ebx), %eax
	pushl	%eax
	call	_log_subitem
	popl	%eax
	jmp	L519
LC66:
	.ascii "Loading Core\0"
LC67:
	.ascii "Loading Root\0"
LC68:
	.ascii "Loading Test\0"
LC69:
	.ascii "Loading Ping\0"
LC70:
	.ascii "Loading Pong\0"
	.align 2
.globl _trifs_load
	.def	_trifs_load;	.scl	2;	.type	32;	.endef
_trifs_load:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%eax
	pushl	$LC66
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	addl	$16, %esp
	movb	_trifs_buffer+56, %al
	movb	%al, -14(%ebp)
	movb	_trifs_buffer+48, %al
	movb	%al, -13(%ebp)
	cmpb	-14(%ebp), %bl
	jb	L531
L553:
	pushl	_log_status_success
	xorl	%ebx, %ebx
	call	_log_status
	pushl	$LC67
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	addl	$20, %esp
	movb	_trifs_buffer+88, %al
	movb	%al, -14(%ebp)
	movb	_trifs_buffer+80, %al
	movb	%al, -13(%ebp)
	cmpb	-14(%ebp), %bl
	jb	L536
L555:
	pushl	_log_status_success
	xorl	%ebx, %ebx
	call	_log_status
	pushl	$LC68
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	addl	$20, %esp
	movb	_trifs_buffer+120, %al
	movb	%al, -14(%ebp)
	movb	_trifs_buffer+112, %al
	movb	%al, -13(%ebp)
	cmpb	-14(%ebp), %bl
	jb	L541
L557:
	pushl	_log_status_success
	xorl	%ebx, %ebx
	call	_log_status
	pushl	$LC69
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	addl	$20, %esp
	movb	_trifs_buffer+152, %al
	movb	%al, -14(%ebp)
	movb	_trifs_buffer+144, %al
	movb	%al, -13(%ebp)
	cmpb	-14(%ebp), %bl
	jb	L546
L559:
	pushl	_log_status_success
	xorl	%ebx, %ebx
	call	_log_status
	pushl	$LC70
	call	_log_item
	pushl	$0
	pushl	$1
	pushl	$_trifs_buffer
	call	_disk_read
	addl	$20, %esp
	movb	_trifs_buffer+184, %al
	movb	%al, -14(%ebp)
	movb	_trifs_buffer+176, %al
	movb	%al, -13(%ebp)
	cmpb	-14(%ebp), %bl
	jb	L551
L561:
	pushl	_log_status_success
	call	_log_status
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L551:
	movzbl	-13(%ebp), %eax
	movzbl	%bl, %edi
	pushl	$0
	addl	%edi, %eax
	sall	$9, %edi
	pushl	%eax
	pushl	$_trifs_buffer
	movl	$_trifs_buffer, %esi
	call	_disk_read
	movl	$256, %ecx
/APP
	movw $0x8800, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
/NO_APP
	incl	%ebx
	addl	$12, %esp
	cmpb	-14(%ebp), %bl
	jb	L551
	jmp	L561
L546:
	movzbl	-13(%ebp), %eax
	movzbl	%bl, %edi
	pushl	$0
	addl	%edi, %eax
	sall	$9, %edi
	pushl	%eax
	pushl	$_trifs_buffer
	movl	$_trifs_buffer, %esi
	call	_disk_read
	movl	$256, %ecx
/APP
	movw $0x8000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
/NO_APP
	incl	%ebx
	addl	$12, %esp
	cmpb	-14(%ebp), %bl
	jb	L546
	jmp	L559
L541:
	movzbl	-13(%ebp), %eax
	movzbl	%bl, %edi
	pushl	$0
	addl	%edi, %eax
	sall	$9, %edi
	pushl	%eax
	pushl	$_trifs_buffer
	movl	$_trifs_buffer, %esi
	call	_disk_read
	movl	$256, %ecx
/APP
	movw $0x7000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
/NO_APP
	incl	%ebx
	addl	$12, %esp
	cmpb	-14(%ebp), %bl
	jb	L541
	jmp	L557
L536:
	movzbl	-13(%ebp), %eax
	movzbl	%bl, %edi
	pushl	$0
	addl	%edi, %eax
	sall	$9, %edi
	pushl	%eax
	pushl	$_trifs_buffer
	movl	$_trifs_buffer, %esi
	call	_disk_read
	movl	$256, %ecx
/APP
	movw $0x6000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
/NO_APP
	incl	%ebx
	addl	$12, %esp
	cmpb	-14(%ebp), %bl
	jb	L536
	jmp	L555
L531:
	movzbl	-13(%ebp), %eax
	movzbl	%bl, %edi
	pushl	$0
	addl	%edi, %eax
	sall	$9, %edi
	pushl	%eax
	pushl	$_trifs_buffer
	movl	$_trifs_buffer, %esi
	call	_disk_read
	movl	$256, %ecx
/APP
	movw $0x2000, %ax;movw %ax, %es;rep movsw;movw %cs, %ax;movw %ax, %es;
/NO_APP
	incl	%ebx
	addl	$12, %esp
	cmpb	-14(%ebp), %bl
	jb	L531
	jmp	L553
	.align 2
.globl _fat_init
	.def	_fat_init;	.scl	2;	.type	32;	.endef
_fat_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _ext2_init
	.def	_ext2_init;	.scl	2;	.type	32;	.endef
_ext2_init:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
.globl _disk_read
	.def	_disk_read;	.scl	2;	.type	32;	.endef
_disk_read:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	$36, %ecx
	movl	12(%ebp), %eax
	movl	8(%ebp), %ebx
	divl	%ecx
	movl	$18, %ecx
	movl	%edx, -16(%ebp)
	movl	%eax, %esi
	movl	%edx, %eax
	sall	$8, %esi
	xorl	%edx, %edx
	divl	%ecx
	movl	%eax, %edi
	movl	$513, %eax
	sall	$8, %edi
	leal	1(%edx,%esi), %ecx
	addl	16(%ebp), %edi
	movl	%edi, %edx
/APP
	stc;int $0x13;sti;jnc disk_read_done;xorw $0, %ax;disk_read_done:
/NO_APP
	shrl	$8, %eax
	popl	%edx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
.globl _init8259
	.def	_init8259;	.scl	2;	.type	32;	.endef
_init8259:
	pushl	%ebp
	movl	%esp, %ebp
/APP
	mov $0x11, %al;out %al, $0x20;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA0;/*jmp .+2;*//*jmp .+2;*/mov $0x20, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x28, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x04, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/mov $0x02, %al;out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x01, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/mov $0x00, %al;out %al, $0x21;/*jmp .+2;*//*jmp .+2;*/out %al, $0xA1;/*jmp .+2;*//*jmp .+2;*/
/NO_APP
	popl	%ebp
	ret
LC71:
	.ascii "Initializing Repository\0"
LC72:
	.ascii "Trinary File System\0"
LC73:
	.ascii "FAT12 / FAT16 / FAT32\0"
LC74:
	.ascii "Ext2 FS\0"
	.align 2
.globl _entry
	.def	_entry;	.scl	2;	.type	32;	.endef
_entry:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$2048, %esp
	pushl	$LC71
	call	_log_item
	pushl	_log_status_success
	call	_log_status
	pushl	$LC72
	call	_log_subitem
	pushl	$LC73
	call	_log_subitem
	pushl	$LC74
	call	_log_subitem
	pushl	$4096
	pushl	$53248
	call	_heap_init
	call	_disk_init
	call	_trifs_list
	call	_trifs_load
	call	_memory_detect
/APP
	movw $0x03F2, %dx;xorb %al, %al;outb %al, %dx;cli;
/NO_APP
	pushl	$0
	call	_a20_enable
	addl	$32, %esp
	call	_init8259
	movw	$-21555, _idt48
	movl	$305419896, _idt48+2
	movw	$2048, _gdt48
	movl	$_gdt, _gdt48+2
	movb	$0, _gdt+4
	movb	$0, _gdt+7
	movw	$0, _gdt+2
	movw	$0, _gdt
	movb	$0, _gdt+5
	movb	$0, _gdt+6
	movb	$0, _gdt+20
	movb	$0, _gdt+23
	movw	$0, _gdt+18
	movw	$-1, _gdt+16
	movb	$-102, _gdt+21
	movb	$-49, _gdt+22
	movb	$0, _gdt+28
	movb	$0, _gdt+31
	movw	$0, _gdt+26
	movw	$-1, _gdt+24
	movb	$-110, _gdt+29
	movb	$-49, _gdt+30
/APP
	lidt _idt48;lgdt _gdt48;
/NO_APP
	movl	$_Aye, %edx
/APP
	movl %edx, code32start;xorl %eax, %eax;movl %eax, %cr3;movl %cr0, %eax;orl $0x00000001, %eax;movl %eax, %cr0;jmp flush;flush:.byte 0x66, 0xea;code32start: .long 0x10000;.word 0x0010;cli; hlt;
/NO_APP
	leave
	ret
	.comm	_heap_pointer, 16	 # 4
	.comm	_heap_end, 16	 # 4
	.comm	_disk_errorcodes, 1024	 # 1024
	.comm	_disk_arch_harddrives, 16	 # 4
	.comm	_disk_arch_floppydrives, 16	 # 4
	.comm	_temp_bda, 256	 # 256
	.comm	_disk_idlist, 1024	 # 1024
	.comm	_trifs_buffer, 512	 # 512
	.comm	_idt48, 16	 # 6
	.comm	_gdt48, 16	 # 6
	.comm	_gdt, 32	 # 24
	.comm	_debugdata, 16	 # 8
	.def	_Aye;	.scl	2;	.type	32;	.endef
	.def	_disk_read;	.scl	2;	.type	32;	.endef
	.def	_memory_findroms;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_00c7;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_0088;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_da88;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_008a;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_e801;	.scl	2;	.type	32;	.endef
	.def	_memory_detect_e820;	.scl	2;	.type	32;	.endef
	.def	_a20_enable_vectra;	.scl	2;	.type	32;	.endef
	.def	_a20_enable_kbc1;	.scl	2;	.type	32;	.endef
	.def	_a20_test;	.scl	2;	.type	32;	.endef
	.def	_log_writestring;	.scl	2;	.type	32;	.endef
