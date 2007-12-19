#ifndef  FRAMES_HPP
#define  FRAMES_HPP

#include <stack>

#include "types.hpp"

namespace SpasmImpl
{

	class FrameStack
	{
		public:
			FrameStack ();
			FrameStack (const FrameStack &);
			~FrameStack ();
			FrameStack & operator= (const FrameStack &);

			const data_t & operator[] (int) const;
			data_t & operator[] (int);
			void pop_frame ();
			void new_frame (size_t); 
			bool empty () const;

		private:
			data_t * base_ptr;
			data_t * frame_ptr;
			size_t g_size;
			size_t c_size;
			std::stack<size_t> fstack;
	} ;

}

#endif   // #ifndef FRAMES_HPP

