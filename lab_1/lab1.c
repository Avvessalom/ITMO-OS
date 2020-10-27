#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>
#include <inttypes.h>

#include "lab1.h"

#define MEMORYSIZE 221 * 1024 * 1024
#define MEMORYSTART 0xF8555978
#define THREADRANDOM 92
#define FILESSIZE 133 * 1024 * 1024
#define IOBLOCK 62

void work_with_memory(){
    void* memory_pointer = (void*) MEMORYSTART;
    memory_pointer = mmap((void*) memory_pointer, MEMORYSIZE,
     PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if (memory_pointer == MAP_FAILED){
        printf("Mapping Failed\n");
    }
    printf("%X", memory_pointer);
    char flag;
    while ((flag = getchar() !='\n' && flag != EOF));
        printf("Press Enter to continue\n");
        getchar();
    write_to_memory(memory_pointer);
    printf("after random now");
    getchar();

    munmap((void*) MEMORYSTART, MEMORYSIZE);
    getchar();
    work_with_file(memory_pointer);
}

void write_to_memory(void* memory_pointer) {
    uint64_t total = MEMORYSIZE;
    uint64_t block = total / THREADRANDOM; 
    pthread_t thread_id;
    void* new_memory_pointer;
    for (uint8_t i = 0; i < THREADRANDOM; i++){
        struct write_to_memory_piece *piece = malloc(sizeof(struct write_to_memory_piece));
        new_memory_pointer = memory_pointer + i;
        piece->memory_pointer = new_memory_pointer;
        piece->size = block;
        piece->start = total;

        pthread_create(&thread_id, NULL, write_thread, piece);
        free(piece);
    }
    pthread_join(thread_id, NULL);
}

void *write_thread(void *arg){
    struct write_to_memory_piece *piece = (struct write_to_memory_piece*) arg;
    FILE *urand = fopen("/dev/urandom", "r");
    fread((piece->memory_pointer + piece->start), 1, piece->size, urand);
    return 0;
}
/*
Записывает область памяти в файлы одинакового размера E (133) мегабайт
с использованием F=(блочного) обращения к диску.
Размер блока ввода-вывода G (62) байт. Преподаватель выдает в качестве
задания последовательность записи/чтения блоковпоследовательный
*/
void work_with_file(void* memory_pointer){
    int files_count = ((MEMORYSIZE) / (FILESSIZE)) + 1;
    for (uint64_t i = 0; i < files_count; i++){
        char* filename = make_filename(i);
        FILE *f = fopen(filename, "wb");
        write_from_memory_to_file(f, memory_pointer);
    }
    
}

void write_from_memory_to_file(FILE *file, void* memory_pointer){
    for (uint64_t counter = 0; counter < FILESSIZE; counter += IOBLOCK){
        fwrite(memory_pointer + counter, sizeof(uint8_t), IOBLOCK, file);
    }
}


int main(int argc, char *argv[]){
    work_with_memory();
    return 0;
}

char* make_filename(int name){
    switch (name)
    {
    case 1:
        return "./first.txt";
    case 2:
        return "./second.txt";
    case 3:
        return "./third.txt";
    case 4:
        return "./forth.txt";
    case 5:
        return "./fiveth.txt";
    default:
        return "./jopa.txt";
    }
}