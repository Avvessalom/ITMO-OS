all:
	nasm -felf32  kernel.asm -o kasm.o
	gcc -fno-stack-protector -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

start:
	qemu-system-i386 -kernel kernel

clear:
	rm -rf *.o kernel