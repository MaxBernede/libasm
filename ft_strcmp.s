global ft_strcmp

ft_strcmp:
.loop:
	mov al, [rdi]	; load byte first stirng
	cmp al, [rsi]	; compare to second string
	jne .diff		; if not requal jump diff Jne = jump not equal
	cmp al, 0	; check its not null | same as test al, al
	jz .equal
	inc rdi			; pointer ++
	inc rsi			; ++
	jmp .loop
.diff:
	sub al, [rsi]	; diff s1 - s2
	movzx rax, al	; change 8bits to 64 to return it
	ret
.equal:
	xor eax, eax	; return 0 for equal | same as rax
	ret