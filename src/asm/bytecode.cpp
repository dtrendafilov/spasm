#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <new>

#include "bytecode.hpp"

namespace SpasmImpl
{
	namespace ASM
	{
		Bytecode_Stream::~Bytecode_Stream()
		{
		}

		Bytecode_File::Bytecode_File (const std::string &filename)
			: _bytecode (filename.c_str(),
					std::ios_base::out | std::ios_base::binary)
		{
		}

		void Bytecode_File::push_byte (Bytecode_Stream::byte byte)
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


		void Bytecode_Memory::push_byte (Bytecode_Stream::byte byte)
		{
			_bytecode.push_back (byte);
		}

		void Bytecode_Memory::push_opcode (Bytecode_Stream::Opcode_t opcode)
		{
			push_byte (opcode);
		}

		void Bytecode_Memory::push_integer (int number)
		{
			for (int i = sizeof (int) - 1; i >= 0; --i)
				push_byte ((number >> (i << 3)) & 0xff);
		}


		void Bytecode_Memory::set_location (size_t index, size_t location)
		{
			int l = sizeof (size_t) - 1;
			for (int i = l; i >= 0; --i)
				_bytecode.at (index + l - i) = ((location >> (i << 3)) & 0xff);
		}

		void Bytecode_Memory::push_location (size_t location)
		{
			for (int i = sizeof (size_t) - 1; i >= 0; --i)
				_bytecode.push_back ((location >> (i << 3)) & 0xff);
		}

		const char *Bytecode_Memory::bytecode() const
		{
			size_t bc_size = _bytecode.size();
			size_t length = sizeof(size_t) + bc_size;
			char *bytecode = new char[length];

			*((size_t *) bytecode) = bc_size;

			std::copy (_bytecode.begin(), _bytecode.end(),
					bytecode + sizeof (size_t));

			return bytecode;
		}

		size_t Bytecode_Memory::size() const
		{
			return _bytecode.size();
		}

	}	// namespace ASM
}	// namespace SpasmImpl
