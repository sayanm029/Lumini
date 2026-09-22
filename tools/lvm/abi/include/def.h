#ifndef DEF_H
#define DEF_H

#include <stdint.h>
/* ABI version */
#define ABI_VERSION 1


/* VM Word / Address ABI */

#define ABI_WORD_BITS \
    64

#define ABI_WORD_BYTES \
    (ABI_WORD_BITS / 8)

#define ABI_POINTER_BITS \
    ABI_WORD_BITS

#define ABI_POINTER_BYTES \
    ABI_WORD_BYTES

#define ABI_STACK_ALIGN \
    ABI_WORD_BYTES


/* File Descriptor Limits */

#define MAX_FD_LIMIT 512
#define DEFAULT_FD_COUNT 3
#define FD_LIMIT (MAX_FD_LIMIT - DEFAULT_FD_COUNT)

#endif /* DEF_H */