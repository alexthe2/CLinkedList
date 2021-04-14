# CLinkedList

This is a very simple implementation of a double linked list in C.

# Structs and functions

The Main Element is the `LList` and it's functions are:

| Function      |      | Description                                  |
| ------------- | ---- | -------------------------------------------- |
| CreateList    |      | Creates a List                               |
| DestroyList   |      | Frees the list                               |
| AddItem       |      | Adds an Item                                 |
| AddItemSorted |      | Adds a sorted Item                           |
| RemoveItem    |      | Removes an Item                              |
| PeekAt        |      | Returns the Content at the position i        |
| Size          |      | Returns the size of the list                 |
| CallForAll    |      | Calls a function foreach element of the list |
| CallForAt     |      | Calls a function for the element at          |
| ElementExists |      | Checks whether an element exists             |

# Predefined

In `ListTools`, there are predefined functions to use for list with basic datatypes

# Examples

Create a List and add 5 elements in order, then print those:

```c
#include "ListTools.h"
#include "LList.h"

#include <stdio.h>

void PrintElem(void *ctx) {
  int* pack = ctx;
  int val = *pack;
  printf("%d ", val);
}

int main() {
  LList list = CreateList(INT_LIST_CMP, EasyFree);

  AddItemSorted(list, PackInt(3));
  AddItemSorted(list, PackInt(5));
  AddItemSorted(list, PackInt(12));
  AddItemSorted(list, PackInt(4));
  AddItemSorted(list, PackInt(1));

  CallForAll(list, PrintElem);

  DestroyList(list);
}
```

We are using `INT_LIST_CMP` as well as `EasyFree` from `ListTools`, as we have a basic list of integers

# Additional info

In the `main.c` a header is used:

```c
#ifdef _MSC_VER
#pragma warning(disable:4996)
#include "vld.h"
#endif
```

if you are copying the main.c and not including Visual Leak Detector, make sure to remove `#include "vld.h"`, if you are building in a non VisualC debugger, 
like gcc you can also remove the entire fragment, though it will not be evaluated by the compiler

# License
You can use this code for free under the MIT License. Would be nice if you could referenece me though ;)
