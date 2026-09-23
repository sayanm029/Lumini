#ifndef INSTANCE_H
#define INSTANCE_H

#include "abi.h"

typedef struct {
	union register_t reg[ABI_REG_COUNT];
	uint8_t* memory;
	uint8_t* program;
	uint8_t* data;
	uint8_t* stack;

	uint32_t ms;	// memory size
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


#endif