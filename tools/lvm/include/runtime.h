#include "instance.h"

/**
 * @brief Safe runtime.
 * @param vm instance pointer
 * @return 0 on sucess, on zero on error. 
 */
[[gnu::hot]] int run_instance(lvm_instance_t* vm);
