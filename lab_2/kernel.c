#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

char *vidptr = (char*)0xb8000; // начало видеопамяти
unsigned int current_loc = 0; // палочка указателя


void kprint(const char *str){
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

void kmain(void){
    const char *str = "test keyboard part";
    clear_screen();
    kprint(str);

}