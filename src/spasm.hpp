#ifndef  SPASM_HPP
#define  SPASM_HPP

#include <iostream>

#include "types.hpp"
#include "dstack.hpp"
#include "frames.hpp"

namespace SpasmImpl 
{


	class Spasm
	{
		public:
			Spasm ();
			Spasm (PC_t, const byte *, std::istream & = std::cin,
					std::ostream & = std::cout);
			Spasm (const Spasm &);
			~Spasm ();
			Spasm & operator= (const Spasm &);

			void run ();

			const Dstack & get_dstack () const;

		private:
			static Operation operations[];
			static PC_t op_size;
			PC_t pc;
			PC_t bc_size;
			byte *bytecode;
			Dstack data_stack;
			Rstack_t return_stack;
			FrameStack frame;
			std::istream * istr;
			std::ostream * ostr;
	
			void push ();
			void pop ();
			void dup ();

			void print ();
			void read ();

			void plus ();
			void minus ();
			void multiply ();
			void divide ();
			void modulus ();

			void gotrue ();
			void gofalse ();
			void go ();

			void call ();
			void ret ();

			void load ();
			void store ();

			// private method for copying and deleting an object
			void copybc (const Spasm &);
			void deleteobj ();
	} ;


} // namespace SpasmImpl
#endif   // #ifndef SPASM_HPP


