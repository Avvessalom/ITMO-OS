#ifndef LAB1_H
#define LAB2_H
#include <stdint.h>
void write_to_memory(void* memory_pointer);
void work_with_memory();
void *write_thread(void *arg);
struct write_to_memory_piece {
    void* memory_pointer;
    uint64_t size;
    uint64_t start;
};

#endif