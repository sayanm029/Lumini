#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LIKELY(x)       __builtin_expect(!!(x), 1)
#define UNLIKELY(x)     __builtin_expect(!!(x), 0)


[[gnu::hot]] int run_instance(lvm_instance_t* vm) {
	// instance check
	if(vm == nullptr) {return -1;}
	if(!validate_instance(*vm)) {return -1;}

	/*
	=========================================================================
					Dispatch Table 
	=========================================================================
	*/

	
[[maybe_unused]] static void* table[] = {
	//  GROUP 0 : CONTROL & MEMORY OPERATIONS
	[0] = &&op_nop,[1] = &&op_halt,[2] = &&op_sys,[3] = &&op_ld,[4] = &&op_st,[5] = &&op_ldi,[6] = &&op_cpy,[7] = &&op_ldd,[8] = &&bad_opcode,[9] = &&bad_opcode,[10] = &&bad_opcode,[11] = &&bad_opcode,[12] = &&bad_opcode,[13] = &&bad_opcode,[14] = &&bad_opcode,[15] = &&bad_opcode,
	// GROUP 1 : INTEGER ARITHMETIC
	[16] = &&op_add,[17] = &&op_sub,[18] = &&op_mul,[19] = &&op_div,[20] = &&op_mod,[21] = &&op_uadd,[22] = &&op_usub,[23] = &&op_umul,[24] = &&op_udiv,[25] = &&op_umod,[26] = &&bad_opcode,[27] = &&bad_opcode,[28] = &&bad_opcode,[29] = &&bad_opcode,[30] = &&bad_opcode,[31] = &&bad_opcode,
	// GROUP 2 : FLOATING-POINT & BITWISE LOGIC
	[32] = &&op_fadd,[33] = &&op_fsub,[34] = &&op_fmul,[35] = &&op_fdiv,[36] = &&op_fmod,[37] = &&op_and,[38] = &&op_or,[39] = &&op_not,[40] = &&op_xor,[41] = &&op_shl,[42] = &&op_shr,[43] = &&op_asl,[44] = &&op_asr,[45] = &&bad_opcode,[46] = &&bad_opcode,[47] = &&bad_opcode,
	//  GROUP 3 : CONTROL FLOW & TYPE CONVERSION
	[48] = &&op_jmp,[49] = &&op_rjmp,[50] = &&op_br_gt,[51] = &&op_br_lt,[52] = &&op_br_eq,[53] = &&op_br_ne,[54] = &&op_call,[55] = &&op_ret,[56] = &&op_push,[57] = &&op_pop,[58] = &&bad_opcode,[59] = &&bad_opcode,[60] = &&op_cnv,[61] = &&bad_opcode,[62] = &&bad_opcode,[63] = &&bad_opcode,
	#if (CURRENT_OPCODE_RANGE > OPCODE_RANGE_1)
	[64] = &&bad_opcode,[65] = &&bad_opcode,[66] = &&bad_opcode,[67] = &&bad_opcode,[68] = &&bad_opcode,[69] = &&bad_opcode,[70] = &&bad_opcode,[71] = &&bad_opcode,[72] = &&bad_opcode,[73] = &&bad_opcode,[74] = &&bad_opcode,[75] = &&bad_opcode,[76] = &&bad_opcode,[77] = &&bad_opcode,[78] = &&bad_opcode,[79] = &&bad_opcode,

	[80] = &&bad_opcode,[81] = &&bad_opcode,[82] = &&bad_opcode,[83] = &&bad_opcode,[84] = &&bad_opcode,[85] = &&bad_opcode,[86] = &&bad_opcode,[87] = &&bad_opcode,[88] = &&bad_opcode,[89] = &&bad_opcode,[90] = &&bad_opcode,[91] = &&bad_opcode,[92] = &&bad_opcode,[93] = &&bad_opcode,[94] = &&bad_opcode,[95] = &&bad_opcode,
	#elif (CURRENT_OPCODE_RANGE > OPCODE_RANGE_2)
	[96] = &&bad_opcode,[97] = &&bad_opcode,[98] = &&bad_opcode,[99] = &&bad_opcode,[100] = &&bad_opcode,[101] = &&bad_opcode,[102] = &&bad_opcode,[103] = &&bad_opcode,[104] = &&bad_opcode,[105] = &&bad_opcode,[106] = &&bad_opcode,[107] = &&bad_opcode,[108] = &&bad_opcode,[109] = &&bad_opcode,[110] = &&bad_opcode,[111] = &&bad_opcode,

	[112] = &&bad_opcode,[113] = &&bad_opcode,[114] = &&bad_opcode,[115] = &&bad_opcode,[116] = &&bad_opcode,[117] = &&bad_opcode,[118] = &&bad_opcode,[119] = &&bad_opcode,[120] = &&bad_opcode,[121] = &&bad_opcode,[122] = &&bad_opcode,[123] = &&bad_opcode,[124] = &&bad_opcode,[125] = &&bad_opcode,[126] = &&bad_opcode,[127] = &&bad_opcode,
	#elif (CURRENT_OPCODE_RANGE > OPCODE_RANGE_3)
	[128] = &&bad_opcode,[129] = &&bad_opcode,[130] = &&bad_opcode,[131] = &&bad_opcode,[132] = &&bad_opcode,[133] = &&bad_opcode,[134] = &&bad_opcode,[135] = &&bad_opcode,[136] = &&bad_opcode,[137] = &&bad_opcode,[138] = &&bad_opcode,[139] = &&bad_opcode,[140] = &&bad_opcode,[141] = &&bad_opcode,[142] = &&bad_opcode,[143] = &&bad_opcode,

	[144] = &&bad_opcode,[145] = &&bad_opcode,[146] = &&bad_opcode,[147] = &&bad_opcode,[148] = &&bad_opcode,[149] = &&bad_opcode,[150] = &&bad_opcode,[151] = &&bad_opcode,[152] = &&bad_opcode,[153] = &&bad_opcode,[154] = &&bad_opcode,[155] = &&bad_opcode,[156] = &&bad_opcode,[157] = &&bad_opcode,[158] = &&bad_opcode,[159] = &&bad_opcode,
	#elif (CURRENT_OPCODE_RANGE > OPCODE_RANGE_4)
	[160] = &&bad_opcode,[161] = &&bad_opcode,[162] = &&bad_opcode,[163] = &&bad_opcode,[164] = &&bad_opcode,[165] = &&bad_opcode,[166] = &&bad_opcode,[167] = &&bad_opcode,[168] = &&bad_opcode,[169] = &&bad_opcode,[170] = &&bad_opcode,[171] = &&bad_opcode,[172] = &&bad_opcode,[173] = &&bad_opcode,[174] = &&bad_opcode,[175] = &&bad_opcode,

	[176] = &&bad_opcode,[177] = &&bad_opcode,[178] = &&bad_opcode,[179] = &&bad_opcode,[180] = &&bad_opcode,[181] = &&bad_opcode,[182] = &&bad_opcode,[183] = &&bad_opcode,[184] = &&bad_opcode,[185] = &&bad_opcode,[186] = &&bad_opcode,[187] = &&bad_opcode,[188] = &&bad_opcode,[189] = &&bad_opcode,[190] = &&bad_opcode,[191] = &&bad_opcode,
	#elif (CURRENT_OPCODE_RANGE > OPCODE_RANGE_5)
	[192] = &&bad_opcode,[193] = &&bad_opcode,[194] = &&bad_opcode,[195] = &&bad_opcode,[196] = &&bad_opcode,[197] = &&bad_opcode,[198] = &&bad_opcode,[199] = &&bad_opcode,[200] = &&bad_opcode,[201] = &&bad_opcode,[202] = &&bad_opcode,[203] = &&bad_opcode,[204] = &&bad_opcode,[205] = &&bad_opcode,[206] = &&bad_opcode,[207] = &&bad_opcode,

	[208] = &&bad_opcode,[209] = &&bad_opcode,[210] = &&bad_opcode,[211] = &&bad_opcode,[212] = &&bad_opcode,[213] = &&bad_opcode,[214] = &&bad_opcode,[215] = &&bad_opcode,[216] = &&bad_opcode,[217] = &&bad_opcode,[218] = &&bad_opcode,[219] = &&bad_opcode,[220] = &&bad_opcode,[221] = &&bad_opcode,[222] = &&bad_opcode,[223] = &&bad_opcode,
	#elif (CURRENT_OPCODE_RANGE > OPCODE_RANGE_6)
	[224] = &&bad_opcode,[225] = &&bad_opcode,[226] = &&bad_opcode,[227] = &&bad_opcode,[228] = &&bad_opcode,[229] = &&bad_opcode,[230] = &&bad_opcode,[231] = &&bad_opcode,[232] = &&bad_opcode,[233] = &&bad_opcode,[234] = &&bad_opcode,[235] = &&bad_opcode,[236] = &&bad_opcode,[237] = &&bad_opcode,[238] = &&bad_opcode,[239] = &&bad_opcode,

	[240] = &&bad_opcode,[241] = &&bad_opcode,[242] = &&bad_opcode,[243] = &&bad_opcode,[244] = &&bad_opcode,[245] = &&bad_opcode,[246] = &&bad_opcode,[247] = &&bad_opcode,[248] = &&bad_opcode,[249] = &&bad_opcode,[250] = &&bad_opcode,[251] = &&bad_opcode,[252] = &&bad_opcode,[253] = &&bad_opcode,[254] = &&bad_opcode,[255] = &&bad_opcode,
	#endif
	};

	/*
	=========================================================================
					Macros & Reused Variables
	=========================================================================
	*/

	/* Instruction fields */
	[[maybe_unused]] uint8_t op;
	[[maybe_unused]] uint8_t rd;
	[[maybe_unused]] uint8_t rs1;
	[[maybe_unused]] uint8_t rs2;

	/*
	* _pc is the local instruction cursor.
	*
	* Every LVM instruction is exactly 4 bytes:
	*
	*     +------+------+------+------+
	*     | OP   | RD   | RS1  | RS2  |
	*     +------+------+------+------+
	*       1 B    1 B    1 B    1 B
	*
	* REG_PC contains the VM-visible program counter.
	* _pc is used locally to keep the interpreter's hot path fast.
	*/
	uint8_t* _pc =
		(uint8_t*)(uintptr_t)vm->reg[REG_PC].u64;

	uint8_t* const program_end =
		vm->program + ((size_t)vm->ic * sizeof(instruction));

	#define THROW(code) vm->reg[REG_RC].u64 = (uint64_t)code; \
		goto op_halt;

	/* Fetch one byte and advance the instruction cursor. */
	#define FETCH() (*_pc++)

	/* Decode one complete 4-byte instruction. */
	#define DECODE() do {                  \
		if (_pc+INSTRUCTION_BYTES >= program_end) { THROW(RC_E_PC_OUT_OF_BOUNDS); } \
		op  = FETCH();                    \
		rd  = FETCH();                    \
		rs1 = FETCH();                    \
		rs2 = FETCH();                    \
	} while (0)

	/*
	* Dispatch the instruction currently pointed to by _pc.
	*/
	#define DISPATCH() do {               \
		if (_pc >= program_end) { THROW(RC_E_PC_OUT_OF_BOUNDS); }   \
		goto *table[*_pc];               \
	} while (0)

	/* Absolute jump: Set the Program Counter directly to a specific memory address */
	#define JUMP(address) do { \
		_pc = (uint8_t*)(uintptr_t)(address); \
		if (_pc >= program_end) { THROW(RC_E_BAD_JUMP_TARGET); }  \
		if (_pc < vm->program || _pc >= program_end) { \
			THROW(RC_E_BAD_JUMP_TARGET); /* Replace with your actual error code */ \
		} \
	} while (0)

	/* Relative jump: Move the Program Counter forward or backward by a byte offset */
	#define RJUMP(offset) do { \
		intptr_t base = (intptr_t)(uintptr_t)_pc;\
	intptr_t delta = (intptr_t)(int32_t)offset; \
	intptr_t target = base + delta; \
 \
	intptr_t begin = (intptr_t)(uintptr_t)vm->program;\
	intptr_t end = (intptr_t)(uintptr_t)program_end;\
\
	if (target < begin || target >= end ||\
		((target - begin) % (int)INSTRUCTION_BYTES) != 0) {\
		THROW(RC_E_BAD_JUMP_TARGET);\
	}\
\
	_pc = (uint8_t *)(uintptr_t)target;\
	} while (0)


	// ======================================================================================




	/* Start execution. */
	DISPATCH();



	/*
	=========================================================================
					Opcode Handlers
	=========================================================================
	*/

	// no operation
	bad_opcode: {
		return RC_E_BAD_INSTRUCTION;
	}

	op_nop: {
	_pc += INSTRUCTION_BYTES;
	DISPATCH();
	}
	// halt execution
	op_halt: {
		return (int)vm->reg[REG_RC].i64;
	}
	// load from heap
	op_ld: {
		DECODE();
		if(vm->reg[rs1].u64 + 7U > vm->hs) {THROW(RC_E_SEGFAULT);}
		memcpy(&vm->reg[rd].u64,&vm->heap[(uint32_t)vm->reg[rs1].u64],8);
		DISPATCH();
	}
	// store to heap
	op_st: {
		DECODE();
		if(vm->reg[rs1].u64 + 7U > vm->hs) {THROW(RC_E_SEGFAULT);}
		memcpy(&vm->heap[(uint32_t)vm->reg[rs1].u64],&vm->reg[rd].u64,8);
		DISPATCH();
	}
	// load 16-bit immidiate
	op_ldi: {
		DECODE();
		vm->reg[rd].u64 = (uint64_t)(((uint16_t)rs1 << 8) | (uint16_t)rs2);
		DISPATCH();
	}
	// copy register value
	op_cpy: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64;
		DISPATCH();
	}
	// Load from Data
	op_ldd: {
		DECODE();
		if(vm->reg[rs1].u64 + 7U > vm->ds) {THROW(RC_E_SEGFAULT);}
		memcpy(&vm->reg[rd].u64,&vm->data[(uint32_t)vm->reg[rs1].u64],8);
		DISPATCH();
	}



	// Add
	op_add: {
		DECODE();
		int64_t a = vm->reg[rs1].i64;
		int64_t b = vm->reg[rs2].i64;
		int64_t result;

		if (UNLIKELY(__builtin_add_overflow(a, b, &result))) {
			THROW(RC_E_INTEGER_OVERFLOW); 
		}

		vm->reg[rd].i64 = result;
		DISPATCH();
	}
	// Subtract
	op_sub: {
		DECODE();
		int64_t a = vm->reg[rs1].i64;
		int64_t b = vm->reg[rs2].i64;
		int64_t result;

		if (UNLIKELY(__builtin_sub_overflow(a, b, &result))) {
			THROW(RC_E_INTEGER_OVERFLOW); 
		}

		vm->reg[rd].i64 = result;
		DISPATCH();
	}
	// Multiply
	op_mul: {
		DECODE();
		int64_t a = vm->reg[rs1].i64;
		int64_t b = vm->reg[rs2].i64;
		int64_t result;

		if (UNLIKELY(__builtin_mul_overflow(a, b, &result))) {
			THROW(RC_E_INTEGER_OVERFLOW); 
		}

		vm->reg[rd].i64 = result;
		DISPATCH();
	}
	// Division
	op_div: {
		DECODE();
		int64_t n = vm->reg[rs1].i64;
		int64_t d = vm->reg[rs2].i64;

		if (UNLIKELY(d == 0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		if (UNLIKELY(n == INT64_MIN && d == -1)) {
			THROW(RC_E_INTEGER_OVERFLOW);
		}

		vm->reg[rd].i64 = n / d;
		
		DISPATCH();
	}
	// Modulus
	op_mod: {
		DECODE();
		int64_t n = vm->reg[rs1].i64;
		int64_t d = vm->reg[rs2].i64;

		if (UNLIKELY(d == 0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		
		if (UNLIKELY(n == INT64_MIN && d == -1)) {
			THROW(RC_E_INTEGER_OVERFLOW);
		} else {
			vm->reg[rd].i64 = n % d;
		}
		
		DISPATCH();
	}


	// Unsigned Add
	op_uadd: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 + vm->reg[rs2].u64;
		DISPATCH();
	}
	// Unsigned Subtract
	op_usub: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 - vm->reg[rs2].u64;
		DISPATCH();
	}
	// Unsigned Multiply
	op_umul: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 * vm->reg[rs2].u64;
		DISPATCH();
	}
	// Unsigned Division
	op_udiv: {
		DECODE();
		uint64_t n = vm->reg[rs1].u64;
		uint64_t d = vm->reg[rs2].u64;

		if (UNLIKELY(d == 0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		
		vm->reg[rd].u64 = n / d;
		DISPATCH();
	}
	// Unsigned Modulus
	op_umod: {
		DECODE();
		uint64_t n = vm->reg[rs1].u64;
		uint64_t d = vm->reg[rs2].u64;

		if (UNLIKELY(d == 0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		
		vm->reg[rd].u64 = n % d;
		DISPATCH();
	}

	// Floating-point Add
	op_fadd: {
		DECODE();
		vm->reg[rd].f64 = vm->reg[rs1].f64 + vm->reg[rs2].f64;
		DISPATCH();
	}
	// Floating-point Subtract
	op_fsub: {
		DECODE();
		vm->reg[rd].f64 = vm->reg[rs1].f64 - vm->reg[rs2].f64;
		DISPATCH();
	}
	// Floating-point Multiply
	op_fmul: {
		DECODE();
		vm->reg[rd].f64 = vm->reg[rs1].f64 * vm->reg[rs2].f64;
		DISPATCH();
	}
	// Floating-point Division
	op_fdiv: {
		DECODE();
		double n = vm->reg[rs1].f64;
		double d = vm->reg[rs2].f64;

		if (UNLIKELY(d == 0.0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		
		vm->reg[rd].f64 = n / d;
		DISPATCH();
	}
	// Floating-point Modulus
	op_fmod: {
		DECODE();
		double n = vm->reg[rs1].f64;
		double d = vm->reg[rs2].f64;

		if (UNLIKELY(d == 0.0)) { 
			THROW(RC_E_DIV_BY_ZERO); 
		}
		
		vm->reg[rd].f64 = fmod(n, d);
		DISPATCH();
	}

	op_and: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 & vm->reg[rs2].u64;
		DISPATCH();
	}
	op_or: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 | vm->reg[rs2].u64;
		DISPATCH();
	}
	op_not: {
		DECODE();
		vm->reg[rd].u64 = ~vm->reg[rs1].u64;
		DISPATCH();
	}
	op_xor: {
		DECODE();
		vm->reg[rd].u64 = vm->reg[rs1].u64 ^ vm->reg[rs2].u64;
		DISPATCH();
	}


	op_shl: {
		DECODE();
		uint64_t shift_amt = vm->reg[rs2].u64;
		// 1. Guard against invalid shift amounts (0 to 63 are valid for 64-bit)
        if (UNLIKELY(shift_amt >= 64)) {
            THROW(RC_E_INVALID_SHIFT);
        }
		// 2. Perform Action
		vm->reg[rd].u64 = vm->reg[rs1].u64 << shift_amt;
		DISPATCH();
	}

	op_shr: {
		DECODE();
		uint64_t shift_amt = vm->reg[rs2].u64;
		// 1. Guard against invalid shift amounts (0 to 63 are valid for 64-bit)
        if (UNLIKELY(shift_amt >= 64)) {
            THROW(RC_E_INVALID_SHIFT);
        }
		// 2. Perform Action
		vm->reg[rd].u64 = vm->reg[rs1].u64 >> shift_amt;
		DISPATCH();
	}

	op_asl: {
        DECODE();
        int64_t shift_amt = vm->reg[rs2].i64;
        
        // 1. Guard against invalid shift amounts (0 to 63 are valid for 64-bit)
        if (UNLIKELY(shift_amt < 0 || shift_amt >= 64)) {
            THROW(RC_E_INVALID_SHIFT); 
        }
        
        int64_t base_val = vm->reg[rs1].i64;
        
        // 2. Perform the shift safely using unsigned casting to prevent host UB
        uint64_t unsigned_res = (uint64_t)base_val << shift_amt;
        int64_t final_res = (int64_t)unsigned_res;
        
        // 3. Mathematical Overflow Check: Ensure the sign didn't change unexpectedly
        // (Sign of result must match sign of original value, unless base was 0)
        if (UNLIKELY(base_val != 0 && ((base_val ^ final_res) < 0))) {
            THROW(RC_E_INTEGER_OVERFLOW);
        }
        
        vm->reg[rd].i64 = final_res;
        DISPATCH();
    }

    op_asr: {
        DECODE();
        int64_t shift_amt = vm->reg[rs2].i64;
        
        // 1. Guard against invalid shift amounts
        if (UNLIKELY(shift_amt < 0 || shift_amt >= 64)) {
            THROW(RC_E_INVALID_SHIFT);
        }
        
        int64_t base_val = vm->reg[rs1].i64;
        
        // 2. Safely perform sign-extended right shift independently of host compiler quirks
        if (base_val < 0) {
            // Guarantee 1s are shifted in from the left
            vm->reg[rd].i64 = (int64_t)(~(~(uint64_t)base_val >> shift_amt));
        } else {
            vm->reg[rd].i64 = (int64_t)((uint64_t)base_val >> shift_amt);
        }
        
        DISPATCH();

    }
	op_jmp: {
		DECODE();
		JUMP(vm->reg[rd].u64);
		DISPATCH();
	}
	op_rjmp: {
		DECODE();
		RJUMP(vm->reg[rd].u64);
		DISPATCH();
	}
	op_br_gt: {
		DECODE();
		if(vm->reg[rs1].u64 > vm->reg[rs2].u64) {JUMP(vm->reg[rd].u64);}
		DISPATCH();
	}
	op_br_lt: {
		DECODE();
		if(vm->reg[rs1].u64 < vm->reg[rs2].u64) {JUMP(vm->reg[rd].u64);}
		DISPATCH();
	}
	op_br_eq: {
		DECODE();
		if(vm->reg[rs1].u64 == vm->reg[rs2].u64) {JUMP(vm->reg[rd].u64);}
		DISPATCH();
	}
	op_br_ne: {
		DECODE();
		if(vm->reg[rs1].u64 != vm->reg[rs2].u64) {JUMP(vm->reg[rd].u64);}
		DISPATCH();
	}

	op_call: {
		DECODE();

		uintptr_t target = (uintptr_t)vm->reg[rd].u64;
		uintptr_t program_begin = (uintptr_t)vm->program;
		uintptr_t program_limit = (uintptr_t)program_end;

		/* Targets must point inside the program and be instruction-aligned. */
		if (target < program_begin ||
		    target >= program_limit ||
		    ((target - program_begin) % INSTRUCTION_BYTES) != 0) {
			THROW(RC_E_BAD_JUMP_TARGET);
		}

		/* The decoded _pc is the return address. */
		uint64_t return_address = (uint64_t)(uintptr_t)_pc;

		if (vm->reg[REG_SP].u64 > vm->ss ||
		    vm->ss - vm->reg[REG_SP].u64 < sizeof(return_address)) {
			THROW(RC_E_STACK_OVERFLOW);
		}

		memcpy(&vm->stack[vm->reg[REG_SP].u64],
		       &return_address,
		       sizeof(return_address));

		vm->reg[REG_SP].u64 += sizeof(return_address);
		_pc = (uint8_t *)target;

		DISPATCH();
	}

	op_ret: {
		DECODE();

		if (vm->reg[REG_SP].u64 - 8U < sizeof(uint64_t)) {
			THROW(RC_E_STACK_UNDERFLOW);
		}

		vm->reg[REG_SP].u64 -= sizeof(uint64_t);

		uint64_t return_address;
		memcpy(&return_address,
		       &vm->stack[vm->reg[REG_SP].u64],
		       sizeof(return_address));

		uintptr_t target = (uintptr_t)return_address;
		uintptr_t program_begin = (uintptr_t)vm->program;
		uintptr_t program_limit = (uintptr_t)program_end;

		if (target < program_begin ||
		    target >= program_limit ||
		    ((target - program_begin) % INSTRUCTION_BYTES) != 0) {
			THROW(RC_E_BAD_JUMP_TARGET);
		}

		_pc = (uint8_t *)target;
		DISPATCH();
	}

	op_push: {
		DECODE();

		if (vm->reg[REG_SP].u64 + 8U > vm->ss ||
		    vm->ss - vm->reg[REG_SP].u64 < sizeof(uint64_t)) {
			THROW(RC_E_STACK_OVERFLOW);
		}

		uint64_t value = vm->reg[rd].u64;

		memcpy(&vm->stack[vm->reg[REG_SP].u64],
		       &value,
		       sizeof(value));

		vm->reg[REG_SP].u64 += sizeof(value);
		DISPATCH();
	}

	op_pop: {
		DECODE();

		if (vm->reg[REG_SP].u64 - 8U < sizeof(uint64_t) ||
		    vm->reg[REG_SP].u64 > vm->ss) {
			THROW(RC_E_STACK_UNDERFLOW);
		}

		vm->reg[REG_SP].u64 -= sizeof(uint64_t);

		memcpy(&vm->reg[rd].u64,
		       &vm->stack[vm->reg[REG_SP].u64],
		       sizeof(uint64_t));

		DISPATCH();
	}

	op_cnv: {
		DECODE();
		switch(rd) {
			case 0: vm->reg[rs1].u64 =(uint64_t) vm->reg[rs2].i64; break;
			case 1: vm->reg[rs1].u64 = (uint64_t)vm->reg[rs2].f64; break;
			case 2: vm->reg[rs1].f64 = (double)vm->reg[rs2].u64; break;
			case 3: vm->reg[rs1].f64 = (double)vm->reg[rs2].i64; break;
			case 4: vm->reg[rs1].i64 = (int64_t)vm->reg[rs2].u64; break;
			case 5: vm->reg[rs1].i64 = (int64_t)vm->reg[rs2].f64; break;
			default: /* do nothing */ break;
		}
		DISPATCH();
	}


	// syscall
	[[gnu::cold]] op_sys: {
		DECODE();

		DISPATCH();
	}

	return (int)vm->reg[REG_RC].i64;
}

