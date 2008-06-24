#include <iostream>
#include <fstream>
#include <string>

#include "bytecode.hpp"

namespace SpasmImpl
{
	namespace ASM
	{
		Bytecode_File::Bytecode_File (const std::string &filename)
			: _bytecode (filename.c_str(),
					std::ios_base::out | std::ios_base::binary)
		{
		}

		void Bytecode_File::push_byte (unsigned char byte)
		{
			_bytecode.put (byte);
		}

		void Bytecode_File::push_opcode (Bytecode_Stream::Opcode_t opcode)
		{
			push_byte (opcode);
		}

		void Bytecode_File::push_integer (int number)
		{
			for (int i = sizeof (int) - 1; i >= 0; --i)
				push_byte ((number >> (i << 3)) & 0xff);
		}


	}	// namespace ASM
}	// namespace SpasmImpl
