all:
	as test.S -o test.o
	ld -Ttext 0x7c00 --oformat=binary test.o -o test.bin
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=test.bin of=floppy.img
start:
	qemu-system-x86_64 floppy.img 

ci:
	cc -c -g -march=x86-64 -Os -ffreestanding -Wall -Werror lab2.c -o lab2.o
	ld -static -Tlab2.ld -nostdlib --nmagic -o lab2.elf lab2.o
	objcopy -O binary lab2.elf lab2.bin
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=lab2.bin of=floppy.img
clear:
	rm -rf *.o *.img *.text *.bin