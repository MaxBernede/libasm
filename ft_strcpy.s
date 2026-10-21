global ft_strcpy

; rdi, rsi, rdx, rcx
; rdi = dst,
; rsi = src
ft_strcpy:
	mov rax, rdi
.loop:
	movsb ; The MOVS command copies data from DS:(SI/ESI/RSI) to ES:(DI/EDI/RDI) then ++
	cmp byte [rdi - 1], 0 ; check if we just copied the 0 
	jne .loop
	ret