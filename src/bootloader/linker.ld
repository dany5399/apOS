ENTRY(start)

SECTIONS{

	. = 1M;
	
	.boot : {
		KEEP(*(.multiboot_h))
	}

	.text BLOCK(4K) : ALIGN(4K){
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K){
		*(.data)
	}
	
	.bss BLOCK(4K) : ALIGN(4K){
		*(COMMON)
		*(.bss)
	}
}
