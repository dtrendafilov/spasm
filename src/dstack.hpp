#ifndef  DSTACK_HPP
#define  DSTACK_HPP

#include "types.hpp"

namespace Spasm
{
	class Dstack {

		public:
			Dstack ();
			Dstack (const Dstack &);
			Dstack & operator= (const Dstack &);
			~Dstack ();
			void push (data_t);
			void push (byte *, size_t);
			void pop (byte *, size_t);
			data_t pop ();
			data_t top () const;
			void reserve (size_t);
			size_t size () const;
			size_t reserved () const;
			bool empty () const;

		private:
			void copy_dstack (const Dstack &);
			byte *bottom;
			byte *tos;
			size_t s_size;
	} ;
}


#endif   // #ifndef DSTACK_HPP

