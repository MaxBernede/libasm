global ft_strcmp

ft_strcmp:
.loop:
	mov al, [rdi]	; load byte first stirng
	cmp al, [rsi]	; compare to second string
	jne .diff		; if not requal jump diff Jne = jump not equal
	cmp al, 0		; check its not null | same as test al, al
	jz .equal
	inc rdi			; pointer ++
	inc rsi			; ++
	jmp .loop
.diff:
	movzx eax, byte[rdi] 	; s1[i] as unsigned 32 bits
	movzx ecx, byte[rsi] 	; s2[i] as unsigned 32 bits
	sub eax, ecx			; diff s1 - s2
	ret
.equal:
	xor eax, eax	; return 0 for equal | same as rax
	ret