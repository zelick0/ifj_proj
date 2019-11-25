#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>

#include "symtable.h"
#include "scanner.h"

//polozka stacku
typedef struct stackItem {
  Token_type tokenType;
  tNodeType nodeType;
  struct stackItem *next;
} symStackItem;

//stack
typedef struct {
  symStackItem *top;
} symStack;

//inicializace stacku
void symstackInit(symStack* stack);
//vlozeni symbolu do stacku
bool symstackPush(symStack* stack, Token_type token, tNodeType type);
//popnuti stacku jednou
bool symstackPop(symStack* stack);
//popnuti stacku vicekrat
void symstackPopMore(symStack* stack, int howmany);
//vrati ukazatel na item na vrchu stacku
symStackItem* symstackTop(symStack* stack);
//zrusi stack
void symstackFree(symStack* stack);
