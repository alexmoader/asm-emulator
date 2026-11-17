#include "emulator.hpp"
#include "common.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>  // output formatting manipulators (std::hex, std::dec, std::showbase)
#include <stdexcept>

// Reading binary file in vector of bytes
static std::vector<uint8_t> readBinaryFile(const std::string& filename) 
{
    //variable "file" is binary and opened with the pointer in the end of the file to find out its size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error("Cannot open binary file: " + filename);

    std::streamsize size = file.tellg(); // tellq() - returns the pointer = size of the file

    file.seekg(0, std::ios::beg); //pointer = beginning

    if (size % INSTR_SIZE != 0)
        throw std::runtime_error("Binary file size is not a multiple of instruction size");

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read binary file");
    return buffer;
}

// Executing single instruction
static void executeInstruction(const uint8_t* instr, uint32_t* reg) 
{
    uint8_t opcode = instr[0];
    uint8_t a = instr[1];
    uint8_t b = instr[2];
    uint8_t c = instr[3];

    switch (opcode) 
    {
        case OP_LI: 
        {
            if (a >= REG_COUNT)
                throw std::runtime_error("Invalid register index in LI");
            uint16_t imm = static_cast<uint16_t>(b) | (static_cast<uint16_t>(c) << 8);
            reg[a] = imm;
            break;
        }
        case OP_ADD: 
        {
            if (a >= REG_COUNT || b >= REG_COUNT || c >= REG_COUNT)
                throw std::runtime_error("Invalid register index in ADD");
            reg[a] = reg[b] + reg[c];
            break;
        }
        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}

// func prints status of registers
static void printRegisters(const uint32_t* reg) 
{
    for (int i = 0; i < REG_COUNT; ++i) 
    {
        std::cout << "R" << std::dec << i << "=0x" << std::hex << reg[i];
        if (i != REG_COUNT - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

// main emulating func
void emulate(const std::string& binaryFile) 
{
    std::vector<uint8_t> program = readBinaryFile(binaryFile);

    uint32_t reg[REG_COUNT] = {0}; // As required by the task: each register is initialized as zero

    for (size_t pc = 0; pc < program.size(); pc += INSTR_SIZE) 
    {
        executeInstruction(&program[pc], reg);
    }

    printRegisters(reg);
}
