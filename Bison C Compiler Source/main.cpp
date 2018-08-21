
#include <iostream.h>
#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>


#include <vector>
#include "operators.h"
#include "token.h"
#include "instructions.h"
#include "file.h"
#include "log.h"
#include "String.h"
#include "lexer.h"
#include "functions.h"
#include "symbol.h"
#include "strings.h"
//#include "label.h"
#include "script.h"
#include "parser.h"
#include "stack.h"
#include "BCParser.h"
//#include "ASMParser.h"


#define C_FILE_IN "test.txt"
#define ASM_FILE_OUT "asm\\bspLoad.basm"

void PrintToken(int tok);

int numInvalidTokens=0;

void main()
{



	int instrIndex =0;
	
//	AddAllInstructions();
	
	CLog log;
 	log.Init("log.txt");

	CLog out;

	out.Init(ASM_FILE_OUT);
	CLexer lexer;
	BCParser parser;

	lexer.InitLogFile(&log);
	parser.AssignLogFile(&log);
	parser.AssignCodeEmitter(&out);

	lexer.LoadASMFile(C_FILE_IN);
	lexer.PrepFile();
//	lexer.AssignInstrTable(&instrTable);

	parser.AssignLexer(&lexer);
/*
	char *lex;
	int tok;
*/
/*

	cout<<"LEXEMES" <<"\n\n";
	while(!(lexer.IsFileFinished()))
	{
		
		tok = lexer.GetNextToken();
		lex = (char*)lexer.GetLexeme();

		if(tok!=TOKEN_TYPE_NEWLINE)
		{
			cout <<"Lexeme: " <<lex<< " Token: "; PrintToken(tok); cout<<"\n";
		}
		else
		{
			cout<<"Token: "; PrintToken(tok); cout<<"\n";
		}

	}
*/
while(!(lexer.IsFileFinished()))
{
	parser.Parse();
}
cout <<"\nlex errors: "<<numInvalidTokens<<" parse errors: "<<parser.GetErrors()<<endl;
parser.log->Msg("\nlex errors: %d  parse errors: %d ",numInvalidTokens,parser.GetErrors() );



cout<<"\npress any key then enter to quit."<<endl;

/*
to stop this demo from being just a flash on the screen in release mode
get some dummy input when everythings finished
*/

char dummy[10];
cin>>dummy;


}


void PrintToken(int tok)
{
		switch (tok)
		{
			case TOKEN_TYPE_NEWLINE:
			{
				cout<<"TOKEN_TYPE_NEWLINE";
			}break;
			case TOKEN_TYPE_INT:
			{
				cout<<"TOKEN_TYPE_INT";
			}break;
			case TOKEN_TYPE_FLOAT:
			{
				cout<<"TOKEN_TYPE_FLOAT";
			}break;
			case TOKEN_TYPE_STRING:
			{
				cout<<"TOKEN_TYPE_STRING";
			}break;
			case TOKEN_TYPE_IDENT:
			{
				cout<<"TOKEN_TYPE_IDENT";
			}break;
			case TOKEN_TYPE_COLON:
			{
				cout<<"TOKEN_TYPE_COLON";
			}break;
			case TOKEN_TYPE_OPEN_BRACKET:
			{
				cout<<"TOKEN_TYPE_OPEN_BRACKET";
			}break;
			case TOKEN_TYPE_CLOSE_BRACKET:
			{
				cout<<"TOKEN_TYPE_CLOSE_BRACKET";
			}break;
			case TOKEN_TYPE_COMMA:
			{
				cout<<"TOKEN_TYPE_COMMA";
			}break;
			case TOKEN_TYPE_OPEN_BRACE:
			{
				cout<<"TOKEN_TYPE_OPEN_BRACE";
			}break;
			case TOKEN_TYPE_CLOSE_BRACE:
			{
				cout<<"TOKEN_TYPE_CLOSE_BRACE";
			}break;


			case TOKEN_TYPE_OPEN_CURLY:
			{
				cout<<"TOKEN_TYPE_OPEN_CURLY";
			}break;
			case TOKEN_TYPE_CLOSE_CURLY:
			{
				cout<<"TOKEN_TYPE_CLOSE_CURLY";
			}break;


		case TOKEN_TYPE_INSTR:
			{
				cout<<"TOKEN_TYPE_INSTR";
			}break;

		case TOKEN_TYPE_SETSTACKSIZE:
			{
				cout<<"TOKEN_TYPE_SETSTACKSIZE";
			}break;

		case TOKEN_TYPE_VAR:
			{
				cout<<"TOKEN_TYPE_VAR";
			}break;
		case TOKEN_TYPE_FUNC:
			{
				cout<<"TOKEN_TYPE_FUNC";
			}break;
		case TOKEN_TYPE_PARAM:
			{
				cout<<"TOKEN_TYPE_PARAM";
			}break;


		case OP_TYPE_LESS_THAN:
			{
				cout<<"OP_TYPE_LESS_THAN";
			}break;
		case OP_TYPE_GREATER_THAN:
			{
				cout<<"OP_TYPE_GREATER_THAN";
			}break;
		case OP_TYPE_SHIFT_LEFT:
			{
				cout<<"OP_TYPE_SHIFT_LEFT";
			}break;
		case OP_TYPE_SHIFT_RIGHT:
			{
				cout<<"OP_TYPE_SHIFT_RIGHT";
			}break;


		case TOKEN_TYPE_INVALID:
			{
				cout<<"*************Tis is bad************";
				numInvalidTokens++;
			}break;

			case TOKEN_TYPE_REG_RETVAL:
			{
				cout<<"TOKEN_TYPE_REG_RETVAL";
			}break;


			case TOKEN_TYPE_WHILE:
			{
				cout<<"TOKEN_TYPE_WHILE";
			}break;
			
			case TOKEN_TYPE_RETURN:
			{
				cout<<"TOKEN_TYPE_RETURN";
			}break;

			case TOKEN_TYPE_FOR:
			{
				cout<<"TOKEN_TYPE_FOR";
			}break;

			case TOKEN_TYPE_IF:
			{
				cout<<"TOKEN_TYPE_IF";
			}break;

			case TOKEN_TYPE_ELSE:
			{
				cout<<"TOKEN_TYPE_ELSE";
			}break;


		default:
			cout<<"This really shouldnt happen";
		}
}
