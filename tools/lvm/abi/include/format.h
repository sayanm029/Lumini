#ifndef FORMAT_H
#define FORMAT_H
#include "isa.h"
#include "bounds.h"

#include <stdint.h>
#define LBF_IDENTIFIER_BYTES 16
extern const char LBF_IDENTIFIER[16];



typedef struct {
	uint8_t identifier[LBF_IDENTIFIER_BYTES];
	uint32_t heap_size;	// heap size
	uint32_t ic;		// instrcution count
	uint32_t ds;		// data size
	uint32_t ss;		// stack size
	uint32_t entry;		// program entry point
	uint16_t flags;		// flags
	uint16_t abi_version; // abi version
	uint8_t padding[24];	// padding
} lbf_header;

typedef struct {
	lbf_header header;
	uint8_t* program;
	uint8_t* rodata;
} lbf_file;

#define EXECUTABLE_EXTENSION ".lbf"
#define HEADER_SIZE sizeof(lbf_header)
#define MAX_FILE_SIZE (MAX_PROGRAM_SIZE+MAX_DATA_SIZE+HEADER_SIZE)

void init_lbf_file(lbf_file* file);
bool load_lbf_file(lbf_file* file, const char* path);
bool write_lbf_file(const lbf_file* file, const char* path);
void free_lbf_file(lbf_file* file);

/* functions for error handling checks */
bool validate_lbf_file(lbf_file f);

#endif /* FORMAT_H */