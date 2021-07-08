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
CFLAGS=-c -g -mno-red-zone -ffreestanding

LDFLAGS=-n -o
LD=x86_64-elf-ld

BOOT_SRC_DIR:=$(SRC)/bootloader
BOOT_SRC_ALL:=$(shell find $(BOOT_SRC_DIR) -name *.asm)
BOOT_OBJ=$(patsubst $(BOOT_SRC_DIR)/%.asm, $(BIN)/%.o, $(BOOT_SRC_ALL))

KERNEL_SRC_DIR:=$(SRC)/kernel
KERNEL_SRC_ALL:=$(shell find $(KERNEL_SRC_DIR) -name *.c)
KERNEL_OBJ=$(patsubst $(KERNEL_SRC_DIR)/%.c, $(BIN)/%.o, $(KERNEL_SRC_ALL))
DEPS=-I $(KERNEL_SRC_DIR)/headers

ALL_OBJ:=$(BOOT_OBJ) $(KERNEL_OBJ)

$(BOOT_OBJ): $(BIN)/%.o : $(BOOT_SRC_DIR)/%.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASM_BOOT_FLAGS) $(patsubst $(BIN)/%.o, $(BOOT_SRC_DIR)/%.asm, $@) -o $@

$(KERNEL_OBJ): $(BIN)/%.o : $(KERNEL_SRC_DIR)/%.c
	mkdir -p $(dir $@) && \
	$(CC) $(CFLAGS) $(DEPS) $(patsubst $(BIN)/%.o, $(KERNEL_SRC_DIR)/%.c, $@) -o $@

.PHONY: grub_img
grub_img: $(ALL_OBJ)
	mkdir -p $(DIST) && \
	mkdir -p $(ISO_BOOT)/grub && \
	cp $(GRUB_CFG) $(ISO_BOOT)/grub && \
	$(LD) $(LDFLAGS) $(DIST)/kernel.bin -T $(BOOT_SRC_DIR)/linker.ld $(ALL_OBJ) && \
	cp $(DIST)/kernel.bin $(ISO_BOOT) && \
	grub2-mkrescue /usr/lib/grub/i386-pc -o $(DIST)/kernel.iso $(ISO)

clean:
	rm $(DIST)/*.iso $(DIST)/*.bin
	rm $(BIN)/*.o
	rm $(ISO_BOOT)/*.bin
