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
	}

	Spasm::Spasm (PC_t _bc_size, const byte * _bytecode)
	{
		bc_size = _bc_size;
		bytecode = new byte[bc_size];
		std::copy (_bytecode, _bytecode + bc_size, bytecode);

		pc = 0;
	}

	Spasm::Spasm (const Spasm &m)
		: data_stack (m.data_stack), return_stack (m.return_stack)
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
		bc_size = m.bc_size;
		bytecode = new byte[bc_size];
		std::copy (m.bytecode, m.bytecode + bc_size, bytecode);
		pc = m.pc;
	}

	const Dstack_t & Spasm::get_dstack () const {
		return data_stack;
	}

	void Spasm::run ()
	{
		while (pc >= 0 && pc < bc_size && operations[pc] != NULL) {
			(this->*operations[pc])();
			++pc;
		}
	}

	void Spasm::push () {
		++pc;
		data_stack.push (*(data_t *)(bytecode + pc));
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
		data_stack.pop ();
	}

	void Spasm::gofalse () {
		++pc;
		if (!data_stack.top ())
			pc = *((PC_t *) (bytecode + pc)) - 1;
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
	}

	void Spasm::ret () {
		pc = return_stack.top ();
		return_stack.pop ();
	}

	void Spasm::load () {
	}

	void Spasm::store () {
	}

		

} // namespace Spasm
