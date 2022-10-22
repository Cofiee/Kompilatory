#include <stdio.h>

#include "globals.h"

int main() {
    Token cur_token;

    LastSymbol = 0; /* Symbol table initialisation */
    LoadKeywords(); /* Load reserved words */
    ListSymbolTable();
    GetNewLine();   /* Read the first line */


    cur_token = GetNextToken();
    do {
        printf("<");
        printf("%s", TokenNames[cur_token] ); 
        printf(", ");
        if (cur_token == Id)
            printf("%s", SymbolTable[IdVal].Name);
        else if (cur_token == IntLiteral || cur_token == FloatLiteral) 
            printf("%s", Lexeme);
        printf("> ");
        cur_token = GetNextToken();
    } while (cur_token != EofSym);
    printf("<");
    printf("%d", cur_token);
    printf(", ");
    printf("> ");

    ListSymbolTable();
    return 0;
}