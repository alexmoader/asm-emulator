#include "assembler.hpp"
#include "common.hpp"
#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

// auxiliary functions

// Processing LI instruction
static void processLI(std::istringstream& iss, int lineNumber, std::ofstream& out) 
{
    std::string reg, imm;
    iss >> reg >> imm;
    if (!iss)
        throw std::runtime_error("Syntax error in LI at line " + std::to_string(lineNumber));
    
    int r = parseRegister(reg);
    uint32_t val = parseImmediate(imm);

    if (val > 0xFFFF) // we check that the value fits in 16 bits
        throw std::runtime_error("Immediate value out of 16-bit range at line " + std::to_string(lineNumber));

    uint8_t bytes[4] = 
    {
        OP_LI,
        static_cast<uint8_t>(r),
        static_cast<uint8_t>(val & 0xFF),        // I0 - low byte
        static_cast<uint8_t>((val >> 8) & 0xFF)  // I1 - high byte
    };
    out.write(reinterpret_cast<const char*>(bytes), INSTR_SIZE);
}

// Processing the ADD instruction
static void processADD(std::istringstream& iss, int lineNumber, std::ofstream& out) 
{
    std::string ra, rb, rc;
    iss >> ra >> rb >> rc;
    if (!iss)
        throw std::runtime_error("Syntax error in ADD at line " + std::to_string(lineNumber));
    
    int a = parseRegister(ra);
    int b = parseRegister(rb);
    int c = parseRegister(rc);
    uint8_t bytes[4] = 
    {
        OP_ADD,
        static_cast<uint8_t>(a),
        static_cast<uint8_t>(b),
        static_cast<uint8_t>(c)
    };
    out.write(reinterpret_cast<const char*>(bytes), INSTR_SIZE);
}

// Processing a single line of assembler
static void processLine(const std::string& line, int lineNumber, std::ofstream& out) 
{
    std::string cleaned = cleanLine(line);
    if (isEmptyLine(cleaned))
        return;

    std::istringstream iss(cleaned);
    std::string opcode;
    iss >> opcode;

    if (opcode == "LI") 
    {
        processLI(iss, lineNumber, out);
    }
    else if (opcode == "ADD") 
    {
        processADD(iss, lineNumber, out);
    } 
    else 
    {
        throw std::runtime_error("Unknown opcode '" + opcode + "' at line " + std::to_string(lineNumber));
    }
}

// main function of assembler
void assemble(const std::string& inputFile, const std::string& outputFile) 
{
    std::ifstream in(inputFile);
    if (!in.is_open())
        throw std::runtime_error("Cannot open input file: " + inputFile);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Cannot open output file: " + outputFile);

    std::string line;
    int lineNumber = 0;
    // we go through each line and execute the commands
    while (std::getline(in, line)) 
    {
        ++lineNumber;
        try 
        {
            processLine(line, lineNumber, out);
        } 
        catch (const std::exception& e) 
        {
            throw std::runtime_error("Line " + std::to_string(lineNumber) + ": " + e.what());
        }
    }
}
