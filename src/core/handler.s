[BITS 32]
[EXTERN _sigSwitch]
[EXTERN _eax]
[EXTERN _ebx]
[EXTERN _ecx]
[EXTERN _edx]
[EXTERN _esi]
[EXTERN _edi]
[EXTERN _esp]
[EXTERN _ebp]
[EXTERN _eip]
[EXTERN _efl]


[GLOBAL _sigWrapper]

_sigWrapper:
	mov [_eax], eax
	mov [_ebx], ebx
	mov [_ecx], ecx
	mov [_edx], edx
	mov [_esi], esi
	mov [_edi], edi
	mov [_ebp], ebp

	pop eax
	mov [_eip], eax
	pop eax
	pop eax
	mov [_efl], eax

	mov [_esp], esp

	call _sigSwitch


	mov esp, [_esp]

	mov eax, [_efl]
	push eax
	push cs
	mov eax, [_eip]
	push eax

	mov eax, [_eax]
	mov ebx, [_ebx]
	mov ecx, [_ecx]
	mov edx, [_edx]
	mov esi, [_esi]
	mov edi, [_edi]
	mov ebp, [_ebp]

	iret
	