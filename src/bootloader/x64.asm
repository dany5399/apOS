global set_long_mode

%define PW 0x3
bits 32

section .bss
align 4096
PML4:	resb 4096
PDPT:	resb 4096
PD:		resb 4096
PT:		resb 4096

section .txt
set_long_mode:
	.paging:
		mov edi, PML4			; PML4
		mov cr3, edi
;		xor eax, eax
;		mov ecx, 4096
;		rep stosd				; clear table
;		mov edi, cr3

		mov eax, PDPT
		or eax, PW
		mov [PML4],	eax			; PDPT present + writable
		
		mov eax, PD
		or eax, PW
		mov [PDPT], eax			; PD

		mov eax, PT
		or eax, PW
		mov [PD], eax
								; identity map 2MiB
		mov ecx, 0
	.set_entries:				; only initializing first page table
		mov eax, 0x1000
		mul ecx
		or eax, 0x3
		mov [PT + ecx * 8], eax

		inc ecx
		cmp ecx, 512
		jne .set_entries

	.enable_long_mode:
		mov eax, cr4
		or eax, 1 << 5			; PAE-bit
		mov cr4, eax								
			
		mov ecx, 0xc0000080		; EFER MSR (extended feature enable register - model specific register)
		rdmsr					; read from MSR
		or eax, 0x100			; LM-bit
		wrmsr					; write to MSR

								; enable paging
		mov eax, cr0
		or eax, 0x80000001		; PG + protected
		mov cr0, eax
		ret


