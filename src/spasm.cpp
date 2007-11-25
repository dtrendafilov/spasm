#include <algorithm>

#include "spasm.hpp"

namespace Spasm
{

	PC_t Spasm::op_size = 19;

	Operation Spasm::operations[19] = {
		NULL,
		&Spasm::push,
		&Spasm::pop,
		&Spasm::dup,
		&Spasm::print,
		&Spasm::read,
		&Spasm::plus,
		&Spasm::minus,
		&Spasm::multiply,
		&Spasm::divide,
		&Spasm::modulus,
		&Spasm::gotrue,
		&Spasm::gofalse,
		&Spasm::go,
		&Spasm::call,
		&Spasm::ret,
		&Spasm::load,
		&Spasm::store
	} ;

	Spasm::Spasm ()
	{
		bc_size = 0;
		bytecode = NULL;
		pc = 0;
		frame_size = 0;
		frame_ptr = NULL;
		cframe_size = 1024;
		cframe_ptr = NULL;
	}

	Spasm::Spasm (PC_t _bc_size, const byte * _bytecode, size_t _frame_size)
		: pc (0), bc_size (_bc_size), frame_size (_frame_size), cframe_size (1024)
	{
		bytecode = new byte[bc_size];
		std::copy (_bytecode, _bytecode + bc_size, bytecode);
		frame_ptr = new data_t[frame_size];
		cframe_ptr = frame_ptr;
	}

	Spasm::Spasm (const Spasm &m)
		: pc(m.pc), bc_size (m.bc_size),
		frame_size (m.frame_size), cframe_size (m.cframe_size),
		data_stack (m.data_stack), return_stack (m.return_stack)
	{
		copybc (m);
	}

	Spasm::~Spasm ()
	{
		deleteobj ();
	}

	Spasm & Spasm::operator= (const Spasm &m)
	{
		if (this != &m) {
			deleteobj ();
			data_stack = m.data_stack;
			return_stack = m.return_stack;
			copybc (m);
		}
		return *this;
	}

	void Spasm::copybc (const Spasm &m)
	{
		bytecode = new byte[bc_size];
		std::copy (m.bytecode, m.bytecode + bc_size, bytecode);
		frame_ptr = new data_t[frame_size];
		cframe_ptr = m.cframe_ptr - m.frame_ptr + frame_ptr;
	}

	void Spasm::deleteobj () {
		if (bytecode)
			delete [] bytecode;
		if (frame_ptr)
			delete [] frame_ptr;
	}

	const Dstack_t & Spasm::get_dstack () const {
		return data_stack;
	}

	void Spasm::run ()
	{
		while (pc >= 0 && pc < bc_size) {
			if (bytecode[pc] > 0 && bytecode[pc] < op_size)
				(this->*operations[bytecode[pc]])();
			else
				return;
			++pc;
		}
	}

	void Spasm::push () {
		++pc;
		data_stack.push (*(data_t *)(bytecode + pc));
		pc += sizeof(data_t) - 1;
	}

	void Spasm::pop () {
		data_stack.pop ();
	}

	void Spasm::dup () {
		data_stack.push (data_stack.top ());
	}

	void Spasm::read () {
	}

	void Spasm::print () {
	}

	void Spasm::plus () {
		data_t x, y = data_stack.top ();
		data_stack.pop ();
		x = data_stack.top ();
		data_stack.pop ();
		data_stack.push (x + y);
	}

	void Spasm::minus () {
		data_t x, y = data_stack.top ();
		data_stack.pop ();
		x = data_stack.top ();
		data_stack.pop ();
		data_stack.push (x - y);
	}
	void Spasm::multiply () {
		data_t x, y = data_stack.top ();
		data_stack.pop ();
		x = data_stack.top ();
		data_stack.pop ();
		data_stack.push (x * y);
	}
	void Spasm::divide () {
		data_t x, y = data_stack.top ();
		data_stack.pop ();
		x = data_stack.top ();
		data_stack.pop ();
		data_stack.push (x / y);
	}
	void Spasm::modulus () {
		data_t x, y = data_stack.top ();
		data_stack.pop ();
		x = data_stack.top ();
		data_stack.pop ();
		data_stack.push (x % y);
	}

	void Spasm::gotrue () {
		++pc;
		if (data_stack.top ())
			pc = *((PC_t *) (bytecode + pc)) - 1;
		else
			pc += sizeof(PC_t) - 1;
		data_stack.pop ();
	}

	void Spasm::gofalse () {
		++pc;
		if (!data_stack.top ())
			pc = *((PC_t *) (bytecode + pc)) - 1;
		else
			pc += sizeof(PC_t) - 1;
		data_stack.pop ();
	}

	void Spasm::go () {
		++pc;
		pc = *((PC_t *) (bytecode + pc)) - 1;
	}

	void Spasm::call () {
		++pc;
		return_stack.push (pc); // using the ++pc in run()
		pc = *((PC_t *) (bytecode + pc)) - 1;
		cframe_ptr += cframe_size;
	}

	void Spasm::ret () {
		pc = return_stack.top ();
		return_stack.pop ();
		cframe_ptr -= cframe_size;
	}

	void Spasm::load () {
	}

	void Spasm::store () {
	}

		

} // namespace Spasm
