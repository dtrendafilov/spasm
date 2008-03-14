#include <iostream>
#include <iomanip>

#include <cassert>

#include "lexer.hpp"
#include "token.hpp"

using namespace SpasmImpl::Lexer;

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

class TokenDumper : public TokenStream
{
	public:
		void push_token (const ASMToken &token)
		{
			ASMToken::Token ttype = token.token_type ();
			std::cout.width (8);
			std::cout << token.get_lineno ();
			std::cout << ": " << token_name[ttype];
			if (ttype == ASMToken::integer || ttype == ASMToken::xinteger)
				std::cout << '|' << token.get_value_int () << '|';
			else if (ttype == ASMToken::ident)
				std::cout << '|' << token.get_value_str () << '|';
			std::cout << std::endl;
		}
	private:

		static const char *token_name[23];
} ;

const char *
TokenDumper::token_name[23] = {
	"halt", 
#define TOK(x) #x,
	TOKENS
#undef TOK
	"notused!!!"
} ;


int
main ()
{
	SpasmImpl::Lexer::ASMLexer lex(std::cin);
	TokenDumper td;

	assert (lex.tokenize (td));

	return 0;
}
