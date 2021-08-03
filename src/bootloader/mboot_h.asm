%define MULTIBOOT2_HEADER_MAGIC	0xe85250d6
%define BASE		0x100000000

global mem_info_tag

section .multiboot_h
m_start:
	dd MULTIBOOT2_HEADER_MAGIC
	dd 0
	dd m_end - m_start
	dd BASE - (MULTIBOOT2_HEADER_MAGIC + 0 + (m_end - m_start))	; 0 puts an extra double

;mem_info_tag:
;	dw 4
;	dw 16
;	dw 0
;	dw 0

end_tag:
	dw 0
	dw 0
	dd 8

m_end:
