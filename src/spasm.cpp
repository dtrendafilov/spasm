#include <algorithm>
#include <iostream>

#include "spasm.hpp"

namespace SpasmImpl
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
		: pc (0), bc_size (0), bytecode (NULL),
		istr (&std::cin), ostr (&std::cout)
	{
	}

	Spasm::Spasm (PC_t _bc_size, const byte * _bytecode,
			std::istream & _istr, std::ostream & _ostr)
		: pc (0), bc_size (_bc_size), istr (&_istr), ostr (&_ostr)
	{
		bytecode = new byte[bc_size];
		std::copy (_bytecode, _bytecode + bc_size, bytecode);
	}

	Spasm::Spasm (const Spasm &m)
		: pc(m.pc), bc_size (m.bc_size),
		data_stack (m.data_stack), return_stack (m.return_stack),
		frame (m.frame), istr (m.istr), ostr (m.ostr)
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
			frame = m.frame;
			istr = m.istr;
			ostr = m.ostr;
			copybc (m);
		}
		return *this;
	}

	void Spasm::copybc (const Spasm &m)
	{
		bytecode = new byte[bc_size];
		std::copy (m.bytecode, m.bytecode + bc_size, bytecode);
	}

	void Spasm::deleteobj () {
		if (bytecode)
			delete [] bytecode;
	}

	const Dstack & Spasm::get_dstack () const {
		return data_stack;
	}

	void Spasm::run ()
	{
		while (pc >= 0 && pc < bc_size) {
			if (bytecode[pc] > 0 && bytecode[pc] < op_size)
				(this->*operations[bytecode[pc]])();
			else
				break;
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
		data_t x;
		*istr >> x;
		data_stack.push (x);
	}

	void Spasm::print () {
		*ostr << data_stack.pop ();
	}

	void Spasm::plus () {
		data_t x, y = data_stack.pop ();
		x = data_stack.pop ();
		data_stack.push (x + y);
	}

	void Spasm::minus () {
		data_t x, y = data_stack.pop ();
		x = data_stack.pop ();
		data_stack.push (x - y);
	}
	void Spasm::multiply () {
		data_t x, y = data_stack.pop ();
		x = data_stack.pop ();
		data_stack.push (x * y);
	}
	void Spasm::divide () {
		data_t x, y = data_stack.pop ();
		x = data_stack.pop ();
		data_stack.push (x / y);
	}
	void Spasm::modulus () {
		data_t x, y = data_stack.pop ();
		x = data_stack.pop ();
		data_stack.push (x % y);
	}

	void Spasm::gotrue () {
		++pc;
		if (data_stack.pop ())
			pc = *((PC_t *) (bytecode + pc)) - 1;
		else
			pc += sizeof(PC_t) - 1;
	}

	void Spasm::gofalse () {
		++pc;
		if (!data_stack.pop ())
			pc = *((PC_t *) (bytecode + pc)) - 1;
		else
			pc += sizeof(PC_t) - 1;
	}

	void Spasm::go () {
		++pc;
		pc = *((PC_t *) (bytecode + pc)) - 1;
	}

	void Spasm::call () {
		size_t fs; // new frame size
		return_stack.push (pc); // using the ++pc in run()
		data_stack.pop (&fs, sizeof (fs));
		data_stack.pop (&pc, sizeof (pc));
		frame.new_frame (fs);
		--pc; // the ++pc in run()
	}

	void Spasm::ret () {
		pc = return_stack.top ();
		return_stack.pop ();
		frame.pop_frame ();
	}

	void Spasm::load () {
		size_t offset;

		data_stack.pop (&offset, sizeof (offset));
		data_stack.push (frame[offset]);
	}

	void Spasm::store () {
		data_t value = data_stack.pop ();
		size_t offset;

		data_stack.pop (&offset, sizeof (offset));
		frame[offset] = value;
	}

		

} // namespace SpasmImpl
