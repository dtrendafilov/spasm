#ifndef  TYPES_HPP
#define  TYPES_HPP

#include <stack>

namespace SpasmImpl
{
	typedef unsigned char byte;
	typedef int PC_t;
	typedef int data_t;
	typedef std::stack<PC_t> Rstack_t;

	class Spasm;
	typedef void (Spasm::*Operation) ();
}
#endif   // ----- #ifndef TYPES_HPP

