OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
 {
   . = 0x7c00;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
 }