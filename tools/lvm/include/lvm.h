#ifndef LVM_H
#define LVM_H

#define LVM_VERSION_MAJOR 1
#define LVM_VERSION_MINOR 0

#if defined(__x86_64__) || defined(_M_X64)
    #define SYSTEM_ARCH "x86_64"
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define SYSTEM_ARCH "arm64"
#elif defined(__arm__) || defined(_M_ARM)
    #define SYSTEM_ARCH "arm"
#else
    #define SYSTEM_ARCH "unknown"
#endif



#include "abi.h"
#include "instance.h"
#include "runtime.h"

#endif