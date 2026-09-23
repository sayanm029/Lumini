/* Runtime Bounds Meta */
#ifndef BOUNDS_H
#define BOUNDS_H

#include "reg.h"

/* Memory is VM's heap.*/

// Heap, stack,program, data combined:
#define TOTAL_MAX_MEMORY (1ULL << 32) // 4 GB

#define MAX_HEAP_SIZE (3ULL << 30)	// 3 GB
#define MAX_STACK_SIZE (256ULL << 20) // 256 MB
#define MAX_DATA_SIZE (128ULL << 20) // 128 MB
#define MAX_PROGRAM_SIZE (640ULL << 20) // 640 MB

#define TOTAL_MIN_MEMORY 4096 // 4 KB

#define MIN_HEAP_SIZE 3840ULL     // 3840 Bytes
#define MIN_STACK_SIZE 128ULL       // 128 Bytes

#define MIN_DATA_SIZE 0       // 0 Bytes
#define MIN_PROGRAM_SIZE 128ULL     // 128 Bytes

#define MAX_INSTRUCTIONS (MAX_PROGRAM_SIZE / sizeof(instruction))
#define MIN_INSTRUCTIONS (MIN_PROGRAM_SIZE / sizeof(instruction))

#endif