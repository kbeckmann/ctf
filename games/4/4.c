#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

#define printflush(...) do{ printf(__VA_ARGS__); fflush(stdout); } while (0)

typedef struct t_node t_node;
typedef void (*fn_cleanup)(struct t_node *node);

struct t_entry {
	char name[32];
	char phone_number[16];
};

struct t_node {
	fn_cleanup cleanup;
	struct t_node *next;
	struct t_entry entry;
};

struct t_node *head;
struct t_node *tail;
int entry_count;

char buf[256];

void read_integer(int *a)
{
	memset(buf, 0, sizeof(buf));
	if(!fgets(buf, sizeof(buf), stdin))
		exit(1);
	sscanf(buf, "%d\n", a);
}

int check_sanity(char c)
{
	return ((c != '\0') &&
		(c != '\x0a') &&
		(c != '\x0d')); 
}

char *read_checked_string()
{
	unsigned int i;
	unsigned int j;
	fgets(buf, sizeof(buf), stdin);
	for (i = 0; i < sizeof(buf); i++) {
		if (!check_sanity(buf[i])) {
			for (j = i; j < sizeof(buf); j++) {
				buf[j] = '\0';
			}
			break;
		}
	}
	return buf;
}

int print_menu()
{
	int ret = -1;
	printflush( "\n"
		"1. List entries\n"
		"2. Add entry\n"
		"3. Edit entry\n"
		"4. Remove entry\n"
		"0. Exit\n");
	read_integer(&ret);
	return ret;
}

void free_node(struct t_node *node)
{
	free(node);
}

void list_entries()
{
	struct t_node *node = head;
	int i = 1;

	while (node) {
		printflush("id: [%d]\nName: [%s]\nNumber: [%s]\n", i++, node->entry.name, node->entry.phone_number);
		node = node->next;
	}
}

void add_entry()
{
	struct t_node *node = malloc(sizeof(struct t_node));

	node->cleanup = free_node;

	printflush("Enter the name of the contact: ");
	read_checked_string();
	strcpy(node->entry.name, buf);
	printflush("Enter the phone number of the contact: ");
	read_checked_string();
	strcpy(node->entry.phone_number, buf);

	node->next = 0;
	entry_count++;

	if (entry_count == 1) {
		head = node;
	} else {
		tail->next = node;
	}
	tail = node;

	printflush("Successfully added new entry with id[%d].\n[%s]:[%s]\n", 
		entry_count, node->entry.name, node->entry.phone_number);
}

void edit_entry()
{
	struct t_node *node = head;
	int index = 0;
	int i = 0;

	printflush("Enter the index of the entry: ");
	read_integer(&index);
	while (node) {
		if (++i == index) {
			break;
		}
		node = node->next;
	}

	if (!node) {
		printflush("Couldn't find the entry.\n");
		return;
	}

	printflush("Enter the name of the contact: ");
	read_checked_string();
	strcpy(node->entry.name, buf);
	printflush("Enter the phone number of the contact: ");
	read_checked_string();
	strcpy(node->entry.phone_number, buf);

	printflush("New contact information stored.\n");
}

void clear_list()
{
	struct t_node *node = head;
	struct t_node *next;

	while (node) {
		next = node->next;
		node->cleanup(node);
		node = next;
	}

	head = tail = 0;
}

void remove_entry()
{
	int index = -1;

	printflush("Enter the id of the entry to remove: ");
	read_integer(&index);

	if (index > 0) {
		int i = 1;
		struct t_node *node = head;
		struct t_node *next;

		if (index == i && node) {
			head = node->next;
			if (tail == node) {
				tail = node->next;
			}
			node->cleanup(node);
			entry_count--;
			node = 0;
		}

		while (node) {
			next = node->next;
			if (++i == index && next) {
				if (tail == next) {
					tail = node;
					node->next = 0;
				} else {
					node->next = next->next;
				}
				next->cleanup(next);
				entry_count--;
				break;
			}
			node = next;
		}
	}
}

void menu()
{
	int c;
	while ((c = print_menu())) {
		switch (c) {
		case 1:
			list_entries();
			break;
		case 2:
			add_entry();
			break;
		case 3:
			edit_entry();
			break;
		case 4:
			remove_entry();
			break;
		case 0:
			return;
		default:
			printflush("Unrecognized command, please try again.\n");
			break;
		}
	}

	clear_list();
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	head = 0;
	tail = 0;
	entry_count = 0;

	menu();

	return 0;
}

