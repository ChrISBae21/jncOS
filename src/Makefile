# Toolchain and Compiler Settings
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-gcc
OBJDUMP = aarch64-linux-gnu-objdump
OBJCOPY = aarch64-linux-gnu-objcopy

# Compiler Flags for 64-bit
CFLAGS = -mcpu=cortex-a53 -ffreestanding -O2 -Wall -Wextra
ASFLAGS =	
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

# Source and Object Files
SOURCES = boot.S kernel.c rrSched.c
OBJECTS = boot.o kernel.o rrSched.o

# Output Files
OUTPUT_ELF = myos.elf
OUTPUT_BIN = myos.bin
OUTPUT_IMG = myos.img

# Default Target
all: $(OUTPUT_IMG)

# Compile Assembly (boot.S)
boot.o: boot.S
	$(AS) $(ASFLAGS) $< -o $@

# Compile C Source (kernel.c)
kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C Source (rrSched.c)
rrSched.o: rrSched.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the Objects into ELF Binary
$(OUTPUT_ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(OUTPUT_ELF) $(OBJECTS)

# Convert ELF to Binary (for .img)
$(OUTPUT_BIN): $(OUTPUT_ELF)
	$(OBJCOPY) -O binary $(OUTPUT_ELF) $(OUTPUT_BIN)

# Create the .img file
$(OUTPUT_IMG): $(OUTPUT_BIN)
	dd if=$(OUTPUT_BIN) of=$(OUTPUT_IMG) bs=512 seek=4

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(OUTPUT_ELF) $(OUTPUT_BIN) $(OUTPUT_IMG)

# Dump ELF File Information (optional)
dump:
	$(OBJDUMP) -D $(OUTPUT_ELF)

.PHONY: all clean dump
