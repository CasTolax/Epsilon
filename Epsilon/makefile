CROSS_CC := i686-elf-gcc
CROSS_LD := i686-elf-ld
CC := $(shell command -v $(CROSS_CC) >/dev/null 2>&1 && echo $(CROSS_CC) || echo gcc)
LD := $(shell command -v $(CROSS_LD) >/dev/null 2>&1 && echo $(CROSS_LD) || echo ld)

FILES = ./bootloader/build/kernel.asm.o ./bootloader/build/kernel.o ./bootloader/build/eprint.o
FLAGS = -g -ffreestanding -fno-pie -nostdlib -nostartfiles -nodefaultlibs -Wall -O0
LDFLAGS =

ifeq ($(CC),gcc)
FLAGS += -m32
LDFLAGS += -m elf_i386
endif

.PHONY: all build clean
all: build

build:
	mkdir -p ./bootloader/bin
	mkdir -p ./bootloader/build
	mkdir -p ./build
	nasm -f bin ./bootloader/src/boot.asm -o ./bootloader/bin/boot.bin
	nasm -f elf -g ./bootloader/src/kernel.asm -o ./bootloader/build/kernel.asm.o
	$(CC) -I./kernel $(FLAGS) -std=gnu99 -c ./kernel/kernel.c -o ./bootloader/build/kernel.o
	$(CC) -I./kernel $(FLAGS) -std=gnu99 -c ./kernel/eprint.c -o ./bootloader/build/eprint.o
	$(LD) -m elf_i386 $(LDFLAGS) -g -relocatable $(FILES) -o ./build/completeKernel.o
	$(CC) $(FLAGS) -no-pie -T ./linker.ld -o ./bootloader/bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/completeKernel.o

	dd if=./bootloader/bin/boot.bin >> ./bootloader/bin/os.bin
	dd if=./bootloader/bin/kernel.bin >> ./bootloader/bin/os.bin
	dd if=/dev/zero bs=512 count=8 >> ./bootloader/bin/os.bin


run: build
	qemu-system-x86_64 -drive format=raw,file=./bootloader/bin/os.bin

clean:
	rm -f ./bootloader/bin/boot.bin
	rm -f ./bootloader/bin/kernel.bin
	rm -f ./bootloader/bin/os.bin
	rm -f ./bootloader/build/kernel.asm.o
	rm -f ./bootloader/build/kernel.o
	rm -f ./bootloader/build/eprint.o
	rm -f ./build/completeKernel.o

