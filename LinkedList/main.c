#define MEMORY_TEST 0

#ifdef _MSC_VER
#pragma warning(disable:4996)
#if MEMORY_TEST
#include "vld.h"
#endif
#endif

#include "ListTools.h"
#include "LList.h"

#include <stdio.h>

void PrintElem(void *ctx) {
	int* pack = ctx;
	int val = *pack;
	printf("->%d", val);
}

/* A very very simple example */
int main() {
	LList list = LL_CreateList(INT_LIST_CMP, EasyFree);

	LL_AddItemSorted(list, PackInt(3));
	LL_AddItemSorted(list, PackInt(5));
	LL_AddItemSorted(list, PackInt(7));

	LL_CallForAll(list, PrintElem);
	
	LL_DestroyList(list);
}