#include <algorithm>

#include "types.hpp"

#include "frames.hpp"

namespace SpasmImpl
{
	FrameStack::FrameStack ()
		: base_ptr (NULL), frame_ptr (NULL), g_size (0), c_size (0)
	{
	}

	FrameStack::FrameStack (const FrameStack &fs)
		: base_ptr (fs.base_ptr), frame_ptr (fs.frame_ptr),
		g_size (fs.g_size), c_size (fs.c_size), fstack (fs.fstack)
	{
	}

	FrameStack::~FrameStack ()
	{
		if (base_ptr)
			delete [] base_ptr;
	}

	FrameStack & FrameStack::operator= (const FrameStack &fs)
	{
		if (this != &fs) {
			if (base_ptr)
				delete [] base_ptr;
			base_ptr = new data_t[fs.g_size];
			std::copy (fs.base_ptr, fs.frame_ptr + fs.c_size, base_ptr);
			frame_ptr = base_ptr + (fs.frame_ptr - fs.base_ptr);
			g_size = fs.g_size;
			c_size = fs.c_size;
			fstack = fs.fstack;
		}
		return *this;
	}

	const data_t & FrameStack::operator[] (int index) const
	{
		return frame_ptr[index];
	}

	data_t & FrameStack::operator[] (int index)
	{
		return frame_ptr[index];
	}

	void FrameStack::pop_frame ()
	{

		if (fstack.empty()) {
			frame_ptr = base_ptr;
			c_size = 0;
		}
		else {
			data_t * new_frame_ptr = base_ptr + fstack.top ();
			fstack.pop ();
			c_size = frame_ptr - new_frame_ptr;
			frame_ptr = new_frame_ptr;
		}
	}

	void FrameStack::new_frame (size_t fsize)
	{
		data_t *new_frame;

		if (frame_ptr + c_size + fsize > base_ptr + g_size) {
			size_t new_size = g_size + std::max (g_size, c_size + fsize);
			data_t *new_base = new data_t[new_size];
			if (base_ptr) {
					std::copy (base_ptr, frame_ptr + c_size, new_base);
					delete [] base_ptr;
			}
			frame_ptr = new_base + (frame_ptr - base_ptr);
			base_ptr = new_base;
		}
		new_frame = frame_ptr + c_size;
		fstack.push (frame_ptr - base_ptr);
		c_size = fsize;
	}
	
	bool FrameStack::empty () const
	{
		return frame_ptr == base_ptr && c_size == 0;
	}
}
