global ft_read
extern __errno_location

ft_read:
	mov rax, 0		; syscall read linux
	syscall			; rdi, rsi, rdx already correct arguments
	cmp rax, 0
	jl .error		; if < 0 error Info : jz = and jl jump if less
	ret				; return rax = nb octets read

.error:
	neg rax
	push rax 		; save code on stack + allign to 16 oct
	; mov rdi, rax	; keeping the rax into rdi
	call __errno_location wrt ..plt ; func from libc, thats brings the address of errno into rax
	pop rdi			; get the code back into rdi
	mov dword [rax], edi ; errno = code (int) | edi is the 4 last octets of rdi
	mov rax, -1		; return value will be -1
	ret