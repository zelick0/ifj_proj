#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>

#include "symstack.h"

void symstackInit(symStack* stack){
  stack->top = NULL;
}

bool symstackPush(symStack* stack, Token_type token, tNodeType type){
  symStackItem* nitem = (symStackItem*)malloc(sizeof(symStackItem));

  if(nitem != NULL){
    nitem->tokenType = token;
    nitem->nodeType = type;
    nitem->next = stack->top;

    stack->top = nitem;
    return true;
  }else{
    return false;
  }
}

bool symstackPop(symStack* stack){
  if(stack->top != NULL){
    symStackItem* out = stack->top;
    stack->top = out->next;

    free(out);
    
    return true;
  }else{
    return false;
  }
}

void symstackPopMore(symStack* stack, int howmany){
  for(int i = 0; i < howmany; i++){
    symstackPop(stack);
  }
}

symStackItem* symstackTop(symStack* stack){
  return stack->top;
}

void symstackFree(symStack* stack){
  while(symstackPop(stack));
}
