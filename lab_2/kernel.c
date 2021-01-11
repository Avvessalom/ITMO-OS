#include "kernel.h"
#include "keyboard.c"

// char *vidptr = (char*)VIDEO_START; // начало видеопамяти
// unsigned int current_loc = 0; // каретка указателя


void print(const char *str){
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void clear_screen(void){
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}


void kernel_main(void){
    const char *str = "test keyboard part";
    clear_screen();
    print(str);
    print_newline();
    print_newline();

	idt_init();
	kb_init();
	while (1);
	
}