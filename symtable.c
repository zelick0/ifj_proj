

#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void BSTInit (tBSTNodePtr *RootPtr) {
//Funkce provede počáteční inicializaci stromu před jeho prvním použitím.
	 *RootPtr = NULL;
}

tBSTNodePtr BSTSearch (tBSTNodePtr RootPtr, char* K)	{
//Funkce vyhledá uzel v BVS s klíčem K.
	 if(RootPtr != NULL){
		 if(RootPtr->Key > K){
			 return BSTSearch(RootPtr->LPtr, K);
		 }else if(RootPtr->Key < K){
			 return BSTSearch(RootPtr->RPtr, K);
		 }else if(RootPtr->Key == K){
			 return RootPtr;
		 }else{
			 return NULL;
		 }
	 }else{
		 return NULL;
	 }

}


void BSTInsert (tBSTNodePtr* RootPtr, char* K, void* Content, tNodeType ntype)	{
//Vloží do stromu RootPtr uzel.
	 if(*RootPtr == NULL){
		 tBSTNodePtr x = malloc(sizeof(struct tBSTNode));
		 x->Key = K;
		 x->BSTNodeCont = Content;
		 x->nodeType = ntype;
		 x->LPtr = NULL;
		 x->RPtr = NULL;
		 *RootPtr = x;
	 }else{
		 if((*RootPtr)->Key > K){
			 BSTInsert(&((*RootPtr)->LPtr), K, Content, ntype);
		 }else if((*RootPtr)->Key < K){
			 BSTInsert(&((*RootPtr)->RPtr), K, Content, ntype);
		 }else if((*RootPtr)->Key == K){
			 (*RootPtr)->BSTNodeCont = Content;
		 }
	 }
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
//Pomocná funkce pro vyhledání, přesun a uvolnění nejpravějšího uzlu.
	 if(*RootPtr != NULL){
		 if((*RootPtr)->RPtr == NULL){
			 PtrReplaced->Key = (*RootPtr)->Key;
			 PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
			 tBSTNodePtr x = *RootPtr;
			 *RootPtr = (*RootPtr)->LPtr;
			 free(x);
		 }else{
			 ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr);
		 }
	 }
}

void BSTDelete (tBSTNodePtr *RootPtr, char* K) 		{
//Zruší uzel stromu, který obsahuje klíč K.
	 if(*RootPtr != NULL){
		 if((*RootPtr)->Key > K){
			 BSTDelete(&(*RootPtr)->LPtr, K);
		 }else if((*RootPtr)->Key < K){
			 BSTDelete(&(*RootPtr)->RPtr, K);
		 }else{
			 tBSTNodePtr x = *RootPtr;
			 if(x->RPtr == NULL){
				 *RootPtr = x->LPtr;
				 free(x);
			 }else if(x->LPtr == NULL){
				 *RootPtr = x->RPtr;
				 free(x);
			 }else{
				 ReplaceByRightmost(*RootPtr, &(*RootPtr)->LPtr);
			 }
		 }
	 }
}

void BSTDispose (tBSTNodePtr *RootPtr) {
//Zruší celý strom
	 if(*RootPtr != NULL){
		 BSTDispose(&(*RootPtr)->LPtr);
		 BSTDispose(&(*RootPtr)->RPtr);
		 free(*RootPtr);
		 *RootPtr = NULL;
	 }
}

//------------------------------------------

void symtableInit(tSymtable* tab){
	BSTInit(&(tab->root));
}

void symtableInsertF(tSymtable* tab, char* key, tInsideFunction * data){
	BSTInsert(&(tab->root), key, data, nFunction);
}

void symtableInsertV(tSymtable* tab, char* key, tInsideVariable * data){
	BSTInsert(&(tab->root), key, data, nVariable);
}

tBSTNodePtr symtableSearch(tSymtable* tab, char* key){
	return BSTSearch(tab->root, key);
}

void symtableDelete(tSymtable* tab, char* key){
	BSTDelete(&(tab->root), key);
}

void symtableDispose(tSymtable* tab){
	BSTDispose(&(tab->root));
}
