SRC=src

BUILD=build
BIN=$(BUILD)/bin

DIST=dist
TARGETS=targets
ISO=$(TARGETS)/iso
ISO_BOOT=$(ISO)/boot

CONFIG_DIR=config
GRUB_CFG=$(CONFIG_DIR)/grub/grub.cfg

ASM=nasm
ASM_BOOT_FLAGS=-felf64

CC=x86_64-elf-gcc
CFLAGS=-mno-red-zone

LDFLAGS=-n -o
LD=x86_64-elf-ld

BOOT_SRC_DIR:=$(SRC)/bootloader
BOOT_SRC_ALL:=$(shell find $(BOOT_SRC_DIR) -name *.asm)
BOOT_OBJ=$(patsubst $(BOOT_SRC_DIR)/%.asm, $(BIN)/%.bin, $(BOOT_SRC_ALL))

$(BOOT_OBJ): $(BIN)/%.bin : $(BOOT_SRC_DIR)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASM_BOOT_FLAGS) $(patsubst $(BIN)/%.bin, $(BOOT_SRC_DIR)/%.asm, $@) -o $@

.PHONY: boot
boot: $(BOOT_OBJ)
	mkdir -p $(DIST) && \
	mkdir -p $(ISO_BOOT)/grub && \
	cp $(GRUB_CFG) $(ISO_BOOT)/grub && \
	$(LD) $(LDFLAGS) $(DIST)/kernel.bin -T $(BOOT_SRC_DIR)/linker.ld $(BOOT_OBJ) && \
	cp $(DIST)/kernel.bin $(ISO_BOOT) && \
	grub2-mkrescue /usr/lib/grub/i386-pc -o $(DIST)/kernel.iso $(ISO)

clean:
	rm $(DIST)/*.iso $(DIST)/*.bin
	rm $(BIN)/*.bin
	rm $(ISO_BOOT)/*.bin
