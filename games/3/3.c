#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

#ifdef DEBUG
#define dbg(...) printf(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define printflush(...) do{ printf(__VA_ARGS__); fflush(stdout); } while (0)

#define STACK_SIZE 32

enum token_type {
	OP_CODE,
	VALUE,
};

enum op_code {
	ADD = '+',	/* Pops two values, adds, pushed result */
	SUBTRACT = '-',	/* Pops two values, adds, pushes result */
	COPY_POP = 'm',	/* Pops one value and puts it in memory */
	PUSH_MEM = 'w',	/* Pushes memory variable */
	PRINT = 'p',	/* Prints value on top of stack */
	PRINT_POP = 'n',/* Pops one value, prints it */
	POP = '.',	/* Pops one value without reading it */
	EXIT = 'q',	/* Exits */
};

struct t_token {
	enum token_type type;
	union {
		enum op_code code;
		int value;
	} data;
};

char buf[1024]; /* make sure that we don't get a buffer overflow!! ;) */

void readToken(struct t_token *token)
{
	int ret = 0;
	fgets(buf, sizeof(buf), stdin);
	dbg("Read: [%s]\n", buf);
	ret = sscanf(buf, "%d", &token->data.value);
	if (ret != 1) {
		token->data.code = (enum op_code)buf[0];
		token->type = OP_CODE;
	} else {
		token->type = VALUE;
	}
}

int handle_op_code(int *stack, int *index, enum op_code code)
{
	switch (code) {
	case ADD:
		stack[(*index) - 1] += stack[*index];
		(*index)--;
		break;
	case SUBTRACT:
		stack[(*index) - 1] -= stack[*index];
		(*index)--;
		break;
	case COPY_POP:
		stack[1] = stack[*index];
		break;
	case PUSH_MEM:
		(*index)++;
		stack[*index] = stack[1];
		break;
	case PRINT:
		dbg("Value at %d: %d\n", *index, stack[*index]);
		printflush("Value: %d\n", stack[*index]);
		break;
	case PRINT_POP:
		dbg("Value at %d: %d\n", *index, stack[*index]);
		printflush("Value: %d\n", stack[*index]);
	case POP:
		(*index)--;
		break;
	case EXIT:
		return 1;
		break;
	}

	return 0;
}

void unicorns(int *stack)
{
	int magic = 1337;
	int *index = (int*)(stack);
	stack++;
	int *values = stack;

	(void) magic;

	*index = STACK_SIZE / 2;

	dbg("Location of index: %p\n", index);
	dbg("Location of values: %p\n", values);
	dbg("Location of buf: %p\n", buf);

	for (;;) {
		struct t_token token = {0};
		readToken(&token);
		dbg("index is: %d\n", *index);
		if (token.type == VALUE) {
			if (*index < STACK_SIZE && *index > 0) {
				(*index)++;
				values[*index] = token.data.value;
				dbg("Pushing %d at %d\n", token.data.value, *index);
			} else {
				printflush("Hold your horses, cowboy, the stack is protected! This incident will be logged!!\n");
			}
		} else {
			dbg("op_code: %d\n", token.data.code);
			if(handle_op_code(values, index, token.data.code)) {
				break;
			}
		}
	}
	dbg("Leaving unicorns\n");
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int ret = 31337;
	int safe_stack[STACK_SIZE] = {0};

	printflush("Welcome to PonyCalculator. It is similar to 'dc'.\n\n"
		"Enter a value or an operation followed by a newline.\n"
		"Supported operations:\n"
		"+: Pops two values, adds them and pushes the result\n"
		"-: Pops two values, subtracts the second popped with the first, pushes result\n"
		"m: Copies the value on top of the stack to a temporary memory\n"
		"w: Pushes the value from the temporary memory on top of the stack\n"
		"p: Prints the top of the stack\n"
		"n: Pops the the stack and prints the value\n"
		".: Pops the stack and ignores the value\n"
		"q: Exits\n\n");
	fflush(stdout);

	unicorns(safe_stack);

	return ret;
}

