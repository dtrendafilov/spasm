#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>

#include "token.hpp"


namespace SpasmImpl
{
	//! Namespace for all lexical analisys classes
	namespace Lexer
	{
		/*!
		** Class for lexers for the assembler-like language for spasm
		*/
		class ASMLexer {
			public:
				ASMLexer (std::istream &);
				~ASMLexer ();
				bool tokenize (TokenStream &);

			private:
				ASMLexer (const ASMLexer &);
				ASMLexer & operator= (const ASMLexer &);

				void buffer_grow (size_t);
				void buffer_init ();

				//! fills the buffer called when the lexer needs more data
				void read (size_t);

				//! input stream for the lexer
				std::istream *file;

				//! buffer for the lexer
				char *buffer;
				
				//! size of the buffer
				size_t buffer_size;

				//! cursor for re2c generated lexer
				char *cursor;

				//! limit for re2c generated lexer
				char *limit;

				//! marker for re2c generated lexer
				char *marker;

				//! pointer to the start of the just recognized token
				char *token_start;


		} ;
	}	// namespace Lexer
}	// namespace SpasmImpl

#endif
