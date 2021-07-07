global start

extern set_long_mode
extern k_main

bits 32

section .bss
align 16						; align stack according to SysV ABI
stack_bottom:
	resb 4096*4					; start at some high address (16K)
stack_top:

section .text
start:
		cli
		mov esp, 4096*4

		call set_long_mode
		lgdt [gdt64.ptr]		; load gdt64
		jmp gdt64.code:lm		; set code seg and set data segment - entering long mode

%include "src/bootloader/gdt64.asm"

bits 64
lm:								; enter long mode
		mov ax, gdt64.data
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax

		call k_main				; call kernel

	;	mov dword [0xb8000], 0x2f4b2f4f			; put OK in video mem
		hlt

