#include "emulator.hpp"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) 
{
    try 
    {
        if (argc != 2) 
        {
            std::cerr << "Usage: " << argv[0] << " <binary.o>\n";
            return 1;
        }
        emulate(argv[1]);
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
