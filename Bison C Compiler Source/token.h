


#define OPEN_BRACKET "["
#define CLOSE_BRACKET "]"
#define OPEN_BRACE "{"
#define CLOSE_BRACE "}"
#define OPEN_CURLY "("
#define CLOSE_CURLY ")"

#define COMMA ","
#define COLON ":"


enum TOKEN_TYPE
{
	    TOKEN_TYPE_INT,              
        TOKEN_TYPE_FLOAT,                      
        TOKEN_TYPE_STRING,                   
        TOKEN_TYPE_QUOTE,                     
        TOKEN_TYPE_IDENT,                   
        TOKEN_TYPE_COLON,                       
        TOKEN_TYPE_OPEN_BRACKET,               
        TOKEN_TYPE_CLOSE_BRACKET,              // An closing bracket
        TOKEN_TYPE_COMMA,                      // A comma
        TOKEN_TYPE_OPEN_BRACE,                // An openening curly brace
        TOKEN_TYPE_CLOSE_BRACE,               // An closing curly brace
        TOKEN_TYPE_NEWLINE,                    // A newline

		TOKEN_TYPE_INSTR,						// An instruction

        TOKEN_TYPE_SETSTACKSIZE,              // The SetStackSize directive
        TOKEN_TYPE_VAR,                        // The Var/Var [] directives
        TOKEN_TYPE_FUNC,                       // The Func directives
        TOKEN_TYPE_PARAM,// The Param directives
        
		TOKEN_TYPE_IF,
		TOKEN_TYPE_ELSE,
		TOKEN_TYPE_WHILE,
		TOKEN_TYPE_FOR,
		
		TOKEN_TYPE_REG_RETVAL,                 // The _RetVal directives

         TOKEN_TYPE_INVALID ,
		 TOKEN_TYPE_OPEN_CURLY,
		 TOKEN_TYPE_CLOSE_CURLY,
		 TOKEN_TYPE_RETURN,
		
		OP_TYPE_GREATER_THAN,
		OP_TYPE_LESS_THAN,
		OP_TYPE_GREATER_THAN_EQUAL_TO,
		OP_TYPE_LESS_THAN_EQUAL_TO,
		OP_TYPE_PLUS,
		OP_TYPE_MINUS,
		OP_TYPE_DIVIDE,
		OP_TYPE_MULTIPLY,
		OP_TYPE_SHIFT_RIGHT,
		OP_TYPE_SHIFT_LEFT,
		OP_NOT, 
		OP_TYPE_EQUALS,

};




