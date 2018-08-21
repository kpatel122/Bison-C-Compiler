#include <stdlib.h>         
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include <iostream.h>

#include <vector>

#include "error.h"
#include "instructions.h"
#include "token.h"
#include "file.h"
#include "log.h"
#include "String.h"
#include "lexer.h"
#include "functions.h"
#include "symbol.h"
#include "strings.h"
//nclude "label.h"
#include "script.h"
#include "parser.h"
#include "stack.h"
#include "operators.h"
#include "BCPArser.h"

//Instr *gl;

long labelCount = 0;



int BCParser::ParseVar()
{
	
	if(CParser::ParseVar() == -1)
		return -1;

	OUT("var ");
	int index;
	index = script.symbolTable.GetNumSymbols();

	Symbol *sym = this->script.symbolTable.GetSymbolByIndex((index-1));
	
	OUT(sym->name);
	OUT("\n");
	return 1;
}

int BCParser::ParseParam()
{
	char funcName[64];
	strcpy(funcName,lex);

	int size = 1;
	

    int s = - ((currFuncStackSize+2) + (numLocalVar) + 1);
	if(script.symbolTable.AddSymbol(funcName,currFuncIndex,s,size) == -1)
	{
		Error("Symbol already defined")
	}

	numParam++;
	currFuncStackSize++;

	return 1;
}

int BCParser::ParseFunc()
{
	
	OUT("func ")
	CParser::ParseFunc();
	OUT(lex);
	OUT("{ \n");
	
	
	int numPar=0;
	
	GetNextToken();
	SkipNewlines();

	if(tok!=TOKEN_TYPE_OPEN_CURLY)
	{
		Error("Expected (");
		SkipNewlines();
	}

	GetNextToken();
	SkipNewlines();

	while(1)
	{
		

		if(tok == TOKEN_TYPE_CLOSE_CURLY)
			break;

		if(  (tok == TOKEN_TYPE_IDENT)  )
		{
			
			numPar++;
			BCParser::ParseParam();
			OUT("param ");
			OUT(lex);
			OUT("\n");
			
			
			GetNextToken();
			SkipNewlines();

			if(tok == TOKEN_TYPE_CLOSE_CURLY)
			break;
			
			if(tok!=TOKEN_TYPE_COMMA)
				Error("Expected ','")

			GetNextToken();
			SkipNewlines();


		}
		else
		{
			Error("Unkown function declarer");
		}

		

	}

	GetNextToken();
    SkipNewlines();
	
	if(tok!=TOKEN_TYPE_OPEN_BRACE)
	{
		Error("Expected {");
		SkipNewlines();
	}
	
	OUT("\n");

	int index = script.funcTable.GetNumFunc();
	Func *func = script.funcTable.GetFuncByIndex((index-1));
	
	
	ParseBlock();

	func->numParams = numPar;
	this->inFunction = false;

	OUT("\n}\n")



	return 1;
}

int BCParser::GetOp()
{
	GetNextToken();
	SkipNewlines();

	switch(tok)
	{
	case TOKEN_TYPE_NEWLINE:
		{
			return -1;
		}break;
//	case TOKEN_TYPE_PLUS:
//		{
//		}
	}
}	

int BCParser::FillOp()
{
	GetNextToken();
	SkipNewlines();

	switch(tok)
	{
		case OP_TYPE_PLUS:
		{
			
			op.push(OP_TYPE_PLUS);
		}break;
		case OP_TYPE_MINUS:
		{
			
			op.push(OP_TYPE_MINUS);
		}break;
		case OP_TYPE_MULTIPLY:
		{
			
			op.push(OP_TYPE_MULTIPLY);
		}break;
			case OP_TYPE_DIVIDE:
		{
			
			op.push(OP_TYPE_DIVIDE);
		}break;

	}

	return 1;
}

/*
int BCParser::ParseExpression()
{
	CStack<int> temp;
	CStack<int> tempOp;

	int currVar;
	int tempVar;

	int res;
	
	int var1;
	int var2;



int *tArr = temp.GetStack();


	while (1)
	{

		if(script.symbolTable.GetSymbolByIndex(lex!=NULL) || 
			(script.stringTable.DoesStringExist(lex)!=NULL) ||
			IS_TOKEN(TOKEN_TYPE_INT) || IS_TOKEN(TOKEN_TYPE_STRING) ||
			IS_TOKEN(TOKEN_TYPE_FLOAT))
			{
			var1=atoi(lex);
			temp.push(var1);

			OUT("PUSH ")iOUT(var1) OUT("\n");
			
			GetNextToken();
		
			
			}
		else if(CStringInfo::IsCharOp(*lex)==false)
		{
			Error("Parsing Expression");
		}
		
	

		
		

	if(tok == OP_TYPE_MULTIPLY || tok == OP_TYPE_DIVIDE )
	{
	
		GetNextToken();
	
		int ar = atoi( lex);
		temp.push(ar);

		OUT("PUSH ") iOUT(ar) OUT("\n")
		
		var1 = temp.pop();
		var2 = temp.pop();
		
		if(tok == OP_TYPE_MULTIPLY)
		res = var1 * var2;
		else
		res = var1 / var2;

		
		temp.push(res);
		
		OUT("POP _T0\n")OUT("POP _T1\n")
		OUT("MUL _T0,_T1\n")OUT("PUSH _T0\n")


	
		GetNextToken();

		

			
	}
	else
		
		if(tok == OP_TYPE_PLUS || tok == OP_TYPE_MINUS )
		{
			op.push(tok);
			GetNextToken();
	
	}
	 else
		break;
	}


int size = op.GetSize();
 for(int j= 0;j<size;j++ )
 {
	int currOp = op.pop();
	
		if(currOp == OP_TYPE_PLUS)
		{
			currVar = temp.pop();
			tempVar = temp.pop();
			res = currVar + tempVar;
			
			
			temp.push(res);

			OUT("POP _T0, \n"); OUT("POP _T1, \n");
			OUT("ADD _T0,_T1\n")
			OUT("PUSH _T0\n")
		}
		if(currOp == OP_TYPE_MINUS)
		{
			currVar = temp.pop();
			tempVar = temp.pop();
			res = currVar - tempVar;
			temp.push(res);
			
			OUT("POP _T0, \n"); OUT("POP _T1, \n");
			OUT("MIN _T0,_T1\n")
			OUT("PUSH _T0\n")

		}
 }
int finalRes=temp.GetAtIndex(0);
temp.clear();
cout<<"res is: "<<finalRes<<"\n";
return finalRes;
}
*/

bool IsTokenOp(int ptok)
{


	return (ptok == OP_TYPE_GREATER_THAN || ptok == OP_TYPE_LESS_THAN ||
			ptok == OP_TYPE_GREATER_THAN_EQUAL_TO 
			|| ptok== OP_TYPE_LESS_THAN_EQUAL_TO);
}

int BCParser::ParseExpressionOp(int op)
{
		char *instr;
		
//		int currVar = temp.pop();
//		int tempVar = temp.pop();
		int res;
		switch(op)
		{
		case OP_TYPE_GREATER_THAN:
			{
				instr = "JG ";
			//	res = (currVar > tempVar);
			}break;
		case OP_TYPE_LESS_THAN:
			{
				instr = "JL ";
		//		res = (currVar < tempVar);
			}break;
		case OP_TYPE_LESS_THAN_EQUAL_TO:
			{
				instr = "JLE ";
			//	res = (currVar <= tempVar);
			}break;
		case OP_TYPE_GREATER_THAN_EQUAL_TO:
			{
				instr = "JGE ";
			//	res = (currVar >= tempVar);
			}break;
		}

		
//		temp.push(res);
			
			
		
		OUT("POP _T0, \n"); OUT("POP _T1, \n");
		OUT(instr) OUT("_T0, T1, _L")iOUT(labelCount)OUT("\n");
		OUT("PUSH 0\n JMP _L")iOUT(labelCount)OUT("1\n")
		OUT("_L")iOUT(labelCount)OUT(":\nPUSH 1\n");
		OUT("_L")iOUT(labelCount)OUT("1:\n")
		labelCount++;

		return res;
}

int BCParser::ParseExpression()
{

	
	CStack<int> tempOp;

	int currVar;
	int tempVar;
	
bool isVar = false;

	int res;
	
	int var1;
	int var2;



	while (1)
	{

			Symbol *sy=	script.symbolTable.GetSymbolByName(lex,this->currFuncIndex);
			if(IS_TOKEN(TOKEN_TYPE_INT) || IS_TOKEN(TOKEN_TYPE_STRING) ||
			IS_TOKEN(TOKEN_TYPE_FLOAT))
			{
			
				var1=atoi(lex);
//				temp.push(var1);

				OUT("PUSH ")iOUT(var1) OUT("\n");
			
				GetNextToken();
			
			}
			else if(sy!=NULL)
			{
			
				 OUT("PUSH ")OUT(sy->name)OUT("\n");
				 GetNextToken();
				 isVar = true;
			}
		
		
		
	if(IsTokenOp(tok) )
	{
			op.push(tok);
			GetNextToken();
			
			
		
	}
	else
	if(tok == OP_TYPE_MULTIPLY || tok == OP_TYPE_DIVIDE )
	{
	
		GetNextToken();
		//SkipNewlines();
		
		
		int ar = atoi( lex);
//		temp.push(ar);

		
		sy = script.symbolTable.GetSymbolByName(lex,currFuncIndex);

		if(isVar)
		{
		OUT("PUSH ") OUT(lex) OUT("\n")
		}
		else
		{
		OUT("PUSH ") iOUT(ar) OUT("\n")
		}
		
//		var1 = temp.pop();
//		var2 = temp.pop();
//		res = var1 * var2;
//		temp.push(res);
		
		OUT("POP _T0\n")OUT("POP _T1\n")
		OUT("MUL _T0,_T1\n")OUT("PUSH _T0\n")


	
		GetNextToken();
	//	SkipNewlines();
		
		
	
			
	}
	else
		if(tok == OP_TYPE_PLUS || tok == OP_TYPE_MINUS )
		{
		
	
		op.push(tok);

			GetNextToken();
		//SkipNewlines();

		
			
		
	}
	 else
		break;
	}


int size = op.GetSize();
 for(int j= 0;j<size;j++ )
 {
	int currOp = op.pop();
	
		if(currOp == OP_TYPE_PLUS)
		{
//			currVar = temp.pop();
////			tempVar = temp.pop();
//			res = currVar + tempVar;
			
			
//			temp.push(res);

			OUT("POP _T0, \n"); OUT("POP _T1, \n");
			OUT("ADD _T0,_T1\n")
			OUT("PUSH _T0\n")
		}
		if(currOp == OP_TYPE_MINUS)
		{
//			currVar = temp.pop();
//			tempVar = temp.pop();
//			res = currVar - tempVar;
//			temp.push(res);
			
			OUT("POP _T0, \n"); OUT("POP _T1, \n");
			OUT("MIN _T0,_T1\n")
			OUT("PUSH _T0\n")

		}
		if(IsTokenOp(currOp) )
		{
			this->ParseExpressionOp(currOp);
		
		}
 }
//int finalRes=temp.GetAtIndex(0);
//cout<<"res is: "<<finalRes<<"\n";
//temp.clear();
//return finalRes;
return 1;
}

int BCParser::ParseHost()
{
	
	char funcName[64];

	strcpy(funcName,lex);
	
	GetNextToken();
	SkipNewlines();
	
	TOKEN_ASSERT(TOKEN_TYPE_OPEN_CURLY,"(");

	GetNextToken();
	SkipNewlines();
	
	while(1)
	{
		if(script.symbolTable.GetSymbolByIndex(lex!=NULL) || 
			(script.stringTable.DoesStringExist(lex)!=NULL) ||
			IS_TOKEN(TOKEN_TYPE_INT) || IS_TOKEN(TOKEN_TYPE_STRING) ||
			IS_TOKEN(TOKEN_TYPE_FLOAT))
			{
				OUT("PUSH "); OUT(lex) OUT("\n");
				

				GetNextToken();
				SkipNewlines();

				if(IS_TOKEN(TOKEN_TYPE_COMMA))
				{
					GetNextToken();
					SkipNewlines();
					continue;
				}
				else
				{
					TOKEN_ASSERT(TOKEN_TYPE_CLOSE_CURLY,")");
					break;
				}
			}
	}
	
	
		OUT("CALLHOST "); OUT(funcName); OUT("\n");
	
		return 1;
}

int BCParser::ParseFuncCall(Func *func)
{
	int param = func->numParams;
	
	GetNextToken();
	SkipNewlines();
	
	TOKEN_ASSERT(TOKEN_TYPE_OPEN_CURLY,"(");
	
	
		GetNextToken();
		SkipNewlines();

	for(int i=0;i<func->numParams; i++)
	{

		
			if(script.symbolTable.GetSymbolByIndex(lex!=NULL) || 
			(script.stringTable.DoesStringExist(lex)!=NULL) ||
			IS_TOKEN(TOKEN_TYPE_INT) || IS_TOKEN(TOKEN_TYPE_STRING) ||
			IS_TOKEN(TOKEN_TYPE_FLOAT))
			{
				OUT("PUSH "); OUT(lex) OUT("\n");
			}
			else
				Error("Invalid parameters")
			

		
		
		GetNextToken();
		SkipNewlines();
		if((i+1)>=func->numParams)
		{
			
			break;
		}
		else
		{
			
			TOKEN_ASSERT(TOKEN_TYPE_COMMA,",")
			GetNextToken();
			SkipNewlines();
		}

		

	}

	TOKEN_ASSERT(TOKEN_TYPE_CLOSE_CURLY,")");

	OUT("CALL "); OUT(func->name); OUT("\n");

	return 1;
}

int BCParser::ParseAssignment(Symbol *symb)
{
	
	
	GetNextToken();
	SkipNewlines();
	TOKEN_ASSERT(OP_TYPE_EQUALS,"=")

	GetNextToken();
	SkipNewlines();

	ParseExpression();

	OUT("POP _T0\n")
	OUT("MOV ");OUT(symb->name); OUT(", _T0 \n\n") 
}

int BCParser::ParseIdent()
{
	Symbol *symb = script.symbolTable.GetSymbolByName(lex,this->currFuncIndex);	
	Func*  func = script.funcTable.GetFuncByName(lex); 
	if(func!=NULL)
	{
		ParseFuncCall(func);		
	}
	else
	if(symb!=NULL)
	{
		ParseAssignment(symb);
	}
	else
	{
		this->ParseHost();
	}


	return -1;
}

int BCParser::ParseReturn()
{
	
	
	if(this->isMainDefined == true)
	{
		int mindex = script.mainIndex;

		if(currFuncIndex == mindex)
		{
			OUT("EXIT \n")
				return 1;
		}
	}
	
		GetNextToken();
		SkipNewlines();

		if(*lex!=';')
		{
			int res = ParseExpression();
			OUT("POP _T0, _RetVal\n RET\n")

		}
		else
		{
		OUT("RET \n")
		}	
		return 1;
	
}


long nextLabel()
{
	return labelCount++;
}
int BCParser::ParseWhile()
{
	GetNextToken();
	SkipNewlines();
	

	int label = (int)nextLabel(); 
	int endLabel = (int)nextLabel();
	TOKEN_ASSERT(TOKEN_TYPE_OPEN_CURLY,"(")
	
	GetNextToken();
	
	OUT("_L")iOUT(label)OUT(": \n");
	
	ParseExpression();

	OUT ("POP _T0\n")
	OUT("JE 0, ")OUT("_L")iOUT(endLabel)OUT("\n")

	//GetNextToken();
	
	TOKEN_ASSERT(TOKEN_TYPE_CLOSE_CURLY,")")
	GetNextToken();
	SkipNewlines();
	TOKEN_ASSERT(TOKEN_TYPE_OPEN_BRACE,"{")
	OUT("{\n")

	ParseBlock();

	OUT("JMP _L")iOUT(label)OUT("\n");

	OUT("_L")iOUT(endLabel)OUT(": \n");

	OUT("}\n")
	


}
int BCParser::ParseInstr()
{
	
	OUT(lex)
	//GetNextToken();
	//SkipNewlines();
	return 1;
}
int BCParser::ParseStatement()
{
	//lexer->GetNextValidChar();
	if(this->lexer->IsFileFinished())
		return -1;
	switch(tok)
	{

		
		case TOKEN_TYPE_WHILE:
		{
			ParseWhile();
		}break;
		case TOKEN_TYPE_RETURN:
		{
			ParseReturn();
		}break;
		case TOKEN_TYPE_INT:
		{
			ParseExpression();
		}break;
		case TOKEN_TYPE_FUNC:
		{
			ParseFunc();
		}break;

	case TOKEN_TYPE_PARAM:
		{
			ParseParam();
		}break;
	case TOKEN_TYPE_VAR:
		{
			
			ParseVar();
		
		}break;
	case TOKEN_TYPE_INSTR:
		{
			
			ParseInstr();
		}break;
	case TOKEN_TYPE_OPEN_BRACE:
		{
			ParseBlock();
		}break;
	case TOKEN_TYPE_IDENT:
		{
			ParseIdent();
	
		}break;
	}
	return 1;
}
int BCParser::ParseBlock()
{
	
	

	while(tok!=TOKEN_TYPE_CLOSE_BRACE)
	{
		GetNextToken();
		SkipNewlines();
		ParseStatement();
	}

	//OUT("}")
	return 1;
}
int BCParser::Parse()
{
	//lexer->GetNextValidChar();
	GetNextToken();
	SkipNewlines();

	ParseStatement();

	return 1;
}


	
