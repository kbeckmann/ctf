#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define printflush(...) do{ printf(__VA_ARGS__); fflush(stdout); } while (0)

typedef void (*fn)();

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char buf[256] = {0};

	printflush("Enter code to execute.\n");

	fgets(buf, sizeof(buf), stdin);

	printflush("Read [%d] bytes.\n", (int)strlen(buf));

	((fn)buf)();

	printflush("Thanks.\n");	

	return 0;
}
