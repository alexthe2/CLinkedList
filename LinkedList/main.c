#ifdef _MSC_VER
#pragma warning(disable:4996)
#include "vld.h"
#endif

#include "ListTools.h"
#include "LList.h"
#include "Utils.h"

#include <stdio.h>

void PrintElem(void *ctx) {
	int* pack = ctx;
	int val = *pack;
	printf("->%d", val);
}

/* A very very simple example */
int main() {
	LList list = CreateList(INT_LIST_CMP, EasyFree);

	AddItemSorted(list, PackInt(3));
	AddItemSorted(list, PackInt(5));
	AddItemSorted(list, PackInt(7));

	CallForAll(list, PrintElem);
	
	DestroyList(list);
}