#ifndef  SPASM_HPP
#define  SPASM_HPP

#include "types.hpp"
#include "dstack.hpp"

namespace Spasm 
{


	class Spasm
	{
		public:
			Spasm ();
			Spasm (PC_t, const byte *, size_t);
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
			data_t *cframe_ptr;
			data_t *frame_ptr;
			size_t frame_size;
			size_t cframe_size;
			Dstack data_stack;
			Rstack_t return_stack;
	
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


} // namespace Spasm
#endif   /* ----- #ifndef SPASM_HPP  ----- */


