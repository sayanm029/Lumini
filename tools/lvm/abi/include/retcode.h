#ifndef ERRLIST_H
#define ERRLIST_H

#include <stdint.h>

/**
 * @brief Complete VM Execution Status, Return & Error Codes
 * @note 0x00000000 indicates standard clean, successful execution.
 *       Non-zero numbers represent status changes, hardware traps, or system failures.
 */
typedef enum : uint32_t {
    /* =========================================================================
     * SUCCESS & CONTROL STATUS (Operational Codes)
     * ========================================================================= */
    RC_SUCCESS               = 0x00000000, // Operation completed successfully
    RC_PROGRAM_HALTED        = 0x00000001, // OP_HALT executed; clean application termination

    /* =========================================================================
     * GROUP 1: HARDWARE & MICRO-ARCHITECTURAL TRAPS (ALU / Control Flow / ISA)
     * ========================================================================= */
    RC_E_DIV_BY_ZERO         = 0x00000002, // Division or Modulo by zero (OP_DIV, OP_MOD, OP_FDIV, OP_FMOD)
    RC_E_INTEGER_OVERFLOW    = 0x00000003, // Signed arithmetic overflow/underflow detected
    RC_E_FPU_DOMAIN          = 0x00000004, // Invalid floating-point operation (NaN / Domain error)
    RC_E_ILLEGAL_OPCODE      = 0x00000005, // Hardware decoder encountered an unknown instruction opcode
    RC_E_JMP_MISALIGNED      = 0x00000006, // Control flow target (JMP/BR) is not 32-bit (4-byte) aligned
    RC_E_BRANCH_OUT_OF_BOUNDS= 0x00000007, // Relative jump target points outside valid code segments
    RC_E_INVALID_CAST        = 0x00000008, // OP_CNV failed due to incompatible types or corrupted values
    RC_E_BAD_INSTRUCTION     = 0x00000009, // Invalid Instruction
    RC_E_INSTRUCTION_ALIGNMENT = 0x00000A, // Invalid Instruction Alignment

    /* =========================================================================
     * GROUP 2: MEMORY, BUS & LIFECYCLE MANAGEMENT ERRORS
     * ========================================================================= */
    RC_E_SEGFAULT            = 0x00000010, // Invalid heap access (Load/Store outside VM RAM limits)
    RC_E_BUS_ALIGNMENT       = 0x00000011, // Memory access (OP_LD, OP_ST) violates architecture alignment
    RC_E_BAD_ADDRESS         = 0x00000012, // Pointer provided to a syscall (AD0, TV0, etc.) points to invalid heap
    RC_E_BUFFER_OVERFLOW     = 0x00000013, // Read/Write buffer boundaries exceed valid heap space limits
    RC_E_STACK_OVERFLOW      = 0x00000014, // Call stack exceeded maximum capacity (nested calls)
    RC_E_STACK_UNDERFLOW     = 0x00000015, // Unmatched OP_RET executed with an empty call stack
    RC_E_STRING_OVERFLOW     = 0x00000016,
    /* =========================================================================
     * GROUP 3: SYSTEM CALL / FILESYSTEM ERRORS (ABI Callbacks)
     * ========================================================================= */
    RC_E_PERMISSION_DENIED   = 0x00000020, // EPERM/EACCES: Operation not permitted or file is read-only
    RC_E_FILE_NOT_FOUND      = 0x00000021, // ENOENT: The requested file path string does not exist
    RC_E_BAD_DESCRIPTOR      = 0x00000022, // EBADF: The register does not contain a valid open file descriptor
    RC_E_INVALID_ARGUMENT    = 0x00000023, // EINVAL: Catch-all invalid parameter configuration
    RC_E_INVALID_IO_TYPE     = 0x00000024, // SYSC_COUT/SYSC_CIN: Unknown I/O type identifier passed in RS1
    RC_E_INVALID_SEEK        = 0x00000025, // SYSC_FSEEK: Unrecognized seek origin (whence) code in RS2
    RC_E_TOO_MANY_OPEN_FILES = 0x00000026, // EMFILE: Out of available internal file descriptor slots
    RC_E_NO_SPACE_LEFT       = 0x00000027, // ENOSPC: Storage media or virtual disk partition is full
    RC_E_FILE_EXISTS         = 0x00000028, // EEXIST: Creating a file (SYSC_FMAKE) with a name already in use
    RC_E_IO_FAILURE          = 0x00000029, // EIO: Low-level physical host read/write system failure

} vm_return_code_t;

#endif /* ERRLIST_H */
