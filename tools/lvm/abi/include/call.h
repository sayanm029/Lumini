#ifndef CALL_H
#define CALL_H

#include "reg.h"
/* Calling Convention */

#define ABI_MAX_REG_ARGS \
    ABI_ARG_REG_COUNT

#define ABI_ARG_REG(i) \
    (ABI_ARG_REG_START + (i))

#define ABI_RETURN_REG \
    REG_RC

#define ABI_CALLER_SAVED(r) \
    ABI_REG_IS_VOLATILE(r)

#define ABI_CALLEE_SAVED(r) \
    ABI_REG_IS_NONVOLATILE(r)

#endif /* CALL_H */