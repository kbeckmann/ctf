#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*fn)();

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char buf[256] = {0};

	printf("Enter code to execute.\n");
	fflush(stdout);

	fgets(buf, sizeof(buf), stdin);
	
	printf("Read [%d] bytes.\n", (int)strlen(buf));

	((fn)buf)();
	
	printf("Thanks.\n");	

	return 0;
}

