PROJECT (libspasm CXX)

ADD_LIBRARY (spasm_asm STATIC
	assembler.cpp bytecode.cpp lexer.cpp symbol.cpp token.cpp tokenizer.cpp)

ADD_EXECUTABLE (compiler main.cpp)
ADD_DEPENDENCIES (compiler spasm_asm)
TARGET_LINK_LIBRARIES (compiler spasm_asm)
