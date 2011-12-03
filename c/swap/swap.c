#include <stdio.h>
 
void swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void modify_string(char str) {
	str = 'X';
}
 
int main()
{
	int x = 2, y = 5;
	printf("Variable x: %i, Variable y: %i\n", x, y);
	swap(&x, &y);
	printf("Variable x: %i, Variable y: %i\n", x, y);

	char mystring = 'S';
	printf("So my string is: %c", mystring);
	modify_string(mystring);
	printf("So now my string is: %c", mystring);
	return 0;
}
