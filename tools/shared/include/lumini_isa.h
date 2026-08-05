#ifndef LUMINI_ISA_H
#define LUMINI_ISA_H
#include <stdint.h>

/* ----- ISA Configurations ----- */
#define ISA_TYPE "64-bit"
#define ISA_PLATFORM "Virtual-Machine"
#define ISA_VERSION 1

/* ----- ISA (System) Configurations ----- */
#define TOTAL_REGISTERS 256
#define MAX_REGISTER_INDEX 255



/* ----- Data Structures, Aliases & Function Definitions ----- */
typedef uint64_t register_t;        // register data type
typedef uint32_t instruction_t;     // instruction data type

typedef struct {
    uint8_t op; // Opcode
    uint8_t rd; // Destination register
    uint8_t ra; // Source register A
    uint8_t rb; // Source register B
} decoded_instruction_t;

// Function used to encode / pack the instruction
inline instruction_t encode_instruction(decoded_instruction_t i);
// Function used to decode / unpack the instruction
inline decoded_instruction_t decode_instruction(instruction_t i);

typedef enum {
    /*
    * job: `Do nothing`.
    */
    OP_NOP      = 0U,

    /*
    * job: `Stop execution & free memory`.
    */
    OP_HALT     = 1U,

    /*
    * System Call - Platform Independent.
    * `rd` used as SyscallID Register Index. `reg[rd] used as SyscallID`.
    * `ra & rb are used`
    * job: `do a platform indemendent syscall`
    */
    OP_SYS      = 2U,

    /*
    * Load Data.
    * `rd` used as target register index.
    * `ra` used as source (memory address) register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Load data from memory`
    */
    OP_LD       = 3U,

    /*
    * Store Data.
    * `rd` used as target (memory address) register index.
    * `ra` used as source register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Store data in memory.`
    */
    OP_SD       = 4U,

    /*
    * Load Data Immidiate.
    * `rd` used as target register index.
    * `ra & rb` used as immidiate.
    * job: `rd =(ra << 8) | rb;`
    */
    OP_LDI      = 5U,

    /*
    * Copy Register.
    * `rd` used as target register index.
    * `ra` used as source register index. 
    * `rb unused`
    */
    OP_CR       = 6U,

    /*
    * Add Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_I    = 16U,

    /*
    * Substract Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_I    = 17U,

    /*
    * Multiply Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_I    = 18U,

    /*
    * Divide Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_I    = 19U,

    /*
    * Modulus Integer (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_I    = 20U,

    /*
    * Add Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_U    = 30U,

    /*
    * Substract Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_U    = 31U,

    /*
    * Multiply Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_U    = 32U,
    
    /*
    * Divide Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_U    = 33U,

    /*
    * Modulus Unsigned (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_U    = 34U,

    /*
    * Add Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_F    = 44U,

    /*
    * Substract Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_F    = 45U,

    /*
    * Multiply Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_F    = 46U,

    /*
    * Divide Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_F    = 47U,

    /*
    * Modulus Floating-point (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_F    = 48U,

    /*
    * AND (bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra & rb`
    */
    OP_AND      = 58U,

    /*
    * OR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra | rb`
    */
    OP_OR       = 59U,

    /*
    * NOT (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register index.
    * `rb unused`.
    * job: `rd =~ra`
    */
    OP_NOT      = 60U,

    /*
    * XOR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra ^ rb`
    * */
    OP_XOR      = 61U,

    /* Shift Left (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd = ra << rb`
    * */
    OP_SL       = 62U,

    /*
    * Shift Right (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd = ra >> rb`
    * */
    OP_SR       = 63U,

    /*
    * Compare Registers.
    * `ra` used as register-1 index.
    * `rb` used as register-2 index.
    * `rd` specifies type.
    * job: `Sets flag register based on comparison result`.
    */
    OP_CMPR     = 73U,

    /*
    * Convert Types.
    * `rd` specifies operation.
    * `ra` used as target register index.
    * `rb` used as soucre register index.
    * job: `Converts type of register and stores it in target register`.
    */
    OP_CT       = 74U,

    /*
    * Jump (Direct).
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * `pc = address`
    */
    OP_JMP      = 84U,

    /*
    * Conditional Jump.
    * `rd` used as jump address register index.
    * `ra` specifies condition.
    * `rb unused`
    * `pc = address`.
    * jump if `flag == condition`.
    */
    OP_CJMP     = 85U,

    /*
    * Call.
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * job: push PC+1 into stack then jump to address. and increase stack pointer by 1.
    */
    OP_CALL     = 86U,

    /*
    * Return.
    * `rd, ra, rb unused`
    * job: pop stack and jump to the address.
    */
    OP_RET      = 87U,

} OpCodes;

#endif