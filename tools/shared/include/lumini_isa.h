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


/* 
* Grouping of opcodes:
* Opcodes per group: 16
* current groups: 8
* 1. System, 
* 2. Memory, 
* 3. Signed Arithmetic, 
* 4. Unsigned Arithmetic, 
* 5. Floating-Point Arithmetic, 
* 6. Bitwise
* 7. Special
* 8. Jump,Branching & Subroutine.
*/

// OpCodes
typedef enum {

    // ---------- 1. System ----------

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

    // ---------- 2. Memory ----------


    /*
    * Load Data.
    * `rd` used as target register index.
    * `ra` used as source (memory address) register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Load data from memory`
    */
    OP_LD       = 16U,

    /*
    * Store Data.
    * `rd` used as target (memory address) register index.
    * `ra` used as source register index.
    * `rb` specifies bytes. Maximum: 8
    * job: `Store data in memory.`
    */
    OP_SD       = 17U,

    /*
    * Load Data Immidiate.
    * `rd` used as target register index.
    * `ra & rb` used as immidiate.
    * job: `rd =(ra << 8) | rb;`
    */
    OP_LDI      = 18U,

    /*
    * Copy Register.
    * `rd` used as target register index.
    * `ra` used as source register index. 
    * `rb unused`
    */
    OP_CR       = 19U,

    // ---------- 3. Signed Arithmetic ----------

    /*
    * Add Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_I    = 32U,

    /*
    * Substract Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_I    = 33U,

    /*
    * Multiply Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_I    = 34U,

    /*
    * Divide Integer.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_I    = 35U,

    /*
    * Modulus Integer (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_I    = 36U,

    // ---------- 4. Unsigned Arithmetic ----------

    /*
    * Add Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */
    OP_ADD_U    = 48U,

    /*
    * Substract Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_U    = 49U,

    /*
    * Multiply Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_U    = 50U,
    
    /*
    * Divide Unsigned.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_U    = 51U,

    /*
    * Modulus Unsigned (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_U    = 52U,

    /*
    * Add Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra + rb`
    */

    // ---------- 5. Floating-Point Arithmetic ----------

    OP_ADD_F    = 64U,

    /*
    * Substract Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra - rb`
    */
    OP_SUB_F    = 65U,

    /*
    * Multiply Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra * rb`
    */
    OP_MUL_F    = 66U,

    /*
    * Divide Floating-point.
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra / rb`
    */
    OP_DIV_F    = 67U,

    /*
    * Modulus Floating-point (Remainder).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra % rb`
    */
    OP_MOD_F    = 68U,

    // ---------- 6. Bitwise ----------

    /*
    * AND (bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra & rb`
    */
    OP_AND      = 80U,

    /*
    * OR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra | rb`
    */
    OP_OR       = 81U,

    /*
    * NOT (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register index.
    * `rb unused`.
    * job: `rd =~ra`
    */
    OP_NOT      = 82U,

    /*
    * XOR (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd =ra ^ rb`
    * */
    OP_XOR      = 83U,

    /* Shift Left (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd = ra << rb`
    * */
    OP_SL       = 84U,

    /*
    * Shift Right (Bitwise).
    * `rd` used as target register index.
    * `ra` used as source register-1 index.
    * `rb` used as source register-2 index.
    * job: `rd = ra >> rb`
    * */
    OP_SR       = 85U,

    // ---------- 7. Special ----------
    /*
    * Compare Registers.
    * `ra` used as register-1 index.
    * `rb` used as register-2 index.
    * `rd` specifies type.
    * job: `Sets flag register based on comparison result`.
    */
    OP_CMPR     = 96U,
    
    /*
    * Convert Types.
    * `rd` specifies operation.
    * `ra` used as target register index.
    * `rb` used as soucre register index.
    * job: `Converts type of register and stores it in target register`.
    */
    OP_CT       = 97U,

    /*
    * Jump (Direct).
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * `pc = address`
    */


    // 8. ---------- Jump & Branching ----------

    OP_JMP      = 112U,

    /*
    * Conditional Jump.
    * `rd` used as jump address register index.
    * `ra` specifies condition.
    * `rb unused`
    * `pc = address`.
    * jump if `flag == condition`.
    */
    OP_CJMP     = 113U,

    /*
    * Call.
    * `rd` used as jump address register index.
    * `ra & rb unused`.
    * job: push PC+1 into stack then jump to address. and increase stack pointer by 1.
    */
    OP_CALL     = 114U,

    /*
    * Return.
    * `rd, ra, rb unused`
    * job: pop stack and jump to the address.
    */
    OP_RET      = 115U,

} OpCodes;

#endif