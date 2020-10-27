#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>
#include <inttypes.h>

#include "lab1.h"

#define MEMORYSIZE 221 * 1024 * 1024
#define MEMORYSTART 0xF8555978
#define THREADRANDOM 92

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
}

void write_to_memory(void* memory_pointer) {
    uint64_t total = MEMORYSIZE;
    uint64_t block = total / THREADRANDOM; 
    pthread_t thread_id;
    for (uint8_t i = 0; i < THREADRANDOM; i++){
        struct write_to_memory_piece *piece = malloc(sizeof(struct write_to_memory_piece));
        piece->memory_pointer = memory_pointer;
        piece->size = block;
        piece->start = total;

        pthread_create(&thread_id, NULL, write_thread, piece);
    }
    pthread_join(thread_id, NULL);
}

void *write_thread(void *arg){
    struct write_to_memory_piece *piece = (struct write_to_memory_piece*) arg;
    FILE *urand = fopen("/dev/urandom", "r");
    fread((piece->memory_pointer + piece->start), 1, piece->size, urand);
    return 0;
}


int main(int argc, char *argv[]){
    work_with_memory();
    return 0;
}

