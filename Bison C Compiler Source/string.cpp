#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TEMP FOR DEBUG
#include <iostream.h>
#define NO_IMPLENTATION cout<<"no implentation"<<""; return 0;

#include "token.h"
#include "operators.h"
#include "String.h"




#define NUM_OPS 7
#define MAX_DOUBLE_OPS 2

int CStringInfo::opID = 0;
char CStringInfo::OP;
short CStringInfo::keyword =-1;
/*
struct Op
{
	char *op;
	int ID;
};

Op SingleOps[] = {">",OP_TYPE_GREATER_THAN,
				 "<", OP_TYPE_LESS_THAN_THAN,
				">=",OP_TYPE_GREATER_THAN_EQUAL_TO,
				"<=",OP_TYPE_LESS_THAN_EQUAL_TO,
				"+",OP_TYPE_PLUS,
				"-",OP_TYPE_MINUS,
				"*",OP_TYPE_MULTIPLY,
                ">>",OP_TYPE_SHIFT_RIGHT ,
                 "<<",OP_TYPE_SHIFT_LEFT};
*/

struct Op
{
	char op;
	int ID;
};

Op SingleOps[] = {'>',OP_TYPE_GREATER_THAN,
				 '<', OP_TYPE_LESS_THAN,
				'=',OP_TYPE_EQUALS,
				//"<=",OP_TYPE_LESS_THAN_EQUAL_TO,
				'+',OP_TYPE_PLUS,
				'-',OP_TYPE_MINUS,
				'*',OP_TYPE_MULTIPLY,
				'!',OP_NOT};
                //">>",OP_TYPE_SHIFT_RIGHT ,
                 //"<<",OP_TYPE_SHIFT_LEFT};
/*
struct DoubleOp
{
	char base;
	int numSupp;
	char next[1];
	
	
	
};
*/

char doubleOps[] = {'>',2,'>',OP_TYPE_SHIFT_RIGHT,'=',OP_TYPE_GREATER_THAN_EQUAL_TO,
						'<',2,'<',OP_TYPE_SHIFT_LEFT, '=',OP_TYPE_LESS_THAN_EQUAL_TO,
						NULL,0,NULL,0, 0,0};




  
bool CStringInfo::IsCharNumeric(char &c)
{
	
	return((c >= '0') && ( c <= '9'));
	
}


bool CStringInfo::IsCharDelimiter(char &c)
{
	return ( (c == ':') || (c == ',') //|| (c ==  '"')
		  || (c == '[') || (c == ']') || (c == '{')
		  || (c == '}') || (c == '(') ||(c == ')'));
		  
}


bool CStringInfo::IsCharWhiteSpace(char &c)
{
	return ( (c == ' ') || (c == '\t') );
}
bool CStringInfo::IsCharNewLine(char &c)
{
	return ( (c == '\n') );
}

bool CStringInfo::IsCharIdent(char &c)
{
	return( (IsCharNumeric(c)) || ((c>='a') && (c<='z')) 
		  || ((c>='A') && (c<='Z')) || (c == '_')  );
}

bool CStringInfo::VerifyNumeric(char *c, bool &negativeNumber)
{
	negativeNumber = 0;

	if(!c)
		return 0;

	
	//look for an early escape, and check for a negation sign
	if  ( !(IsCharNumeric(c[0])) )  
	{
		if((c[0]!= '-'))
			return 0;
		else
			negativeNumber = true;
	} 
	
	//make sure the negation sign is not the only 
	//character in the string, this would be an error 
	if(negativeNumber)
	{
		if(strlen(c) <=1)
		{
			return 0;
		}
	}
	return 1;
}

bool CStringInfo::IsOpCompatible(char& s, char& d)
{
	/*	
	DoubleOp doubleOps[] = {'>',2,'>',OP_TYPE_SHIFT_RIGHT,'=',OP_TYPE_GREATER_THAN_EQUAL_TO,
						'<',2,'<',OP_TYPE_SHIFT_LEFT, '=',OP_TYPE_LESS_THAN_EQUAL_TO,
	*/

	bool found =0;
	bool res = 0;
	char *temp;
	int i =0;
	int counter;
	for(temp = &doubleOps[i];temp!=NULL;i++)
	{
		if(temp[i] == s)
		{
			found =1;
			break;
		}
		i++;
		 counter = doubleOps[i];
		i+=(counter*2);

	}
	
//	DoubleOp doubleOps[] = {'>',2,'>',OP_TYPE_SHIFT_RIGHT,'=',OP_TYPE_GREATER_THAN_EQUAL_TO,		
	if(found)
	{
		i++;
		counter = doubleOps[i];
		i++;
		for(int j=0; j<counter; j++)
		{
			if(temp[i] == d)
			{
				opID = temp[(i+1)];
				res = 1;
				break;
			}
			i+=2;
		}

	}
	


	return res;
}

bool CStringInfo::IsCharOp(char &c)
{
	Op *temp;

	for(int i=0; i < NUM_OPS; i++)
	{
		temp = &SingleOps[i];
		if(c == temp->op)
		{
			opID = temp->ID;
			OP  = temp->op;
			return 1;
		}
	}
	return 0;
}

bool CStringInfo::IsStringInt(char *c)
{
	bool negativeNumber;
	
	
	if(!(VerifyNumeric(c,negativeNumber)))
		return 0;

	//loop through the string
	for(int i=1; i <(unsigned short)strlen(c); i++)
	{
		//check to see if we have a number
		if( !(IsCharNumeric(c[i])) )
			return 0;
	}
	
	//at this point the whole string has been verified
	//it must be a number
	return 1;
}

bool CStringInfo::IsStringFloat(char *c)
{
	bool res, negativeNumber, radixFound = 0;

	//verify the start of the number
	res = VerifyNumeric(c,negativeNumber);
	
	if( (!res) )
	{
		//it may still be a float, if the first char is te radix
		if(c[0]!='.')
			return 0;
		else
			radixFound = 1;//mark the radix as found

	}
	
	//loop through the string
	for(int i=1; i <(unsigned short)strlen(c); i++)
	{
		//check to see if we have a number
		if( !(IsCharNumeric(c[i])) )
		{
			//check for the radix
			if(c[i]!= '.')
				return 0;
			else
			{
				//make sure the radix has not already been found
				if(radixFound)
					return 0;
				else
					radixFound = 1;//mark the radix as found
			}
			
		}
			
	}
	//at this stage we know the string is a valid
	//but did we find the radix that qulifies it as a float
	return (radixFound ? 1 : 0);	

}

bool CStringInfo::IsStringIdent(char *c)
{
	bool res,b;
	
	if(!c)
		return 0;

	//make sure the start of the string is not a number
	res = VerifyNumeric(c,b);
	
	//identifiers cannot start with a numeric
	if(res)
		return 0;

	int len = strlen(c);
	if(!len)
		return 0;
	//loop thrugh the string 
	for(int i =0; i < len; i++)
	{
		//check for an identifier
		if(!(IsCharIdent(c[i])) )
			return 0;
	}
	 
	//at this point we have a valid identifier
	return 1;
	
}
bool CStringInfo::IsStringWhiteSpace(char *c)
{
	if(c == NULL)
		return 0;
	
	//an empty string still qualifys
    if(strlen(c) == 0)
		return 1;

	//loop throughthe string
	for(int i=0 ; i < (unsigned short)strlen(c); i++)
	{
		//check for whiespace
		if(!(IsCharWhiteSpace(c[i])))
			return 0;
	}
	
	//we found a valid one
	return 1;
}

void CStringInfo::MakeStringLowerCase(char *c)
{
		/*************************************
	takes the string in buff
	and sets every character to lowercase
	*************************************/

	//check for a valid string
	if(!c)
		return;

	int len = strlen(c);
	for(int i=0;i<len;i++)
	{
		*c = tolower(*c);
		c++;
	}
}

bool CStringInfo::IsStringQuote(char *c)
{
	int len = strlen(c);
	
	if(len<2)
		return false;

	if((c[0]!='"') || (c[(len-1)]!='"') )
	return 0;
	
	for(int i=1; i<(len-1);i ++)
	{
		if(c[i] =='"')
		{
			if(c[i-1] !='\\')
				return 0;
		}
	}
	return 1;
}

void CStringInfo::RemoveStringQuotes(char *s)
{
	if(!s)
	{
		return;
	}
	int len = strlen(s);
	if(len<1)
	{
		return;
	}
	
	for(int i=1;i<len-1;i++)
	{
		s[(i-1)] = s[i];
	}
	
	s[i-1] = '\0';

}