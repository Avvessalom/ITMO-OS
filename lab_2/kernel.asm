[bits 16]
section .text
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum

global start
global keyboard_handler
global read_port
global write_port
global load_idt

extern kernel_main
extern keyboard_handler_main
extern clear_screen

read_port:
	mov edx, [esp + 4]
	in al, dx	;dx is the lower 16 bits of edx
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti 				
	ret

keyboard_handler:                 
	call    keyboard_handler_main
	iretd

start:
  xor ax, ax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  cli
  xor ax, ax
  mov ds, ax
  lgdt[gdt_descriptor]
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax
  jmp protected


[bits 32]
protected:
  cli
  mov esp, stack_space
  call kernel_main
  hlt

gdt_start:

gdt_null:
  dd 0x0
  dd 0x0

gdt_code:
  dw 0xffff
  dw 0x0
  dw 0x0
  db 10011010b
  db 11001111b
  db 0x0

gdt_data
  dw 0xffff
  dw 0x0
  db 0x0
  db 10011010b
  db 11001111b
  db 0x0
gdt_end:

gdt_descriptor:
  dw gdt_end - gdt_start - 1
  dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


section .bss
resb 8192
stack_space: