

static char ioutBuffer[80];

#define iOUT(x){itoa(x, ioutBuffer, 10 );OUT(ioutBuffer);}

#define OUT(x)  {codeOut->Msg(x);}

class BCParser : public CParser
{
public:
	int Parse();
	
	int ParseVar();
	int ParseParam();
	int ParseFunc();
	int ParseBlock();
	int ParseStatement();
	int ParseIdent();
	int ParseFuncCall(Func *);
	int ParseAssignment(Symbol *);
	int ParseReturn();
	int ParseWhile();
	int ParseInstr();
	int ParseHost();

	int ParseExpression();
	void AssignCodeEmitter(CLog *l) {codeOut = l;}
	int FillOp();
	int GetOp();
	/*implement me!!!
	int InitCodeEmitter(char *);
	*/

private:
	
	int ParseExpressionOp(int op);
	int ParseExpressionMath(int op);


	CLog *codeOut;
	CStack<int> expr;
	CStack<int> op;
//	CStack<int> temp;

};
	
