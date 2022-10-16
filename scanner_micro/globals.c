#include "globals.h"

// TODO: change to heap allocated array
//IdString* TokenNames = calloc(15 * sizeof(IdString))
IdString TokenNames[19] = {
    "ProgramSym", 
    "BeginSym", "EndSym", 
    "ReadSym", "WriteSym", 
    "Id", 
    "IntLiteral", 
    "BoolLiteral", 
    "LParen", "RParen", 
    "Plus", "Minus", "Multiply", "Divide", 
    "Lesser", "Equal", "Greater", "LeEqual", "NotEqual", "GrEqual"
    "Assign", "SemiColon", "Comma", 
    "EofSym", "ErrorSym"
};

int  IdVal;           /* the symbol-table entry for an ID */
IdString IntLexeme;   /* the lexeme for an INT literal    */

/* symbol table */

int LastSymbol;  /* must be initialized to 0 */

struct SymEntry SymbolTable[MAX_SYMBOL+1];