#include "lumini_isa.h"


inline instruction_t encode_instruction(decoded_instruction_t i) {
    return (instruction_t)((i.op << 24) | (i.rd << 16) | (i.ra << 8) | i.rb);
}

inline decoded_instruction_t decode_instruction(instruction_t i) {
    return (decoded_instruction_t){.op = (i >> 24) & 0xFF, .rd = (i >> 16) & 0xFF, .ra = (i >> 8) & 0xFF, .rb = i & 0xFF};
}