#ifndef INSTANCE_H
#define INSTANCE_H

#include "abi.h"

typedef enum {
	LVM_STATE_INITIALIZED = 0,
	LVM_INSTANCE_READY = 1,
	LVM_STATE_FREED = 2,
} lvm_state;

typedef struct {
	unsigned int state;
	union register_t reg[ABI_REG_COUNT];
	uint8_t* heap;
	uint8_t* program;
	uint8_t* data;
	uint8_t* stack;

	uint32_t hs;	// heap size
	uint32_t ic;	// instruction count
	uint32_t ds;	// data size

	uint32_t ss;	// stack size
} lvm_instance_t;

/* lvm instance life cycle functions. */

/**
 * @brief Create a instance
 */
lvm_instance_t create_instance(void);
/**
 * @brief Set the up instance
 * 
 * @param instance vm instance
 * @param file lbf file
 * @return true on sucess.
 * @return false on failure .
 */
bool setup_instance(lvm_instance_t *instance,lbf_file* file);
/**
 * @brief Destory instance
 * 
 * @param instance vm instance
 */
void destroy_instance(lvm_instance_t* instance);



/* Functions for error handling checks */
bool validate_instance(lvm_instance_t vm);


#endif