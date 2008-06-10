#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>

#include "token.hpp"


namespace SpasmImpl
{
	// ! Namespace for all classes and functions dealing with assembler
	namespace ASM
	{
		//! Namespace for all lexical analisys classes
		namespace Lexer
		{
			/*!
			** Class for lexers for the assembler-like language for spasm
			*/
			class Lexer {
				public:
					Lexer (std::istream &);
					~Lexer ();
					bool tokenize (TokenStream &);

				private:
					Lexer (const Lexer &);
					Lexer & operator= (const Lexer &);

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
	}	// namespace ASM
}	// namespace SpasmImpl

#endif
