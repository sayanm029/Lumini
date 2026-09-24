#include "instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


[[gnu::cold]] bool validate_instance(lvm_instance_t vm) {
	// heap bounds check
	if(vm.hs < MIN_HEAP_SIZE || vm.hs >= MAX_HEAP_SIZE) {return false;}
	// stack bounds check
	if(vm.ss < MIN_STACK_SIZE || vm.hs >= MAX_STACK_SIZE) {return false;}
	// program bounds check
	if(vm.ic*INSTRUCTION_BYTES < MIN_INSTRUCTIONS || vm.ic*INSTRUCTION_BYTES >= MAX_INSTRUCTIONS) {return false;}
	// data bounds check
	if(vm.ds >= MAX_DATA_SIZE) {return false;}
	return true;
}


lvm_instance_t create_instance(void) {
	lvm_instance_t vm = (lvm_instance_t){
		.heap = nullptr,
		.hs = 0,
		.program = nullptr,
		.ic = 0,
		.data = nullptr,
		.ds = 0,
		.stack = nullptr,
		.ss = 0
	};
	memset(vm.reg,0,sizeof(vm.reg));
	return vm;
}

bool setup_instance(lvm_instance_t *instance, lbf_file *file) {
	// nullptr check
	if(instance == nullptr || file == nullptr) {return false;}

	if(validate_instance(*instance) && validate_lbf_file(*file)) {

		/* Borrow program & rodata */
		instance->program = file->program;
		instance->data = file->rodata;

		/* allocate heap for vm heap & stack */
		instance->heap = (uint8_t*)malloc((instance->hs + 7U) & ~7U);		// allocate 8 byte aligned
		if(instance->heap == nullptr) {
			free_lbf_file(file);
			return false;
		}

		instance->stack =(uint8_t*)malloc((instance->ss + 7U) & ~7U);		// allocate 8 byte aligned
		if(instance->stack == nullptr) {
			free_lbf_file(file);
			free(instance->heap);
			return false;
		}

		/* Setup Instance's Tracker Variables */
		instance->reg[REG_PC].u64 = file->header.entry;
		instance->hs = file->header.heap_size;
		instance->ic = file->header.ic;
		instance->ds = file->header.ds;
		instance->ss = file->header.ss;
	} else {return false;}
	return true;
}

void destroy_instance(lvm_instance_t *instance) {
	/* free allocated heap */
	if(instance->heap != nullptr) {free(instance->heap); instance->heap = nullptr;}
	if(instance->stack != nullptr) {free(instance->stack); instance->stack = nullptr;}
	/* set borrowed parameters as nullptr */
	instance->program = nullptr;
	instance->data = nullptr;
}