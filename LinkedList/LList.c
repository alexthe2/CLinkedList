#include "LList.h"
#include "Utils.h"

/* ------------------ Private (not accessible from outside) ------------------ */
Node CreateNode(void* content) {
	const Node node = (Node)SAFEMALLOC(sizeof(struct ListNode));

	node->content = content;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void FreeNode(FreeContent free_ctx,	Node node) {
	free_ctx(node->content);
	free(node);
}

Node AddNode(Node successor, Node node) {
	if (successor != NULL) {
		node->next = successor;
		successor->prev = node;
	}
	return node;
}

void RemoveElement(FreeContent free_ctx, Node node) {
	node->prev->next = node->next;
	if(node->next != NULL) {
		node->next->prev = node->prev;
	}

	FreeNode(free_ctx, node);
}

/* ------------------ Public (accessible from outside) ------------------ */
LList CreateList(Compare compare, FreeContent fc) {
	LList list = (LList) SAFEMALLOC(sizeof(struct List));

	list->compare_function = compare;
	list->free_function = fc;
	list->head = NULL;
	list->count = 0;
	return list;
}

void DestroyList(LList list) {
	Node curr = list->head;
	while(curr != NULL) {
		const Node next = curr->next;
		FreeNode(list->free_function, curr);
		curr = next;
	}
	free(list);
}

void AddItem(LList list, void* item) {
	const Node node = CreateNode(item);
	list->count++;
	
	list->head = AddNode(list->head, node);
}

void AddItemSorted(LList list, void* item) {
	Node node = CreateNode(item);
	list->count++;
	
	Node curr = list->head;
	if(curr == NULL || list->compare_function(curr, item) >= 0) {
		node->next = curr;
		if (curr != NULL) {
			curr->prev = node;
		}
		list->head = node;
		return;
	}
	
	while(curr->next != NULL && list->compare_function(curr->next, item) < 0) {
		curr = curr->next;
	}

	node = AddNode(curr->next, node);
	node->prev = curr;
	curr->next = node;
}

void RemoveItem(LList list, void* content) {
	Node curr = list->head;
	while (curr != NULL && list->compare_function(curr, content) != 0) {
		curr = curr->next;
	}

	if(list->head == curr) {
		if (curr != NULL) {
			list->head = curr->next;
			FreeNode(list->free_function, curr);
			list->count--;
		}
		return;
	}
	
	RemoveElement(list->free_function, curr);
}

void* PeekAt(LList list, int i) {
	if(list->count < i) {
		return NULL;
	}

	Node node = list->head;
	while(i-- != 0) {
		node = node->next;
	}

	return node->content;
}

int Size(LList list) {
	return list->count;
}

void CallForAll(LList list, ListCall lc) {
	Node node = list->head;
	while(node != NULL) {
		lc(node->content);
		node = node->next;
	}
}

void* CallForAt(LList list, ListCall lc, int i) {
	if(list->count <= i) {
		return NULL;
	}
	Node n = list->head;
	while(i-- != 0) {
		n = n->next;
	}

	return lc(n->content);
}

int ElementExists(LList list, void* ctx) {
	Node node = list->head;
	while(node != NULL) {
		if(list->compare_function(node->content, ctx)) {
			return 1;
		}

		node = node->next;
	}

	return 0;
}



