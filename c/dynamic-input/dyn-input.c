#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 255

struct haus {
	char *str;
	int number;
};

struct node {
	struct haus *data;
	struct node *next;
};

int main(void) {

	char strbuf[BUF_LEN];

	printf("Bitte Strassennamen eingeben: ");
	scanf("%s", strbuf);

	struct haus myhaus;

	myhaus.str = malloc(strlen(strbuf) * sizeof(char));
	strcpy(myhaus.str, strbuf);

	printf("Bitte Strassennummer eingeben: ");
	scanf("%i", &myhaus.number);

	printf("Adresse: %s %i\n\n", myhaus.str, myhaus.number);

	return EXIT_SUCCESS;
}
