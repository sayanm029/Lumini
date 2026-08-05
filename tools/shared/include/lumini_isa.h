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
    OP_NOP,

    /*
    * job: `Stop execution & free memory`.
    */
    OP_HALT,

    /*
    * System Call - Platform Independent.
    * `rd` used as SyscallID Register Index. `reg[rd] used as SyscallID`.
    * `ra & rb are used`
    * job: `do a platform indemendent syscall`
    */
    OP_SYS,

    /*
    * Load Data.
    * `rd` used as target register index.
    * `ra` used as source (memory address) register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Load data from memory`
    */
    OP_LD,

    /*
    * Store Data.
    * `rd` used as target (memory address) register index.
    * `ra` used as source register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Store data in memory.`
    */
    OP_SD,

    /*
    * Load Data Immidiate.
    * `rd` used as target register index.
    * `ra & rb` used as immidiate.
    * job: `rd =(ra << 8) | rb;`
    */
    OP_LDI,

    /*
    * Copy Register.
    * `rd` used as target register index.
    * `ra` used as source register index. 
    * `rb unused`
    */
    OP_CR,

    /*
    * Add Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_I,

    /*
    * Substract Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_I,

    /*
    * Multiply Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_I,

    /*
    * Divide Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_I,

    /*
    * Modulus Integer (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_I,

    /*
    * Add Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_U,

    /*
    * Substract Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_U,

    /*
    * Multiply Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_U,
    
    /*
    * Divide Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_U,

    /*
    * Modulus Unsigned (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_U,

    /*
    * Add Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_F,

    /*
    * Substract Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_F,

    /*
    * Multiply Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_F,

    /*
    * Divide Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_F,

    /*
    * Modulus Floating-point (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_F,

    /*
    * AND (bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra & rb`
    */
    OP_AND,

    /*
    * OR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra | rb`
    */
    OP_OR,

    /*
    * NOT (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register index.
    * `rb unused`.
    * job: `rd =~ra`
    */
    OP_NOT,

    /*
    * XOR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra ^ rb`
    * */
    OP_XOR,

    /* Shift Left (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra << rb`
    * */
    OP_SL,

    /*
    * Shift Right (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    * */
    OP_SR,

    /*
    * Compare Registers.
    * `ra` used as register-1 index.
    * `rb` used as register-2 index.
    * `rd` specifies type.
    * job: `Sets flag register based on comparison result`.
    */
    OP_CR,

    /*
    * Convert Types.
    * `rd` specifies operation.
    * `ra` used as target register index.
    * `rb` used as soucre register index.
    * job: `Converts type of register and stores it in target register`.
    */
    OP_CT,

    /*
    * Jump (Direct).
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * `pc = address`
    */
    OP_JMP,

    /*
    * Conditional Jump.
    * `rd` used as jump address register index.
    * `ra` specifies condition.
    * `rb unused`
    * `pc = address`.
    * jump if `flag == condition`.
    */
    OP_CJMP,

    /*
    * Call.
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * job: push PC+1 into stack then jump to address. and increase stack pointer by 1.
    */
    OP_CALL,

    /*
    * Return.
    * `rd, ra, rb unused`
    * job: pop stack and jump to the address.
    */
    OP_RET,

    OP_COUNT,
} OpCodes;

#endif