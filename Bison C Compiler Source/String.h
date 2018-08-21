
/*String info*/
class CStringInfo
{

public:

	static	bool IsCharNumeric(char &);
	static	bool IsCharIdent(char &);
	static	bool IsCharNewLine(char &);
	static	bool IsCharWhiteSpace(char &);
	static	bool IsCharDelimiter(char &);
	
	static  bool IsStringKeyWord(char *);
	static	bool IsStringIdent(char *);
	static	bool IsStringInt(char *);
	static	bool IsStringFloat(char *);
	static	bool IsStringWhiteSpace(char *);
	static	bool IsStringQuote(char *);
	static  void MakeStringLowerCase(char *);
	static  void RemoveStringQuotes(char *);
	static   bool IsCharOp(char &c);
	static int GetCurrOpID(){return opID;} 
	static bool IsOpCompatible(char&,char&);


private:
	static int opID;
	static char OP;
	
	static short keyword;
	static	bool VerifyNumeric(char *,bool &);
	
	/*Make a singleton class*/
	CStringInfo();
	~CStringInfo();
	
};