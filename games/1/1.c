#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*func)();

int main(int argc, char **argv)
{
	char buf[256] = {0};

	printf("Enter code to execute.\n");
	fflush(stdout);

	fgets(buf, sizeof(buf), stdin);
	
	printf("Read [%d] bytes.\n", (int)strlen(buf));

	((func)(buf))();
	
	printf("Thanks.\n");	

	return 0;
}

