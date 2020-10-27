#ifndef LAB1_H
#define LAB2_H
#include <stdint.h>
void write_to_memory(void* memory_pointer);
void work_with_memory();
void *write_thread(void *arg);
void work_with_file(void* memory_pointer);
void write_from_memory_to_file(FILE *file, void* memory_pointer);
char* make_filename(int name);
struct write_to_memory_piece {
    void* memory_pointer;
    uint64_t size;
    uint64_t start;
};

#endif