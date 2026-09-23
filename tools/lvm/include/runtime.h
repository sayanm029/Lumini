#include "instance.h"

/**
 * @brief Safe runtime.
 * @param vm instance pointer
 * @return 0 on sucess, on zero on error. 
 */
[[gnu::hot]] int run_instance(lvm_instance_t* vm);
/**
 * @brief Shows message on return code after execution.
 * @param return_code returned form `run_instance()`
 */
void show_message_on_return(int return_code);