#ifndef FORMAT_H
#define FORMAT_H
#include "isa.h"

#include <stdint.h>
#define LBF_IDENTIFIER_BYTES 16
const char LBF_IDENTIFIER[16] = {'L','V','M','B','y','t','e','c','o','d','e',' ','F','i','l','e'};

#define MAX_FILE_SIZE 1ULL << 32		// 4 GB

#define MIN_MEMORY_SIZE 1ULL << 12		// 4 KB
#define MAX_MEMORY_SIZE 1ULL << 32		// 4 GB

#define MIN_DATA_SIZE 0ULL
#define MAX_DATA_SIZE 1ULL << 31

#define MAX_PROGRAM_SIZE 1ULL << 31
#define MAX_INSTRUCTIONS (MAX_PROGRAM_SIZE / sizeof(instruction))

#define MIN_PROGRAM_SIZE (sizeof(instruction))
#define MIN_INSTRUCTIONS 1


typedef struct {
	uint8_t identifier[LBF_IDENTIFIER_BYTES];
	uint32_t memory;
	uint32_t ic;
	uint32_t ds;
	uint32_t entry;
	uint16_t flags;
	uint16_t abi_version;
	uint8_t padding[28];
} lbf_header;

typedef struct {
	lbf_header header;
	uint8_t* program;
	uint8_t* rodata;
} lbf_file;

#define EXECUTABLE_EXTENSION ".lbf"
#define HEADER_SIZE sizeof(lbf_header)

void init_lbf_file(lbf_file* file);
bool load_lbf_file(lbf_file* file, const char* path);
bool write_lbf_file(const lbf_file* file, const char* path);
void free_lbf_file(lbf_file* file);

#endif /* FORMAT_H */