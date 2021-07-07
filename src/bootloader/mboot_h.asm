%define BOOT_SIG	0xe85250d6
%define BASE		0x100000000

section .multiboot_h
m_start:
	dd BOOT_SIG
	dd 0
	dd m_end - m_start
	dd BASE - (BOOT_SIG + 0 + (m_end - m_start))	; 0 puts an extra double

	dw 0
	dw 0
	dd 8
m_end:
