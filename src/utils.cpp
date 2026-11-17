#include "utils.hpp"
#include "common.hpp"
#include <algorithm>
#include <stdexcept>
#include <cctype>

std::string cleanLine(const std::string& line) 
{
    std::string result = line;
    // removing comment (starting usually with ';' in asm)
    size_t commentPos = result.find_first_of(";");
    if (commentPos != std::string::npos) result = result.substr(0, commentPos);
    // removing spaces at the begining and end
    result.erase(0, result.find_first_not_of(" \t\r\n"));
    // and end
    result.erase(result.find_last_not_of(" \t\r\n") + 1);
    return result;
}

bool isEmptyLine(const std::string& line) 
{
    return line.empty() || std::all_of(line.begin(), line.end(), ::isspace);
}

int parseRegister(const std::string& token) 
{
    if (token.size() < 2 || token[0] != 'R')
        throw std::runtime_error("Invalid register name: " + token);
    int num = std::stoi(token.substr(1));
    if (num < 0 || num >= REG_COUNT)
        throw std::runtime_error("Register number out of range: " + token);
    return num;
}

uint32_t parseImmediate(const std::string& token) 
{
    // base = 0 auto detect hex (0x) / dec
    return static_cast<uint32_t>(std::stoul(token, nullptr, 0));
}
