#include "dstack.hpp"

#include <algorithm>

namespace SpasmImpl
{
	Dstack::Dstack ()
		: bottom(NULL), tos(NULL), s_size(0)
	{
	}

	Dstack::Dstack (const Dstack &ds)
		: s_size (ds.s_size)
	{
		copy_dstack (ds);
	}

	Dstack & Dstack::operator= (const Dstack &ds)
	{
		if (this != &ds) {
			if (bottom)
				delete [] bottom;
			s_size = ds.s_size;
			copy_dstack (ds);
		}
		return *this;
	}

	Dstack::~Dstack ()
	{
		if (bottom)
			delete [] bottom;
	}

	void Dstack::reserve (size_t new_size)
	{
		size_t offset = tos - bottom;
		byte *new_bottom = new byte[new_size];
		if (bottom) {
			std::copy (bottom, bottom + std::min (s_size, new_size),
					new_bottom);
			delete [] bottom;
		}
		bottom = new_bottom;
		tos = new_bottom + offset;
		s_size = new_size;
	}

	void Dstack::push (data_t x)
	{
		if (bottom + s_size < tos + sizeof (data_t))
			reserve ((s_size? s_size : sizeof (data_t)) * 2);
		*((data_t *) tos) = x;
		tos += sizeof (data_t);
	}

	void Dstack::push (byte * x, size_t x_size)
	{
		if (bottom + s_size < tos + x_size)
			reserve (s_size + (s_size > x_size)? s_size : x_size);
		std::copy (x, x + x_size, tos);
		tos += x_size;
	}

	void Dstack::pop (void * x, size_t x_size)
	{
		if (tos - x_size >= bottom) {
			std::copy (tos - x_size, tos, (byte *)x);
			tos -= x_size;
		}
	}

	data_t Dstack::pop ()
	{
		data_t x;
		if (tos - sizeof (data_t) >= bottom) {
			tos -= sizeof (data_t);
			x = * ((data_t *) tos);
		}
		return x;
	}

	data_t Dstack::top () const
	{
		data_t x;
		if (tos - sizeof (data_t) >= bottom) {
			x = * ((data_t *) (tos - sizeof (data_t)));
		}
		return x;
	}

	size_t Dstack::size () const
	{
		return tos - bottom;
	}

	size_t Dstack::reserved () const
	{
		return s_size;
	}

	void Dstack::strip_memory ()
	{
		reserve (size ());
	}

	bool Dstack::empty () const
	{
		return tos - bottom == 0;
	}

	void Dstack::copy_dstack (const Dstack &ds)
	{
		if (ds.bottom) {
			bottom = new byte[ds.s_size];
			tos = bottom + (ds.tos - ds.bottom);
			std::copy (ds.bottom, ds.tos, bottom);
		}
		else
			bottom = tos = NULL;
	}


}
