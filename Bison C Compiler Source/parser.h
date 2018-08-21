
#define PRINT(x) cout<<x<<""; log->Msg(x);
#define Error(x){ cout<<"Error: "<<x<<"\n"; numErrors++; \
log->Msg("Error : %s\n", x); return -1; }


static char errBuff[80];
#define TOKEN_ASSERT(x,y) { if(x!=tok){sprintf(errBuff,"Expected Token: %s ",y); \
					Error(errBuff); } }  

#define IS_TOKEN(x)(x == tok) 

#define DEFAULT_STACK_SIZE 1024

struct BASM_Header
{
	char id[4];
	
	int numInstr;
	int numFunc;
	int numStrings;
	int numAPICalls;
	int numSymbols;
	int numLineLable;
	int stackSize;
	int main;
	int mainIndex;
	int globalSize;

};

class CParser
{

public:

	CParser();
	~CParser();
	CLog *log;
	
	
		
	int WriteASMFile(char *);

	int WriteFuncTable();
	int WriteSymbolTable();
	int WriteStringTable();
	int WriteAPITable();
	int WriteLabelTable();
	int WriteInstructions();
	int WriteHeader();
		
	void PrintStats();
	void AssignLexer(CLexer *l) {lexer = l;}
	int InitLogFile(char *);
	void AssignLogFile(CLog *l){log = l;}
	
	int GetErrors() {return numErrors;}
//	virtual int Parse() = 0;
	/*
	
	CFuncTable   funcTable;
	CSymbolTable symbolTable;
	CStringTable stringTable;
	CStringTable apiFuncTable;
	CLabelTable  labelTable;
	int globalSize;
	int stackSize;
	int mainIndex;
	*/


protected:
	
	void SkipNewlines();
	void GetNextToken();
	void GetLexeme() {lex = lexer->GetLexeme();}
	
virtual	int ValidateParam(int,Operand*,Operand*);
	
virtual	int ParseFunc();
virtual	int ParseParam();
virtual	int ParseVar();
virtual int Parse()=0;

//virtual	int ParseLabel();
virtual	int ParseCloseFune();


	bool inFunction;
	bool isMainDefined;
	bool stackSet;
	

	int instrIndex;

	int currFuncStackSize;

	int currFuncIndex;
	int numLocalVar;
	int numParam;
	int numErrors;


	CLexer       *lexer;


	
	Script script;
	
	
	int tok;
	char *lex;
	
	
	FILE *f;
	



};