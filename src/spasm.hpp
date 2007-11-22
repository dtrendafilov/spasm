#ifndef  SPASM_HPP
#define  SPASM_HPP

#include <stack>
namespace Spasm 
{



	typedef unsigned char byte;
	typedef int PC_t;
	typedef int data_t;
	typedef std::stack<data_t> Dstack_t;
	typedef std::stack<PC_t> Rstack_t;

	class Spasm;
	typedef void (Spasm::*Operation) ();
	class Spasm
	{
		public:
			Spasm ();
			Spasm (PC_t, const byte *);
			Spasm (const Spasm &);
			~Spasm ();
			Spasm & operator= (const Spasm &);

			void run ();

			const Dstack_t & get_dstack () const;

		private:
			static Operation operations[];
			static PC_t op_size;
			Dstack_t data_stack;
			Rstack_t return_stack;
			PC_t pc;
			PC_t bc_size;
			byte *bytecode;
	
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


