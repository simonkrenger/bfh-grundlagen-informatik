/**
 *
 * lists.c
 *
 *  Created on: Jan 11, 2012
 *      Author: simon
 *
 *  Kommt an Prüfung
 *
 *	In Assembler hatten wir folgende Segmente eines Programmes:
 *	CODE: Program / Binary
 *	DATA: Globale Variablen (eg. <label> .byte 48)
 *	STACK: Lokale Variablen, Parameter, "CALL" / "JSR" Rücksprungadresse
 *	HEAP: Allozierbar [malloc(Grösse in Bytes), Retourniert Addresse des ersten Bytes]
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * List node
 */
typedef struct node {
	int data;
	struct node *next;
} lnode;

/**
 * Function to build a new list with some preset values
 */
lnode* init_list() {
	lnode *first = malloc(sizeof(lnode));
	lnode *second = malloc(sizeof(lnode));
	lnode *third = malloc(sizeof(lnode));

	first->data = 1;
	first->next = second;

	// Different syntax
	(*second).data = 2;
	(*second).next = third;

	third->data = 3;
	third->next = NULL;

	return first;
}

/**
 * Function to get the size of a list
 */
int nodelen(lnode* list) {
	int len = 0;
	lnode *cur = list;

	while (cur != NULL) {
		len++;
		cur = cur->next;
	}
	return len;
}

/**
 * Recursive function to calculate the size of a list.
 * Sweet!
 * Provided by Christian Meyer.
 */
int reclen(lnode* n) {
	return n ? 1 + reclen(n->next) : 0;
}

/**
 * Function to print a list
 * Provided by Olivier Buechel
 */
void printlist(lnode* head) {
	lnode *current = head;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

/**
 * Function to push a new element to a list
 */
void push(int data, lnode** list) {
	lnode *new_node = malloc(sizeof(lnode));
	new_node->data = data;
	new_node->next = *list;
	*list = new_node;
}

/**
 * Function to pop an element from a list
 */
int pop(lnode** list) {
	lnode *temp = *list;
	int ret = (*list)->data;
	*list = temp->next;
	free(temp);
	return ret;
}

/**
 * Return n-th element.
 * Returns -1 if the n-th element does not exist
 */
int get_nth(lnode** list, int n) {
	if (n >= nodelen(*list))
		return -1;
	lnode* p = *list;
	int i;
	for (i = 0; i < n; i++) {
		p = p->next;
	}
	return p->data;
}

/**
 * Delete list
 */
void delete_list(lnode** list) {
	lnode* cur = *list;

	while (cur != NULL) {
		lnode* temp = cur;
		free(cur);
		cur = temp->next;
	}

	*list = NULL;
}

/**
 * Insert element at n-th position (indexed).
 */
void insert_nth(lnode** listref, int ele, int n) {
	lnode* cur = *listref;
	lnode* last = cur;
	int i;
	for (i = 0; i < ele; i++) {
		last = cur;
		cur = cur->next;
	}

	lnode *new_node = malloc(sizeof(lnode));
	new_node->data = n;

	new_node->next = cur;
	last->next = new_node;
}

/**
 * Append list B to list A
 */
void append(lnode** listref_a, lnode** listref_b) {
	lnode *cur = *listref_a;

	// Skip to end
	while (cur->next != NULL) {
		cur = cur->next;
	}

	cur->next = *listref_b;
}

/**
 *
 */
int main(void) {

	lnode *head = init_list();

	printlist(head);

	printf("nodelen=%i\n", nodelen(head));
	printf("reclen=%i\n", reclen(head));

	lnode **list = &head;
	push(4, list);

	printlist(*list);

	push(5, list);
	push(6, list);

	printlist(*list);

	while (nodelen(head) > 3) {
		printf("pop()=%i\n", pop(list));
	}

	printlist(*list);

	printf("get_nth(index 2) = %i\n", get_nth(list, 2));

	printlist(*list);

	delete_list(list);

	printf("List should now be empty: ");
	printlist(*list);

	push(1, list);
	push(2, list);
	push(3, list);
	push(5, list);
	printf("List is now filled again: ");
	printlist(*list);

	insert_nth(list, 1, 4);
	printlist(*list);

	printf("Created a new list: ");
	lnode* listb = init_list();
	printlist(listb);

	append(list, &listb);
	printf("Appended the new list to the old list: ");
	printlist(*list);

	return EXIT_SUCCESS;
}
