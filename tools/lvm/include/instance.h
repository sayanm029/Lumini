#ifndef INSTANCE_H
#define INSTANCE_H

#include "abi.h"

union register_t {
	int64_t i64;
	uint16_t u64;
	double f64;
};

typedef struct {
	union register_t reg[ABI_REG_COUNT];
	uint8_t* memory;
	uint8_t* program;
	uint8_t* data;

	uint32_t memsize;
	uint32_t program_size;
	uint32_t data_size;
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