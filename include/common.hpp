#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdint> // contains uint8_t... and other int types with fixed size

const int REG_COUNT = 16; // amount of regs: R0..R15
const int INSTR_SIZE = 4; // size of instructions (in bytes)

// Codes of operations in binary
enum Opcode : uint8_t 
{
    OP_LI  = 0x00,
    OP_ADD = 0x02
};

#endif // COMMON_HPP
