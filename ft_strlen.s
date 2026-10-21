global ft_strlen

ft_strlen:
	xor rcx, rcx ; reset the counter to 0, also mov rcx, 0 works
.loop:
	cmp byte [rdi + rcx], 0
	jz .done 				; jump if zero
	inc rcx
	jmp .loop
.done:
	mov rax, rcx 			; rax is the return counter
	ret