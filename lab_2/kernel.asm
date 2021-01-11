bits 32
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
  cli
  mov esp, stack_space
  call kernel_main
  hlt

section .bss
resb 8192
stack_space: