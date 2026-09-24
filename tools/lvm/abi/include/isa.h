#ifndef ISA_H
#define ISA_H

#include <stdint.h>

/**
 * @brief Instruction. 
 * @note layout:
 	1. OpCode 			: 8 bits
 	2. rd (Destination) : 8 bits 
 	3. rs1 (Source 1)	: 8 bits 
 	4. rs2 (Source 2)	: 8 bits 
 */
typedef uint32_t instruction;
#define INSTRUCTION_BYTES sizeof(instruction)

/**
 * @brief Opcode list.
 */
 #include <stdint.h>

 /**
  * @brief Block-aligned Virtual Machine Opcodes.
  * @note Organized into groups of 16. The high nibble (bits 4-7) dictates the functional unit.
  */
typedef enum : uint8_t {
	/* =========================================================================
	 * GROUP 0 (0x00 - 0x0F / 0 - 15): CONTROL & MEMORY OPERATIONS
	 * Hardware Decoder Hint: if ((opcode >> 4) == 0) -> Route to Core/Bus Controller
	 * ========================================================================= */
	OP_NOP       = 0x00,  // No Operation
	OP_HALT      = 0x01,  // Terminate program execution
	OP_SYS       = 0x02,  // System Call / Software Interrupt
	
	OP_LD        = 0x03,  // Load from heap address to register.
	OP_ST        = 0x04,  // Store from register to heap address
	OP_LDI       = 0x05,  // Load Immediate value into register
	OP_CPY       = 0x06,  // Copy register to register (Register Move)
	OP_LDD		 = 0x07,  // Load Data from rodata 

	/* =========================================================================
	 * GROUP 1 (0x10 - 0x1F / 16 - 31): INTEGER ARITHMETIC (ALU)
	 * Hardware Decoder Hint: if ((opcode >> 4) == 1) -> Route to Integer ALU
	 * ========================================================================= */
	OP_ADD       = 0x10,  // Signed Addition
	OP_SUB       = 0x11,  // Signed Subtraction
	OP_MUL       = 0x12,  // Signed Multiplication
	OP_DIV       = 0x13,  // Signed Division
	OP_MOD       = 0x14,  // Signed Modulo / Remainder
	
	OP_UADD      = 0x15,  // Unsigned Addition
	OP_USUB      = 0x16,  // Unsigned Subtraction
	OP_UMUL      = 0x17,  // Unsigned Multiplication
	OP_UDIV      = 0x18,  // Unsigned Division
	OP_UMOD      = 0x19,  // Unsigned Modulo / Remainder

	/* =========================================================================
	 * GROUP 2 (0x20 - 0x2F / 32 - 47): FLOATING-POINT & BITWISE LOGIC
	 * Hardware Decoder Hint: if ((opcode >> 4) == 2) -> Route to FPU / Bitwise Unit
	 * ========================================================================= */
	OP_FADD      = 0x20,  // Floating-Point Addition
	OP_FSUB      = 0x21,  // Floating-Point Subtraction
	OP_FMUL      = 0x22,  // Floating-Point Multiplication
	OP_FDIV      = 0x23,  // Floating-Point Division
	OP_FMOD      = 0x24,  // Floating-Point Modulo
	
	OP_AND       = 0x25,  // Bitwise AND
	OP_OR        = 0x26,  // Bitwise OR
	OP_XOR       = 0x27,  // Bitwise XOR
	OP_NOT       = 0x28,  // Bitwise NOT (Unary)
	OP_SHL       = 0x29,  // Logical Shift Left
	OP_SHR       = 0x2A,  // Logical Shift Right
	OP_ASL		 = 0x2B,  // Arithmetic Shift Left (Preserves Sign Bit)
	OP_ASR		 = 0x2C,  // Arithmetic Shift Right (Preserved Sign Bit)

	/* =========================================================================
	 * GROUP 3 (0x30 - 0x3F / 48 - 63): CONTROL FLOW & TYPE CONVERSION
	 * Hardware Decoder Hint: if ((opcode >> 4) == 3) -> Route to Branch Predictor/PC Unit
	 * ========================================================================= */
	OP_JMP       = 0x30,  // Unconditional Absolute Jump
	OP_RJMP      = 0x31,  // Unconditional PC-Relative Jump
	
	OP_BR_GT     = 0x32,  // Branch if Greater Than
	OP_BR_LT     = 0x33,  // Branch if Less Than
	OP_BR_EQ     = 0x34,  // Branch if Equal
	OP_BR_NE     = 0x35,  // Branch if Not Equal
	
	OP_CALL      = 0x36,  // Call Subroutine
	OP_RET       = 0x37,  // Return from Subroutine
	OP_PUSH		 = 0x38,
	OP_POP		 = 0x39,
	OP_PUSHR	 = 0x3A,
	OP_POPR		 = 0x3B,
	
	OP_CNV       = 0x3C,  // Type Conversion / Cast
} opcode_t;
 
#define OPCODE_RANGE_1 63	// 0 - 63
#define OPCODE_RANGE_2 95	// 0 - 95
#define OPCODE_RANGE_3 127  // 0 - 127
#define OPCODE_RANGE_4 159  // 0 - 159
#define OPCODE_RANGE_5 191	// 0 - 191
#define OPCODE_RANGE_6 223	// 0 - 223
#define OPCODE_RANGE_max 255 	// 0 - 255


#define CURRENT_OPCODE_RANGE OPCODE_RANGE_1

#endif /* ISA_H */