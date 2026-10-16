global ft_strcmp

ftrcmp:
.loop:
	mov al, [rdi]	; load byte first stirng
	cmp al. [rsi]	; compare to second string
	jne .diff		; if not requal jump diff Jne = jump not equal
	test al, al		; check its not null
	inc rdi			; pointer ++
	inc rsi			; ++
	jmp .loop
.diff:
	sub al, [rsi]	; diff s1 - s2
	movzx rax, al	; change 8bits to 64 to return it
	ret
.equal:
	xor rax, rax	; return 0 for equal
	ret