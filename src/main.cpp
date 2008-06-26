#include <iostream>
#include <fstream>

#include "spasm.hpp"

int
main (int argc, const char *argv[])
{
	if (argc != 2)
		return 1;

	std::ifstream input (argv[1], std::ios_base::in | std::ios_base::binary);

	size_t len;

	input.read ((char *) &len, sizeof (len));

	Spasm::byte *bytecode = new Spasm::byte[len];

	input.read ((char *)bytecode, len);

	for (size_t i = 0; i < len; ++i)
		std::cout << std::hex << (int) bytecode[i] << ' ';
	std::cout << std::endl;

	Spasm::Spasm vm(len, bytecode);

	vm.run();

	return 0;
}
