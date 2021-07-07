section .rodata
gdt64:
	.null: equ $ - gdt64
		dq 0
	;	dw 0xFFFF				; limit 0:15
	;	dw 0					; base 0:15
	;	db 0					; base 16:23
	;	db 0					; access
	;	db 1					; granularity, flags, limit 16:19
	;	db 0					; base 24:31
	.code: equ $ - gdt64
	;	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
		dw 0
		dw 0
		db 0
		db 10011010b
		db 10101111b
		db 0
	.data: equ $ - gdt64
		dw 0
		dw 0
		db 0
		db 10010010b
		db 00000000b
		db 0
	.ptr:
		dw $ - gdt64 - 1			; limit
		dq gdt64					; base

