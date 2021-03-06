#include "LList.h"
#include "Utils.h"

/* ------------------ Private (not accessible from outside) ------------------ */
/* TC: O(1) */
Node CreateNode(void* content) {
	const Node node = (Node)SAFEMALLOC(sizeof(struct ListNode));

	node->content = content;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void FreeNode(FreeContent free_ctx, Node node) {
	free_ctx(node->content);
	free(node);
}

/* TC: O(1) */
Node AddNode(Node successor, Node node) {
	if (successor != NULL) {
		node->next = successor;
		successor->prev = node;
	}
	return node;
}

/* O(1) */
void RemoveElement(FreeContent free_ctx, Node node) {
	node->prev->next = node->next;
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}

	FreeNode(free_ctx, node);
}

/* ------------------ Public (accessible from outside) ------------------ */
/* TC: O(1) */
LList LL_CreateList(Compare compare, FreeContent fc) {
	LList list = (LList)SAFEMALLOC(sizeof(struct List));

	list->compare_function = compare;
	list->free_function = fc;
	list->head = NULL;
	list->count = 0;
	return list;
}

/* TC O(N) */
void LL_DestroyList(LList list) {
	Node curr = list->head;
	while (curr != NULL) {
		const Node next = curr->next;
		FreeNode(list->free_function, curr);
		curr = next;
	}
	free(list);
}

/* TC: O(1) */
void LL_AddItem(LList list, void* item) {
	const Node node = CreateNode(item);
	list->count++;

	list->head = AddNode(list->head, node);
}

/* TC: O(N) */
void LL_AddItemSorted(LList list, void* item) {
	Node node = CreateNode(item); /* O(1) */
	list->count++;

	Node curr = list->head;
	if (curr == NULL || list->compare_function(curr->content, item) >= 0) {  /* O(1) */
		node->next = curr;
		if (curr != NULL) {
			curr->prev = node;
		}
		list->head = node;
		return;
	}

	/* O(N-1) => O(N) */
	while (curr->next != NULL && list->compare_function(curr->next->content, item) < 0) {
		curr = curr->next;
	}

	/* O(1) */
	node = AddNode(curr->next, node);
	node->prev = curr;
	curr->next = node;
}

/* TC: O(N) */
void LL_RemoveItem(LList list, void* content) {
	Node curr = list->head;
	/* O(N) */
	while (curr != NULL && list->compare_function(curr->content, content) != 0) {
		curr = curr->next;
	}

	/* O(1) */
	if (list->head == curr) {
		if (curr != NULL) {
			list->head = curr->next;
			list->head->prev = NULL;
			FreeNode(list->free_function, curr);
			list->count--;
		}
		return;
	}

	/* O(1) */
	RemoveElement(list->free_function, curr);
}

/* TC: O(N) */
void* LL_PeekAt(LList list, int i) {
	if (list->count < i) {
		return NULL;
	}

	/* O(N) */
	Node node = list->head;
	while (i-- != 0) {
		node = node->next;
	}

	return node->content;
}

/* TC: O(1) */
int LL_Size(LList list) {
	return list->count;
}

/* TC: O(N) */
void LL_CallForAll(LList list, ListCall lc) {
	Node node = list->head;
	while (node != NULL) {
		lc(node->content);
		node = node->next;
	}
}

/* TC: O(N) */
void LL_CallForAllBackwards(LList list, ListCall lc) {
	Node node = list->head;
	Node prev = node;
	while(node != NULL) {
		prev = node;
		node = node->next;
	}

	node = prev;
	while(node != NULL) {
		lc(node->content);
		node = node->prev;
	}
}

/* TC: O(N) */
void* LL_CallForAt(LList list, ListCall lc, int i) {
	if (list->count <= i) {
		return NULL;
	}
	Node n = list->head;
	while (i-- != 0) {
		n = n->next;
	}

	return lc(n->content);
}

/* TC: O(N) */
int LL_ElementExists(LList list, void* ctx) {
	return LL_GetElement(list, ctx) != NULL;
}

/* TC: O(N) */
void* LL_GetElement(LList list, void* compare) {
	Node node = list->head;
	while (node != NULL) {
		if (list->compare_function(node->content, compare) == 0) {
			return node->content;
		}

		node = node->next;
	}

	return NULL;
}
