#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

#define printflush(...) do{ printf(__VA_ARGS__); fflush(stdout); } while (0)

typedef int (*func)(int a, int b);

static int add(int a, int b) {return a + b;}
static int subtract(int a, int b) {return a - b;}
static int multiply(int a, int b) {return a * b;}
static int divide(int a, int b) {return b ? a / b : 0;}

func funcs[] = {add, subtract, multiply, divide};
char buf[256];

static void read_integers(int *a, int *b)
{
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d %d", a, b);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int method;
	int a;
	int b;
	int result;

	printflush("What would you like to do?\n"
		"1. Add two numbers\n"
		"2. Subtract two numbers\n"
		"3. Multiply two numbers\n"
		"4. Divide two numbers\n");

	read_integers(&method, &a);

	printflush("You chose: %d\n"
		"Enter two numbers to do math with, e.g. [3 4]\n", method);

	read_integers(&a, &b);
	func call = funcs[method - 1];

	result = call(a, b);
	printflush("Result: %d\n", result);

	return 0;
}
