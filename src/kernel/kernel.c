#include "console.h"
#include "kprintf.h"
#include "multiboot.h"

void kmain(/*struct multiboot_tag_basic_meminfo* meminfo, uint32_t magic*/){
	//*
	unsigned long long sp, cr3;

	asm("mov %%rsp, %0\n\t"
		"mov %%cr3, %1\n\t"
		: "=r" (sp), "=r" (cr3)
		: 
	);

	kprintf("rsp: %x\n", sp);
	kprintf("cr3: %x\n", cr3);
	//*/
	//kprintf("%d\n", meminfo->mem_lower);
}
