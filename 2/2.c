#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

typedef int (*func)(int a, int b);

int add(int a, int b) {return a + b;}
int subtract(int a, int b) {return a - b;}
int multiply(int a, int b) {return a * b;}
int divide(int a, int b) {return b ? a / b : 0;}

func funcs[] = {add, subtract, multiply, divide};
char buf[256];

void readIntegers(int *a, int *b)
{
	int ret = 0;
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d %d", a, b);
}

int main(int argc, char **argv)
{
	int method;
	int a;
	int b;
	int result;

//	if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) exit(1);

	printf("What would you like to do?\n"
		"1. Add two numbers\n"
		"2. Subtract two numbers\n"
		"3. Multiply two numbers\n"
		"4. Divide two numbers\n");

	readIntegers(&method, &a);

	printf("You chose: %d\n", method);
	printf("Enter two numbers to do math with, e.g. [3 4]\n");

	fflush(stdout);

	readIntegers(&a, &b);
	func call = funcs[method - 1];

	result = call(a, b);
	printf("Result: %d\n", result);	
	fflush(stdout);

	return 0;
}

