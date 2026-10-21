global ft_strdup
extern ft_strlen
extern ft_strcpy
extern malloc

; rdi, rsi, rdx, rcx

ft_strdup:
	push rdi
	call ft_strlen
	mov rdi, rax			; because return data in rax
	inc rdi
	call malloc	wrt ..plt	; with respect to plt : explain where is malloc to program		
	test rax, rax
	jz .error
	mov rdi, rax 			; the pointer from malloc into 1st arg
	mov rsi, [rsp]			; saved val into 2nd arg to not pop it 
	call ft_strcpy
	pop rsi
	ret
.error:
	pop rdi
	ret