#ifndef SYSCALL_H
#define SYSCALL_H

#include "def.h"
#include "reg.h"

/**
 * @note Plain capital identifiers such as RS1 represent direct 8-bit
 *       values encoded in the instruction.
 *
 * @note register[index] means the value stored in register[index].
 *
 * @note When used for a string, register[index] contains the starting
 *       memory address of the string, and the associated length register
 *       contains the string length in bytes.
 */

typedef enum : uint8_t {
    SYSC_TIME = 0,     // Store the current time in RD.

    SYSC_COUT = 1,     // Output register[RD]. RS1 = output type.
    SYSC_CIN  = 2,     // Input a value into register[RD]. RS1 = input type.

    /**
     * @brief Open a file.
     * @param rd Register where the file descriptor will be stored.
     * @param rs1 Register containing the memory address of the filename.
     * @param rs2 Register containing the filename length in bytes.
     */
    SYSC_FOPEN = 3,

    /**
     * @brief Close a file.
     * @param rd Register containing the file descriptor.
     */
    SYSC_FCLOSE = 4,

    /**
     * @brief Seek to a position in a file.
     * @param rd Register containing the file descriptor.
     * @param rs1 Register containing the byte offset.
     * @param rs2 Register containing the seek origin (whence).
     */
    SYSC_FSEEK = 5,

    /**
     * @brief Get the current file position.
     * @param rd Register containing the file descriptor.
     * @param rs1 Register where the current byte offset will be stored.
     */
    SYSC_FPOS = 6,

    /**
     * @brief Read bytes from a file.
     * @param rd Register containing the file descriptor.
     * @note register[TV0] contains the number of bytes to read.
     * @note register[AD0] contains the destination memory address.
     */
    SYSC_FREAD = 7,

    /**
     * @brief Write bytes to a file.
     * @param rd Register containing the file descriptor.
     * @note register[TV0] contains the number of bytes to write.
     * @note register[AD0] contains the source memory address.
     */
    SYSC_FWRITE = 8,

    /**
     * @brief Remove a file.
     * @note register[AD0] contains the memory address of the filename.
     * @note register[AD1] contains the filename length in bytes.
     */
    SYSC_FREMOVE = 9,

    /**
     * @brief Rename a file.
     * @note register[AD0] contains the memory address of the old filename.
     * @note register[AD1] contains the length of the old filename in bytes.
     * @note register[TV0] contains the memory address of the new filename.
     * @note register[TV1] contains the length of the new filename in bytes.
     */
    SYSC_FRENAME = 10,

    /**
     * @brief Create a file.
     * @note register[AD0] contains the memory address of the filename.
     * @note register[AD1] contains the filename length in bytes.
     */
    SYSC_FMAKE = 11,

} syscall_code_t;

#endif