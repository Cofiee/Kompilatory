#include "globals.h"

// TODO: change to heap allocated array
//IdString* TokenNames = calloc(15 * sizeof(IdString))
IdString TokenNames[35] = {
    "ProgramSym", 
    "BeginSym", "EndSym",
    "ReadSym", "WriteSym",  
    "IfSym", "ThenSym",
    "WhileSym", "DoSym",
    "VarSym",
    "Id", 
    "IntSym", "FloatSym",
    "IntLiteral", "FloatLiteral", "BoolLiteral", 
    "LParen", "RParen", 
    "PlusSym", "MinusSym", "MultiplySym", "DivideSym", 
    "Lesser", "Equal", "Greater", "LeEqual", "NotEqual", "GrEqual",
    "AssignSym", "SemiColonSym", "ColonSym", "CommaSym", "DotSym",
    "EofSym", "ErrorSym"
};

int  IdVal;           /* the symbol-table entry for an ID */
IdString Lexeme;   /* the lexeme for an INT literal    */

/* symbol table */

int LastSymbol;  /* must be initialized to 0 */

struct SymEntry SymbolTable[MAX_SYMBOL+1];