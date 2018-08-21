
#define MAX_LEXEME_SIZE 1024

class CLexer
{

public:	
	CLexer();
	~CLexer();
	int InitLogFile(char *);
	int InitLogFile(CLog *l);
	int GetNextToken();
	char *GetCurrentLexeme();
	char *GetLexeme(){return currLexeme;}
	
	int GetNumberLines() {return numberLines;}
	void SkipLine();
	int LoadASMFile(char*);
	char *GetSource(){return pSource;}
	void PrepFile();
	bool IsFileFinished() {return endOfFile;} 
//	void AssignInstrTable (CInstrTable* table)  {instrTable = table;}
	void PrintToken(int);
	int PrintOp(int);
//	CInstrTable *instrTable;

	char *GetCurrPos() {return currPos;}
		void GetNextValidChar();
private:
	
	CFile *fp;
	CLog *log;
	
	void SkipWhiteSpaces();

	void StripComments(char *,int);
	void TrimWhiteSpaces(char *,int);
	void MoveToNextLine();
	bool EndOfFile();
	
	
	char *pSource;
	char **ppSource;
	char *currPos;
	char *endPos;
	char *currLexeme;
	int currToken;
	bool endOfFile;
	
	int numInvalidTokens;
	int numberLines;
	int currentLine;
	int currLineLength;
	int index0;
	int index1;
	int lines;
	int len;
	char lexBuffer[MAX_LEXEME_SIZE];
	bool newLineFound;
	

};