#include <string>

#ifndef  TOKEN_HPP
#define  TOKEN_HPP

#define TOKENS			\
        TOK(push)		\
        TOK(pop)		\
        TOK(dup)		\
        TOK(print)		\
        TOK(read)		\
        TOK(plus)		\
        TOK(minus)		\
        TOK(multiply)	\
        TOK(divide)		\
        TOK(modulus)	\
        TOK(gotrue)		\
        TOK(gofalse)	\
        TOK(go)			\
        TOK(call)		\
        TOK(ret)		\
        TOK(load)		\
        TOK(store)		\
        TOK(label)		\
        TOK(ident)      \
        TOK(integer)	\
		TOK(xinteger)	

namespace SpasmImpl
{
	namespace Lexer
	{
		class ASMToken
		{
			public:
				enum Token {
					halt = 0, 
#define TOK(x) x,
					TOKENS
#undef TOK
					notused
				} ;

				ASMToken (Token, size_t, const char * = NULL, const char * = NULL);

				Token token_type () const;

				size_t get_lineno () const;

				int get_value_int () const;

				const std::string & get_value_str () const;

			private:
				Token type;
				
				size_t lineno;

				int value_int;

				std::string value_str;
		} ;

		class TokenStream
		{
			public:
				virtual void push_token (const ASMToken &) = 0;
				virtual ~TokenStream () { };
		} ;
	}	// namespace Lexer
}	// namespace SpasmImpl

#undef TOKENS


#endif 

