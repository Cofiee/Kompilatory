#include <stdbool.h>
#include <string.h>

#define EOL	'\n'
#define EOS	'\0'

/* size definitions */
#define ID_STRING_LENGTH      32   /* max length of a line */
#define MAX_LINE_LENGTH       132  /* max length of a line */
#define TOKEN_SIZE            32   /* max length of a token */
#define MAX_SYMBOL  	      50   /* size of symbol table */
#define NONE                  -1   /* default token attribute */

/* tokens */
typedef enum {
    ProgramSym, 
    BeginSym, EndSym, 
    ReadSym, WriteSym,
    IfSym, ThenSym,
    WhileSym, DoSym,
    VarSym,
    Id, 
    IntSym, FloatSym,
    IntLiteral, FloatLiteral, BoolLiteral, 
    LeftParenthesis, RightParenthesis, 
    PlusSym, MinusSym, MultiplySym, DivideSym,
    LesserSym, EqualSym, GreaterSym, LeEqualSym, NotEqualSym, GrEqualSym,
    AssignSym, SemiColonSym, ColonSym, CommaSym, DotSym,
    EofSym, ErrorSym
} Token;

/* a string definition */
typedef char IdString[ID_STRING_LENGTH];

/* translation from enum to strings */
extern IdString TokenNames[35];

/* The global variables communicating the lexeme of integers and
   identifiers to the parser */
extern int  IdVal;           /* the symbol-table entry for an ID */
extern IdString Lexeme;   /* the lexeme for an INT literal    */

/* symbol table */
struct SymEntry {           /* form of symbol table entry */
    char *Name;             /* allocate space dynamically for lexeme */
    Token Code; 
    };

extern int LastSymbol;      /* must be initialized to 0 */

extern struct SymEntry SymbolTable[MAX_SYMBOL+1];