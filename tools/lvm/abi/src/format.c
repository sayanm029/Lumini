#define _LARGEFILE64_SOURCE 
#include "format.h"
#include "def.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char LBF_IDENTIFIER[16] = {'L','V','M','B','y','t','e','c','o','d','e',' ','F','i','l','e'};

static inline void init_header(lbf_header *header) {
	memcpy(header->identifier,LBF_IDENTIFIER,LBF_IDENTIFIER_BYTES);
	header->heap_size = 0;
	header->ic = 0;
	header->ds = 0;
	header->entry = 0;
	header->flags = 0;
	header->abi_version = ABI_VERSION;
}

static inline bool validate_header(lbf_header header) {
	if(memcmp(header.identifier,LBF_IDENTIFIER,LBF_IDENTIFIER_BYTES) != 0) { return false;}
	if(header.abi_version < ABI_VERSION) {return false;}

	if(header.heap_size < MIN_HEAP_SIZE) {return false;}
	if(header.ic < MIN_INSTRUCTIONS || header.ic > MAX_INSTRUCTIONS) {return false;}
	if(header.ds == MIN_DATA_SIZE || header.ds > MAX_DATA_SIZE) {return false;}
	if(header.entry >= header.ic) {return false;}
	uint64_t size = header.ds + (header.ic*sizeof(instruction));
	if(size > MAX_FILE_SIZE) {return false;}
	return true;
}

bool validate_lbf_file(lbf_file f) {
	// header check
	if(!validate_header(f.header)) {return false;}
	// program & data check
	if(f.program == nullptr) {return false;}
	if(f.header.ds == 0 || f.header.ds >= MAX_DATA_SIZE) {return false;}
	else {if(f.rodata == nullptr) {return false;}}
	return true;
}

void init_lbf_file(lbf_file* file) {
	if(file == nullptr) {return;}
	init_header(&file->header);
	file->program = nullptr;
	file->rodata = nullptr;
}

/*
 * On-disk layout:
 *   [lbf_header][program: header.ic * sizeof(instruction) bytes][rodata: header.ds bytes]
 * Native endianness is assumed; no byte-swapping is performed.
 */

bool load_lbf_file(lbf_file* file, const char* path) {
	if(file == nullptr || path == nullptr) {return false;}

	FILE* fp = fopen(path, "rb");
	if(fp == nullptr) {return false;}

	int fd = fileno(fp);
	if (fd == -1) {
		perror("Error extracting file descriptor"); 
		return false;
	}

	struct stat64 statbuf; // 64-bit struct

	if (fstat64(fd, &statbuf) == -1) {
		perror("Error getting file status"); 
		return false;
	}

	if ((size_t)statbuf.st_size >= (size_t)MAX_FILE_SIZE) {
		fprintf(stderr, "Error: file size is too big\n");
		return false;
	}

	lbf_header header;
	if(fread(&header, sizeof(lbf_header), 1, fp) != 1) {
		fclose(fp);
		return false;
	}

	if(!validate_header(header)) {
		fclose(fp);
		return false;
	}

	file->header = header;
	file->program = nullptr;
	file->rodata = nullptr;

	size_t program_size = (size_t)header.ic * sizeof(instruction);
	file->program = malloc(program_size);
	if(file->program == nullptr) {
		fclose(fp);
		return false;
	}
	if(fread(file->program, 1, program_size, fp) != program_size) {
		free(file->program);
		file->program = nullptr;
		fclose(fp);
		return false;
	}

	if(header.ds > 0) {
		file->rodata = malloc(header.ds);
		if(file->rodata == nullptr) {
			free(file->program);
			file->program = nullptr;
			fclose(fp);
			return false;
		}
		if(fread(file->rodata, 1, header.ds, fp) != header.ds) {
			free(file->program);
			free(file->rodata);
			file->program = nullptr;
			file->rodata = nullptr;
			fclose(fp);
			return false;
		}
	}

	fclose(fp);

	if(!validate_lbf_file(*file)) {
		free_lbf_file(file);
		return false;
	}

	return true;
}

bool write_lbf_file(const lbf_file* file, const char* path) {
	if(file == nullptr || path == nullptr) {return false;}
	if(!validate_lbf_file(*file)) {return false;}

	FILE* fp = fopen(path, "wb");
	if(fp == nullptr) {return false;}

	bool ok = true;

	if(fwrite(&file->header, sizeof(lbf_header), 1, fp) != 1) {ok = false;}

	size_t program_size = (size_t)file->header.ic * sizeof(instruction);
	if(ok && fwrite(file->program, 1, program_size, fp) != program_size) {ok = false;}

	if(ok && file->header.ds > 0) {
		if(fwrite(file->rodata, 1, file->header.ds, fp) != file->header.ds) {ok = false;}
	}

	if(fclose(fp) != 0) {ok = false;}

	return ok;
}

void free_lbf_file(lbf_file* file) {
	if(file == nullptr) {return;}
	if(file->program != nullptr) {free(file->program);}
	if(file->rodata != nullptr) {free(file->rodata);}
	file->program = nullptr;
	file->rodata = nullptr;
}