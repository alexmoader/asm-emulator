#include "assembler.hpp"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) 
{
    try 
    {
        if (argc != 3) 
        {
            std::cerr << "Usage: " << argv[0] << " <input.s> <output.o>\n";
            return 1;
        }
        assemble(argv[1], argv[2]);
        std::cout << "Assembly successful.\n";
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
