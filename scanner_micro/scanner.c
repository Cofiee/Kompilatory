/* C version of the scanner for the Tiny language */

/*  Tiny grammar
    <program>        -> BEGIN <stmt list> END
    <stmt list>      -> <stmt list> <stmt> | <stmt>
    <stmt>           -> <ident> := <expr>;
    <stmt>           -> READ ( <id list> ) ;
    <stmt>           -> WRITE ( <expr list> ) ;
    <id list>        -> <id list>, <ident> | <ident>
    <expr list>      -> <expr list>, <expr> | <expr> 
    <expr>           -> <expr> <op> <factor> | <factor>
    <factor>         -> ( <expr> ) | <ident> | INT
    <op>             -> + | - 
    <ident>          -> ID 
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "globals.h"

/* Beginning of scanner declarations */

IdString TokenBuffer;
int TokenPtr;

char LineBuffer[MAX_LINE_LENGTH + 1];
int LineLength, LinePtr, LineCount;

char EofFlag;

void ToLowerCase()
    /* Convert characters to lower case characters */
{
    int i;
    for (i = 0; i < LineLength; i++)
        LineBuffer[i] = tolower(LineBuffer[i]);
}

void ListThisLine()
{
int i;
    /* produce a listing of the source program */
    printf("\n");
    for (i = 0; i < LineLength; i++)
        printf("%c", LineBuffer[i]);
    printf("\n");
}

void GetNewLine()
    /* get a new input line */
{
    LineCount++;

    LineLength = 0;
    while ((EofFlag = getchar()) != EOL && EofFlag != EOF) 
        LineBuffer[LineLength++] = EofFlag;

    LineBuffer[LineLength++] = ' ';

    ListThisLine();

    LinePtr = -1;

    ToLowerCase();
}

void GetNextChar (char * c)
{
    if (LinePtr + 1 >= LineLength)
        GetNewLine();
    *c = LineBuffer[LinePtr+1];
    LinePtr = LinePtr + 1;
}

void PutNextChar()
{
    LinePtr = LinePtr - 1;
}


void ClearBuffer()
{
    TokenPtr = 0;
    TokenBuffer[0] = EOS;
}

void BufferChar (char c)
{
    TokenBuffer[TokenPtr++] = c;
}

void LexicalError (char c)
{
    printf("\n***** Lexical error: line %d at %c\n", LineCount, c);
}

void BufferName(char c)
{
    char Inspect;

    BufferChar(c);
    GetNextChar(&Inspect);
    while (isalnum(Inspect) || Inspect == '_') 
    {
        BufferChar(Inspect);
        GetNextChar(&Inspect);
	}
    PutNextChar();
    BufferChar(EOS);
}

bool BufferNumberWithFloatValidation(c)
{
    char Inspect;

    BufferChar(c);
    GetNextChar(&Inspect);
    bool float_flag = false;
    while (isdigit(Inspect) || Inspect == '.') 
    {
        if (Inspect == '.' && float_flag)
            break;
        if (Inspect == '.')
            float_flag = true;
        BufferChar(Inspect);
        GetNextChar(&Inspect);
	}
    PutNextChar();
    BufferChar(EOS);
    return float_flag;
}

void BufferIntLiterals(char c) 
{
    char Inspect;

    BufferChar(c);
    GetNextChar(&Inspect);
    while (isdigit(Inspect)) 
    {
        BufferChar(Inspect);
        GetNextChar(&Inspect);
	}
    PutNextChar();
    BufferChar(EOS);
}

Token CheckReserved()
{
    int i;
    for (i = 1; i <= LastSymbol; i++) 
        if (strcmp(TokenBuffer, SymbolTable[i].Name) == 0)
            return SymbolTable[i].Code;
    return Id;
}

Token GetNextToken()
{
    char CurrentChar, Inspect;

    IdVal = NONE;
    ClearBuffer();

    while (EofFlag != EOF) 
	{
        GetNextChar(&CurrentChar);
        if (isspace(CurrentChar))
            ;  /* null statement - skip blanks and tabs */
        else if (isalpha(CurrentChar)) 
        {
            BufferName(CurrentChar);
            if ((IdVal = LookUp (TokenBuffer)) == 0)  /* a new identifier */
                IdVal = Enter(TokenBuffer, Id);
            return CheckReserved();
        }
        else if (isdigit(CurrentChar))
        {
            bool float_flag = BufferNumberWithFloatValidation(CurrentChar);
            strcpy(Lexeme, TokenBuffer);
            if (float_flag) 
                return FloatLiteral;
            else
                return IntLiteral;            
        }
        else 
        {
	        switch (CurrentChar) { /* other tokens */
                case '(':
                    return LeftParenthesis; 
                case ')':
                    return RightParenthesis; 
                case ';':
                    return SemiColonSym; 
                case ',':
                    return CommaSym; 
                case '.':
                    return DotSym;
                case ':':
                    GetNextChar(&Inspect);
                    if (Inspect == '=')
                        return AssignSym;
                    else 
                    {
                        PutNextChar();
                        return ColonSym;
                    }
                case '+':
                    return PlusSym; 
                case '-':
                    GetNextChar(&Inspect);
                    if (Inspect == '-')
                    {
                        GetNewLine(); /* skip rest of input line */
                        break;
                    }
                    else
                    {
                        PutNextChar();
                        return MinusSym; 
                    }
                case '*':
                    return MultiplySym;
                case '/':
                    return DivideSym;
                case '<':
                    GetNextChar(&Inspect);
                    if (Inspect == '=') 
                        return LeEqualSym;
                    else if (Inspect == '>')
                        return NotEqualSym;
                    else {
                        PutNextChar();
                        return LesserSym;
                    }
                case '=':
                    return EqualSym;
                case '>':
                    GetNextChar(&Inspect);
                    if (Inspect == '=')
                        return GrEqualSym;
                    else 
                    {
                        PutNextChar();
                        return GreaterSym;
                    }
                        
                default:
                    LexicalError(CurrentChar);
                    return ErrorSym;
            }
        }
    }
    return EofSym; /* EofFlag == EOF */
}

