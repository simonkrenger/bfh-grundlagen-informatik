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
lnode* build123() {
	lnode *first;
	lnode *second;
	lnode *third;

	first = malloc(sizeof(lnode));
	second = malloc(sizeof(lnode));
	third = malloc(sizeof(lnode));

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
void printlist(lnode *head) {
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
void push(int data, lnode **list) {
	lnode *new_node = malloc(sizeof (lnode));
	new_node->data = data;
	new_node->next = *list;
	*list = new_node;
}

/**
 * Function to pop an element from a list
 */
int pop(lnode **list) {
	lnode *temp = *list;
	int ret = (*list)->data;
	*list = temp->next;
	free(temp);
	return ret;
}

/**
 *
 */
int main(void) {

	lnode *head;
	head = build123();

	printlist(head);

	printf("nodelen=%i\n", nodelen(head));
	printf("reclen=%i\n", reclen(head));

	lnode **list = &head;
	push(4, list);

	printlist(*list);

	push(5, list);
	push(6, list);

	printlist(*list);

	printf("pop()=%i\n", pop(list));

	printlist(*list);

	return EXIT_SUCCESS;
}
