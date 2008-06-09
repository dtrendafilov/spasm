#include <iostream>
#include <iomanip>

#include <cassert>

#include "lexer.hpp"
#include "token.hpp"

using namespace SpasmImpl::Lexer::ASM;

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
		void push_token (const Token &token)
		{
			Token::Token_type ttype = token.type ();
			std::cout.width (8);
			std::cout << token.lineno ();
			std::cout << ": " << token_name[ttype];
			if (ttype == Token::integer || ttype == Token::xinteger)
				std::cout << '|' << token.value_int () << '|';
			else if (ttype == Token::ident)
				std::cout << '|' << token.value_str () << '|';
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
	SpasmImpl::Lexer::ASM::Lexer lex(std::cin);
	TokenDumper td;

	assert (lex.tokenize (td));

	return 0;
}
