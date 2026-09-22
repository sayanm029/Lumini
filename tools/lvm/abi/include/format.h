#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>
#define LBF_IDENTIFIER_BYTES 16
const char LBF_IDENTIFIER[16] = {'L','V','M','B','y','t','e','c','o','d','e',' ','F','i','l','e'};

typedef struct {
	uint8_t identifier[LBF_IDENTIFIER_BYTES];
	uint32_t memory;
	uint32_t ic;
	uint32_t ds;
	uint32_t entry;
	uint32_t size;
	uint16_t flags;
	uint16_t abi_version;
	uint32_t odata;		// other data
	uint32_t padding;
} lbf_header;

typedef struct {
	lbf_header header;
	uint8_t* program;
	uint8_t* rodata;
} lbf_file;

#define EXECUTABLE_EXTENSION ".lbf"
#define HEADER_SIZE sizeof(lbf_header)

void init_lbf_file(lbf_file* file);
int load_lbf_file(lbf_file* file);
int write_lbf_file(const lbf_file* file);
void free_lbf_file(lbf_file* file);

#endif /* FORMAT_H */