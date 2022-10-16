/****************************************************************
 *       T H E   S Y M B O L   T A B LE                         *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

int LookUp (IdString S)
  /*  Returns index of the entry for S, or 0 if it is not found */
{
int i;
   for (i = 1; i <= LastSymbol; i++) 
      if (strcmp(SymbolTable[i].Name, S) == 0) 
         return i;
   return 0;
}

int Enter(IdString S, Token Code)
  /*  Put S unconditionally into the symbol table and returns inde
      of the entry for S */
{
   if (LastSymbol < MAX_SYMBOL) {
      LastSymbol++;
      SymbolTable[LastSymbol].Name = (char *)malloc(strlen(S)+1);
      strcpy(SymbolTable[LastSymbol].Name, S);
      SymbolTable[LastSymbol].Code = Code;
      return LastSymbol;
      }
   else {
      printf("Symbol Table Overflow");
      return (MAX_SYMBOL+1);
      }
}

void LoadKeywords()
{
   Enter("begin", BeginSym);
   Enter("end", EndSym);
   Enter("read", ReadSym);
   Enter("write", WriteSym);
}

void ListSymbolTable()
/* for debugging */
{
int i;
   printf("\n--------- Symbol Table ----------\n");
   for (i = 1; i <= LastSymbol; i++) 
        printf("%s\n",SymbolTable[i].Name);
   printf("\nTotal: %d\n", LastSymbol);
}
