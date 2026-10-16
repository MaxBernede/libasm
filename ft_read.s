global ft_read
extern __errno_location

ft_read:
	mov rax, 0		; syscall write linux
	syscall			; rdi, rsi, rdx already correct arguments
	cmp rax, 0
	jl .error		; if < 0 error Info : jz = and jl jump if less
	ret				; return rax = nb octets writen

.error:
	neg rax
	mov rdi, rax	; keeping the rdi
	call __errno_location wrt ..plt
	mov dword [rax], edi ; errno = code
	mov rax, -1		; return value will be -1
	ret