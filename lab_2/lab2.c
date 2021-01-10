/* генерирует 16-битный код */
__asm__(".code16\n");
/* переходит к точке входа загрузочного кода */
__asm__("jmpl $0x0000, $main\n");

void printString(const char* pStr) {
     while(*pStr) {
          __asm__ __volatile__ (
               "int $0x10" : : "a"(0x0e00 | *pStr), "b"(0x0007)
          );
          ++pStr;
     }
}

void main() {
     /* выводит 'H' */
     __asm__ __volatile__("movb $'H' , %al\n");
     __asm__ __volatile__("movb $0x0e, %ah\n");
     __asm__ __volatile__("int  $0x10\n");
}