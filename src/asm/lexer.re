#include <iostream>

#include "lexer.hpp"

#include "token.hpp"

namespace SpasmImpl
{
	//! Namespace for all lexical analisys classes
	namespace Lexer
	{

		ASMLexer::ASMLexer (std::istream & _file)
			: file (&_file), buffer_size (4096)
		{
			buffer = new char[buffer_size];
			cursor = limit = marker = token_start = NULL;
		}

		ASMLexer::~ASMLexer ()
		{
			delete [] buffer;
		}

		bool ASMLexer::tokenize (TokenStream &ts)
		{
			size_t lineno = 0;

			buffer_init ();

			while (1)
/*!re2c
re2c:indent:top = 3;

re2c:define:YYFILL=read;
re2c:define:YYCTYPE="char";
re2c:define:YYCURSOR=cursor;
re2c:define:YYLIMIT=limit;
re2c:define:YYMARKER=marker;

DIGIT	= [0-9] ;
XDIGIT	= [0-9a-fA-F] ;

INTEGER		= "-"? "0" | ([1-9] DIGIT*) ;
XINTEGER	= "0" [xX] XDIGIT+ ;
IDENTIFIER	= [a-zA-Z_] [0-9a-zA-Z_]+ ;

INTEGER		{
				ts.push_token (ASMToken (ASMToken::integer, lineno, token_start, cursor));
				token_start = cursor;

				continue;
			}

XINTEGER	{
				ts.push_token (ASMToken (ASMToken::xinteger, lineno, token_start, cursor));
				token_start = cursor;

				continue;
			}

"push"		{
				ts.push_token (ASMToken (ASMToken::push, lineno));

				token_start = cursor;

				continue;
			}

"pop"		{
				ts.push_token (ASMToken (ASMToken::pop, lineno));
				token_start = cursor;
				continue;
			}

"dup"		{
				ts.push_token (ASMToken (ASMToken::dup, lineno));
				token_start = cursor;
				continue;
			}

"read"		{
				ts.push_token (ASMToken (ASMToken::read, lineno));
				token_start = cursor;
				continue;
			}

"print"		{
				ts.push_token (ASMToken (ASMToken::print, lineno));
				token_start = cursor;
				continue;
			}

"+"			{
				ts.push_token (ASMToken (ASMToken::plus, lineno));
				token_start = cursor;
				continue;
			}

"-"			{
				ts.push_token (ASMToken (ASMToken::minus, lineno));
				token_start = cursor;
				continue;
			}

"*"			{
				ts.push_token (ASMToken (ASMToken::multiply, lineno));
				token_start = cursor;
				continue;
			}

"/"			{
				ts.push_token (ASMToken (ASMToken::divide, lineno));
				token_start = cursor;
				continue;
			}

"%"			{
				ts.push_token (ASMToken (ASMToken::modulus, lineno));
				token_start = cursor;
				continue;
			}

"gotrue"	{
				ts.push_token (ASMToken (ASMToken::gotrue, lineno));
				token_start = cursor;
				continue;
			}

"gofalse"	{
				ts.push_token (ASMToken (ASMToken::gofalse, lineno));
				token_start = cursor;
				continue;
			}

"go"		{
				ts.push_token (ASMToken (ASMToken::go, lineno));
				token_start = cursor;
				continue;
			}

"call"		{
				ts.push_token (ASMToken (ASMToken::call, lineno));
				token_start = cursor;
				continue;
			}

"ret"		{
				ts.push_token (ASMToken (ASMToken::ret, lineno));
				token_start = cursor;
				continue;
			}

"load"		{
				ts.push_token (ASMToken (ASMToken::load, lineno));
				token_start = cursor;
				continue;
			}

"store"		{
				ts.push_token (ASMToken (ASMToken::store, lineno));
				token_start = cursor;
				continue;
			}

"label"		{
				ts.push_token (ASMToken (ASMToken::label, lineno));
				token_start = cursor;
				continue;
			}

IDENTIFIER	{
				ts.push_token (ASMToken (ASMToken::ident, lineno, token_start, cursor));
				token_start = cursor;
				continue;
			}

[ 	]+		{
				token_start = cursor;
				continue;
			}

"\n"		{
				++lineno;
				token_start = cursor;

				continue;
			}

"\000"		{
				break;
			}

[^]			{
				return false;
			}

*/
			return true;
		}

		/*!
		** Fills up the buffer when neccessary.
		** Note the buffer is always filled to the maximum, not just the
		** number of bytes neccessary for the lexer to continue.
		**
		** \param nbytes	- the number of bytes
		*/

		void ASMLexer::buffer_grow (size_t new_size)
		{
			char *new_buffer = new char[new_size];

			std::copy (buffer, limit, new_buffer);

			token_start = new_buffer + (token_start - buffer);
			cursor = new_buffer + (cursor - buffer);
			limit = new_buffer + new_size;

			buffer_size = new_size;

			delete [] buffer;
			buffer = new_buffer;
		}

		void ASMLexer::read (size_t nbytes)
		{
			if (token_start + nbytes > limit) { // we need larger buffer
				buffer_grow (token_start - buffer + nbytes);
			}

			std::copy (token_start, limit, buffer);
			cursor -= token_start - buffer;
			char *old_limit = limit - (token_start - buffer);
			token_start = buffer;

			file->read (old_limit, limit - old_limit);
			if (file->eof ()) {
				size_t bytes = file->gcount ();
				std::fill (old_limit + bytes, limit, 0);
			}
		}

		void ASMLexer::buffer_init ()
		{
			file->read (buffer, buffer_size);
			if (file->eof ()) {
				size_t bytes = file->gcount ();
				std::fill (buffer + bytes, buffer + buffer_size, 0);
			}

			cursor = marker = token_start = buffer;
			limit = buffer + buffer_size;
		}



	}	// namespace Lexer
}	// namespace SpasmImpl

