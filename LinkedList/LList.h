/* Copyright (C) 2021 Alexander Procelewski - All Rights Reserved
 * https://github.com/alexthe2/CLinkedList
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#ifndef LLIST_H_
#define LLIST_H_

#pragma region Typedefs
typedef struct List* LList;
typedef struct ListNode* Node;

typedef int (*Compare)(void* a, void* b);
typedef void (*FreeContent)(void* ctx);
typedef void* (*ListCall)(void* ctx);
#pragma endregion 

#pragma region Structs
struct List {
	Node head;
	int count;

	Compare compare_function;
	FreeContent free_function;
};

struct ListNode {
	Node prev;
	Node next;

	void* content;
};
#pragma endregion 

#pragma region Functions
/// <summary>
/// Create a list. If you want to use default elements: <b>int</b>, <b>float</b>, <b>double</b>, <b>char*</b> use the default Compare functions. <b>TC: O(1)</b>
/// </summary>
/// <param name="compare">The compare function which should be used to compare two elements</param>
/// <param name="fc">The free function for the content which should be called for the cleanup</param>
/// <returns></returns>
LList CreateList(Compare compare, FreeContent fc);

/// <summary>
/// Destroy the list and frees all it's nodes. <b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
void DestroyList(LList list);

/// <summary>
/// Add an item to the beginning of the list. <b>TC: O(1)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="item">The item to be added</param>
void AddItem(LList list, void* item);

/// <summary>
/// Add an item to the list which is sorted. <b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="item">The item to be added</param>
void AddItemSorted(LList list, void* item);

/// <summary>
/// Remove the first occurrence with the given content. <b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="item">The content to be removed</param>
void RemoveItem(LList list, void* content);

/// <summary>
/// Get the element at i. <b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="i">The position</param>
/// <returns>The content, or NULL if out of range</returns>
void* PeekAt(LList list, int i);

/// <summary>
/// Get the size of the list. This function only works if inserting/removing has been called via the given functions. <b>TC: O(1)</b>
/// </summary>
/// <param name="list">The list</param>
/// <returns></returns>
int Size(LList list);

/// <summary>
/// Call a function foreach element. <b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="lc">The function to be called</param>
void CallForAll(LList list, ListCall lc);

/// <summary>
/// Call a function for the element at i and return the result.<b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="lc">The function to be called</param>
/// <param name="i">The position</param>
/// <returns>The return of the function, or NULL if out of range</returns>
void* CallForAt(LList list, ListCall lc, int i);

/// <summary>
/// Check whether the element is in the list.<b>TC: O(N)</b>
/// </summary>
/// <param name="list">The list</param>
/// <param name="ctx">The element to check</param>
/// <returns>1 if exists, 0 if doesn't exist</returns>
int ElementExists(LList list, void* ctx);
#pragma endregion 

#endif // LLIST_H_
