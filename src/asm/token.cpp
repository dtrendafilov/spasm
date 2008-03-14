#include <string>

#include "token.hpp"

namespace SpasmImpl
{
	namespace Lexer
	{

		ASMToken::ASMToken (ASMToken::Token _type, size_t _lineno,
				const char * _start, const char *_end)
			: type (_type), lineno (_lineno)
		{
			if (type == integer || type == xinteger)
				value_int = strtol (_start, NULL, 0);
			else if (type == ident)
				if (_end)
					value_str = std::string (_start, _end);
				else
					value_str = std::string (_start);

		}

		ASMToken::Token ASMToken::token_type () const {
			return type;
		}

		int ASMToken::get_value_int () const {
			return value_int;
		}

		const std::string & ASMToken::get_value_str () const {
			return value_str;
		}

		size_t ASMToken::get_lineno () const {
			return lineno;
		}

	}	// namespace Lexer
}	// namespace SpasmImpl
