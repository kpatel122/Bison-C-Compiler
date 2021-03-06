#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <iostream.h>
//#include "instructions.h"
#include "keywords.h"
#include "token.h"
#include "file.h"
#include "String.h"
#include "log.h"
#include "operators.h"
#include "lexer.h"


#define PRINT(x) cout<<x<<""; log->Msg(x);

CLexer::CLexer()
{
	index0 = index1 =currentLine = numberLines = numInvalidTokens= 0;
	endOfFile = newLineFound = false;
//	ppSource = NULL;
	ppSource = new char * [1024];//(char**)malloc(sizeof(char*));
}



CLexer::~CLexer()
{

	//free(ppSource);
	//delete[] ppSource;
}


int CLexer::InitLogFile(CLog *l)
{
	log = l;
	return 1;
}

int CLexer::InitLogFile(char *f)
{
	log = new CLog;
	log->Init(f);

	if(!log)
		return -1;

	return 1;
}

int CLexer::LoadASMFile(char *fileName)
{
	fp = new CFile;

	if(fp->LoadFile(fileName,BISON_FILE_READ)!=BISON_SUCCESS)
		return -1;

	len = fp->GetFileLen();

	if(!len)
		return -1;

	pSource = new char[len+1];
	
	

	fp->ReadFile(pSource,sizeof(char),len+1);
	
	pSource[len] = '\0';

	currPos = pSource;
	endPos = &pSource[len];

	if(!pSource)
		return -1;

	return 1;
}

void CLexer::SkipLine()
{
	while(*currPos!='\n')
	{
		currPos++;
		index0++;
	}

	currPos++;
	index0++;
}

void CLexer::StripComments(char *str,int line)
{
	int counter = 0;
	bool inStr = false;
	int lastLine = index0;
	


	while(1)
	{
		


		if(*currPos == '"')
		{
		  if ((counter < 1))
				inStr = !(inStr);

			else
			{
				if ( *(((currPos)-1)) != '\\')
				{
					inStr = !(inStr);
				}
			}
		}
		
		if ( !((currPos) < (endPos)) )
		{
			pSource[index0] = '\0';
			ppSource[line] = &pSource[lastLine];
			
			
			
			lastLine = index0;

			

			return;
		}

		if ( (*currPos == '\n') && (inStr == false) )
		{
			
			//if((!pSource) || (!ppSource[index0]))
			//	continue;
			pSource[index0] = '\0';
			ppSource[line] = &pSource[lastLine];
			//ppSource[line][0] = pSource[lastLine];

			currPos+=1;
			index0+=1;
			
			lastLine = index0;

			

			return;
		}

		if( (*currPos == ';')  && (inStr == false) )
		{
			pSource[index0] = '\0';
			ppSource[line] = &pSource[lastLine];
			

			SkipLine();
			
			//currPos+=2;
			//index0+=2;
			
			lastLine = index0;

			return;
		}
		
		currPos++;
		index0++;
		counter++;
		
	}
}



void CLexer::PrepFile()
{
	index0 = 0;
	static int line = 0;
	char *str;
	while(currPos < endPos)
	{
		str = currPos;
		
		StripComments(str,line);
		line++;
		
	

	}
	
	index0 = index1 = 0;
	numberLines = line;
	currentLine = 0;
	currPos = ppSource[currentLine];
	currLineLength = strlen(ppSource[currentLine]);
	GetNextValidChar();

	
}


bool CLexer::EndOfFile()
{
	return ( !((currPos) < (endPos)) );
}


void CLexer::SkipWhiteSpaces()
{ 
	
	
	
	while(*currPos ==' ' || *currPos =='\t')
	{
	
		currPos++;
		index1++;
		index0++;

		
	}

	
}

void CLexer::MoveToNextLine()
{
	index0 = index1 = 0;
	currentLine++;
	currPos = ppSource[currentLine];
	currLineLength = strlen(ppSource[currentLine]);
	newLineFound = true;

}

void CLexer::GetNextValidChar()
{


	if(currPos>=(endPos-1))
	{
		endOfFile = true;
		return;
	}
	
	if(!(index0 < currLineLength))
	{
		if(currentLine >= (numberLines-1))
		{
			
			endOfFile = true;
			return;
		}
		
		MoveToNextLine();

	
		
	
	}
	
	
	if(CStringInfo::IsCharWhiteSpace(*currPos))
	{
		SkipWhiteSpaces();
	}
	if((*currPos == '\n') || ((*currPos == '\0')))
	{
		MoveToNextLine();
	}
	
}

char *CLexer::GetCurrentLexeme()
{
	bool inStr = false;
	int counter = 0;
	bool inOP = false;
	
	if(newLineFound)
	{
		newLineFound = false;
		lexBuffer[0]= '\n';
		lexBuffer[1]= '\0';
		GetNextValidChar();
		return lexBuffer;
	}
	

	while(1)
	{
		lexBuffer[counter] = ppSource[currentLine][index0];
		
	
		
		if(*currPos == '"')
		{
			if ((counter < 1))
				inStr = !(inStr);

			else
			{
				if ( *(((currPos)-1)) != '\\')
				{
					inStr = !(inStr);
				}
			}

			if(inStr == false)
			{
				lexBuffer[counter+1] = '\0';

				currPos++;
				index0++;
				counter++;

				GetNextValidChar();
				return lexBuffer;
			}
		}
		
		
		if((CStringInfo::IsCharDelimiter(*currPos)) && (inStr == false) )
		{
			if(!counter)
			{
				currPos++;
				index0++;
				counter++;
			}

			lexBuffer[counter] = '\0';
		//	CStringInfo::MakeStringLowerCase(lexBuffer);
			
			GetNextValidChar();
			return lexBuffer;
		}

		if((CStringInfo::IsCharOp(*currPos)) && (inStr == false) )
		{
			/*
			if(IsCharOp((*currPos+1)))
			{
				CStringInfo::IsOpCompatible(*currPos,*(curPos+1);
			}
			*/
			if(!counter)
			{
				currPos++;
				index0++;
				counter++;
			}

			lexBuffer[counter] = '\0';
		//	CStringInfo::MakeStringLowerCase(lexBuffer);
			
			GetNextValidChar();
			return lexBuffer;
		}

		if ((*currPos == ' ') && (inStr == false))
		{
			lexBuffer[counter] = '\0';
		//	CStringInfo::MakeStringLowerCase(lexBuffer);
			
			currPos++;
			index0++;
			counter++;
			
			GetNextValidChar();
			return lexBuffer;


		}

		currPos++;
		index0++;
		counter++;
		
	}
	
}

int CLexer::GetNextToken()
{
	currLexeme = GetCurrentLexeme();
	
	if(CStringInfo::IsCharNewLine(*currLexeme))
		return TOKEN_TYPE_NEWLINE;

	if(CStringInfo::IsStringQuote(currLexeme))
		return TOKEN_TYPE_STRING;
	
	if(CStringInfo::IsStringInt(currLexeme))
		return TOKEN_TYPE_INT;

	if(CStringInfo::IsStringFloat(currLexeme))
		return TOKEN_TYPE_FLOAT;

	if(CStringInfo::IsStringIdent(currLexeme))
	{

		
		if(strcmp(KEYWORD_ELSE,currLexeme)==0)
		return TOKEN_TYPE_ELSE;

		if(strcmp(KEYWORD_IF,currLexeme)==0)
		return TOKEN_TYPE_IF;

		if(strcmp(KEYWORD_WHILE,currLexeme)==0)
		return TOKEN_TYPE_WHILE;

		if(strcmp(KEYWORD_FOR,currLexeme)==0)
		return TOKEN_TYPE_FOR;

		if(strcmp(KEYWORD_RETURN,currLexeme)==0)
		return TOKEN_TYPE_RETURN;
		
		if(strcmp(KEYWORD_FUNCTION,currLexeme)==0)
		return TOKEN_TYPE_FUNC;

		if(strcmp(KEYWORD_VARIABLE,currLexeme)==0)
		return TOKEN_TYPE_VAR;

		if(strcmp(KEYWORD_PARAM,currLexeme)==0)
		return TOKEN_TYPE_PARAM;

		if(strcmp(KEYWORD_REG,currLexeme)==0)
		return TOKEN_TYPE_REG_RETVAL;

		if(strcmp(KEYWORD_STACK_SIZE,currLexeme)==0)
		return TOKEN_TYPE_SETSTACKSIZE;
		
//		if(instrTable->IsValidInstr(currLexeme))
//		return TOKEN_TYPE_INSTR;
		
		return TOKEN_TYPE_IDENT;
	
	}
	
	if(CStringInfo::IsCharDelimiter(*currLexeme))
	{
		if(strcmp(OPEN_CURLY,currLexeme)==0)
		return TOKEN_TYPE_OPEN_CURLY;

		if(strcmp(CLOSE_CURLY,currLexeme)==0)
		return TOKEN_TYPE_CLOSE_CURLY;
		
		if(strcmp(OPEN_BRACE,currLexeme)==0)
		return TOKEN_TYPE_OPEN_BRACE;

		if(strcmp(CLOSE_BRACE,currLexeme)==0)
		return TOKEN_TYPE_CLOSE_BRACE;

		if(strcmp(OPEN_BRACKET,currLexeme)==0)
		return TOKEN_TYPE_OPEN_BRACKET;

		if(strcmp(CLOSE_BRACKET,currLexeme)==0)
		return TOKEN_TYPE_CLOSE_BRACKET;

		if(strcmp(COLON,currLexeme)==0)
		return TOKEN_TYPE_COLON;

		if(strcmp(COMMA,currLexeme)==0)
		return TOKEN_TYPE_COMMA;

	
	}
	if(CStringInfo::IsCharOp(*currLexeme))
	{
			char c = *(currPos);
			if(CStringInfo::IsCharOp(c) )
			{
				if(CStringInfo::IsOpCompatible(*currLexeme,c))
				{
					currPos++;
					index0++;
					GetNextValidChar();
					return CStringInfo::GetCurrOpID();
				}
				else
				return TOKEN_TYPE_INVALID;
			}
			return CStringInfo::GetCurrOpID();
			
	}
	

	return TOKEN_TYPE_INVALID;
	
	

}

int CLexer::PrintOp(int tok)
{
	/*
#define  52
#define  53
#define  54
#define  55
#define  56
#define  57
#define  58
#define  59
#define OP_NOT 60
*/
	switch (tok)
	{
	case OP_TYPE_GREATER_THAN:
		{
			PRINT("OP_TYPE_GREATER_THAN");
		}break;

	case OP_TYPE_LESS_THAN:
		{
			PRINT("OP_TYPE_LESS_THAN");
		}break;
	case OP_TYPE_GREATER_THAN_EQUAL_TO:
		{
			PRINT("OP_TYPE_GREATER_THAN_EQUAL_TO");
		}break;
	case OP_TYPE_LESS_THAN_EQUAL_TO:
		{
			PRINT("OP_TYPE_LESS_THAN_EQUAL_TO");
		}break;
	case OP_TYPE_PLUS:
		{
			PRINT("OP_TYPE_PLUS");
		}break;
	case OP_TYPE_MINUS:
		{
			PRINT("OP_TYPE_MINUS");
		}break;
	case OP_TYPE_DIVIDE:
		{
			PRINT("OP_TYPE_DIVIDE");
		}break;
	case OP_TYPE_MULTIPLY:
		{
			PRINT("OP_TYPE_MULTIPLY");
		}break;
	case OP_TYPE_SHIFT_RIGHT:
		{
			PRINT("OP_TYPE_SHIFT_RIGHT");
		}break;
	case OP_TYPE_SHIFT_LEFT:
		{
			PRINT("OP_TYPE_SHIFT_LEFT");
		}break;
	case OP_TYPE_EQUALS:
		{
			PRINT("OP_TYPE_EQUALS");
		}break;
	default:return-1;
	};

	return 1;
}

void CLexer::PrintToken(int tok)
{
	char *lex = GetLexeme();
	
	
	if(tok!=TOKEN_TYPE_NEWLINE)
	{
		cout<<"Lex: "<<lex<<" ";
		log->Msg("Lex: %s ",lex);
	}
	else
	{
		   cout<<"Lex: \\n ";
		log->Msg("Lex: \\n ",lex);
	}

	
	
	//this->"Lex: "<<lex<<" ";
	switch (tok)
		{
			case TOKEN_TYPE_NEWLINE:
			{
				PRINT("TOKEN_TYPE_NEWLINE");
			}break;
			case TOKEN_TYPE_INT:
			{
				PRINT("TOKEN_TYPE_INT");
			}break;
			case TOKEN_TYPE_FLOAT:
			{
				PRINT("TOKEN_TYPE_FLOAT");
			}break;
			case TOKEN_TYPE_STRING:
			{
				PRINT("TOKEN_TYPE_STRING");
			}break;
			case TOKEN_TYPE_IDENT:
			{
				PRINT("TOKEN_TYPE_IDENT");
			}break;
			case TOKEN_TYPE_COLON:
			{
				PRINT("TOKEN_TYPE_COLON");
			}break;
			case TOKEN_TYPE_OPEN_BRACKET:
			{
				PRINT("TOKEN_TYPE_OPEN_BRACKET");
			}break;
			case TOKEN_TYPE_CLOSE_BRACKET:
			{
				PRINT("TOKEN_TYPE_CLOSE_BRACKET");
			}break;
			case TOKEN_TYPE_COMMA:
			{
				PRINT("TOKEN_TYPE_COMMA");
			}break;
			case TOKEN_TYPE_OPEN_BRACE:
			{
				PRINT("TOKEN_TYPE_OPEN_BRACE");
			}break;
			case TOKEN_TYPE_CLOSE_BRACE:
			{
				PRINT("TOKEN_TYPE_CLOSE_BRACE");
			}break;
			

			case TOKEN_TYPE_OPEN_CURLY:
			{
				PRINT("TOKEN_TYPE_OPEN_CURLY");
			}break;
			case TOKEN_TYPE_CLOSE_CURLY:
			{
				PRINT("TOKEN_TYPE_OPEN_CURLY");
			}break;

			


		case TOKEN_TYPE_INSTR:
			{
				PRINT("TOKEN_TYPE_INSTR");
			}break;

		case TOKEN_TYPE_SETSTACKSIZE:
			{
				PRINT("TOKEN_TYPE_SETSTACKSIZE");
			}break;

		case TOKEN_TYPE_VAR:
			{
				PRINT("TOKEN_TYPE_VAR");
			}break;
		case TOKEN_TYPE_FUNC:
			{
				PRINT("TOKEN_TYPE_FUNC");
			}break;

		case TOKEN_TYPE_RETURN:
			{
				cout<<"TOKEN_TYPE_RETURN";
			}break;

		case TOKEN_TYPE_PARAM:
			{
				PRINT("TOKEN_TYPE_PARAM");
			}break;
		case TOKEN_TYPE_INVALID:
			{
				PRINT("*************This is bad************");
				numInvalidTokens++;
			}break;

			case TOKEN_TYPE_REG_RETVAL:
			{
				PRINT("TOKEN_TYPE_REG_RETVAL");
			}break;
/**/

			case TOKEN_TYPE_WHILE:
			{
				PRINT("TOKEN_TYPE_WHILE");
			}break;


			case TOKEN_TYPE_FOR:
			{
				PRINT("TOKEN_TYPE_FOR");
			}break;

			case TOKEN_TYPE_IF:
			{
				PRINT("TOKEN_TYPE_IF");
			}break;

			case TOKEN_TYPE_ELSE:
			{
				PRINT("TOKEN_TYPE_ELSE");
			}break;


		
	

		default:
			{
				if(PrintOp(tok)!=-1)
				break;
				else
			PRINT("This really shouldnt happen");
			}
		}
	PRINT(" \n");
	
}

/*
#define KEYWORD_FUNCTION "func"
#define KEYWORD_VARIABLE "var"
#define KEYWORD_PARAM "param"
#define KEYWORD_REG "reg0"
#define KEYWORD_STACK_SIZE "stacksize"
*/