# Toolchain
AS = aarch64-none-elf-as
CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
QEMU = qemu-system-aarch64

# Files
BOOT = boot.s
KERNEL = kernel.c
LINKER = linker.ld
OBJ_BOOT = boot.o
OBJ_KERNEL = kernel.o
PANIC_SRC = panic.s
OBJ_PANIC = panic.o
ELF = kernel.elf

# Check for device.h
ifeq ("$(wildcard device.h)","")
$(error device.h not found! Please run ./configure first)
endif

# Default target
all: build run

# Compile boot.s
$(OBJ_BOOT): $(BOOT)
	$(AS) $< -o $@

# Compile kernel.c
$(OBJ_KERNEL): $(KERNEL)
	$(CC) -ffreestanding -c $< -o $@

$(OBJ_PANIC): $(PANIC_SRC)
	aarch64-none-elf-as $< -o $@

$(ELF): $(OBJ_BOOT) $(OBJ_KERNEL) $(OBJ_PANIC) $(LINKER)
	aarch64-none-elf-ld -nostdlib -T $(LINKER) $(OBJ_BOOT) $(OBJ_KERNEL) $(OBJ_PANIC) -o $@

# Build kernel
build: $(ELF)

# Run in QEMU
run: $(ELF)
	$(QEMU) -machine virt -cpu cortex-a57 -kernel $(ELF) -m 128M -nographic

# Clean up
clean:
	rm -f $(OBJ_BOOT) $(OBJ_KERNEL) $(ELF)

config_virt:
	./configure 0x09000000 "Qemu Aarch64 Virt Machine" 1
