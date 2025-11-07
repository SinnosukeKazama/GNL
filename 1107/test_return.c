#include <stdio.h>

int f(int a)
{
	return (printf("%d", a), 1);
}

int main(void)
{
	printf("%d", f(10));
	return (0);
}
