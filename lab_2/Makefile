all:
	nasm -f elf32 kernel.asm -o kasm.o
	gcc -m32 -c -fno-stack-protector   kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

start:
	qemu-system-i386 -kernel kernel

clear:
	rm -rf *.o kernel