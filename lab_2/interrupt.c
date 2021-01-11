#include "keyboard.c"

#define IDT_SIZE 256

struct IDT_entry{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};



struct IDT_entry IDT[IDT_SIZE];
extern write_port(unsigned short port, unsigned char data);
extern load_interrupt(unsigned long *interrupt_ptr);
extern keyboard_handler(void);

void idt_init(void){
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    keyboard_address = (unsigned long)keyboard_handler; 
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    write_port(0x20 , 0x11);
    write_port(0xA0 , 0x11);

    write_port(0x21 , 0x20);
    write_port(0xA1 , 0x28);

    write_port(0x21 , 0x00);  
    write_port(0xA1 , 0x00);  

    write_port(0x21 , 0x01);
    write_port(0xA1 , 0x01);

    write_port(0x21 , 0xff);
    write_port(0xA1 , 0xff);

    idt_address = (unsigned long)IDT ;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16 ;

    load_interrupt(idt_ptr);
}