#include <stdio.h>
 
void swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
 
int main()
{
	int x = 2, y = 5;
	printf("Variable x: %i, Variable y: %i\n", x, y);
	swap(&x, &y);
	printf("Variable x: %i, Variable y: %i\n", x, y);

	return 0;
}
