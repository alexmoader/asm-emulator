#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <cstdint>

//func removes comments and extra spaces from a line
std::string cleanLine(const std::string& line);

// func checks whether the string is empty or consists only of spaces
bool isEmptyLine(const std::string& line);

// func parses the register number from a string like "R0"..."R15"
int parseRegister(const std::string& token);

// Integer parsing func with decimal and hexadecimal support (0x...) format
uint32_t parseImmediate(const std::string& token);

#endif // UTILS_HPP
