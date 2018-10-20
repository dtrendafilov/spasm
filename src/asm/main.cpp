#include <fstream>
#include <iostream>
#include "assembler.hpp"

int main(int argc, const char* argv[])
{
    if (argc != 2)
        return 1;

    const char* bc = SpasmImpl::ASM::compile(std::cin);

    std::ofstream output(argv[1], std::ios_base::out | std::ios_base::binary);

    // output.write ("SPASM", 5);
    output.write(bc, *(size_t*)bc + sizeof(size_t));

    return 0;
}
