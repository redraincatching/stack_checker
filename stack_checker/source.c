#include <stdio.h>
#include <string.h>

#define SIZE 50

typedef enum { 
	EXIT,
	PUSH, 
	POP, 
	OR, 
	AND, 
	ADD,
	SUB
} cmd;

const static struct {
	cmd     command;
	const char* str;
} conversion[] = {
	{EXIT, "exit"},
	{PUSH, "push"},
	{POP, "pop"},
	{OR, "or"},
	{AND, "and"},
	{ADD, "add"},
	{SUB, "subtract"}
};

int stack[SIZE];
int stack_ptr = -1;		// this is more of a pseudo-pointer tbh
						// set to the current highest full index

void push();
void pop();
void or();
void and();
void add();
void subtract();
void display();
cmd input_to_enum(const char* str);

int main() {
	int running = 1;
	char input[10] = { 0 };
	cmd inp = EXIT;

	while (running) {
		// read user input
		printf("enter a command: ");
		scanf_s("%s", input, sizeof(input));

		inp = input_to_enum(input);

		switch (inp) {
			case PUSH:
				push();
				display();
				break;
			case POP:
				pop();
				display();
				break;
			case OR:
				or();
				display();
				break;
			case AND:
				and();
				display();
				break;
			case ADD:
				add();
				display();
				break;
			case SUB:
				subtract();
				display();
				break;
			case EXIT:
				running = 0;
				break;
			default:
				printf("please enter a valid command\n");
				break;
		}
	}
}

void push() {
	int val;

	if (stack_ptr == SIZE - 1) {
		printf("overflow, cannot execute\n");
		return;
	}
	else {
		printf("enter a value: ");
		scanf_s("%d", &val);

		stack[++stack_ptr] = val;
	}	
}

void pop() {
	if (stack_ptr < 0) {
		printf("underflow, cannot execute\n");
	}
	else {
		stack_ptr--;
	}
}

void or() {
	if (stack_ptr < 1) {
		printf("not enough operands in the stack to execute this");
	}
	else {
		stack[stack_ptr - 1] = (stack[stack_ptr - 1] | stack[stack_ptr]);
		stack_ptr--;
	}
}

void and() {
	if (stack_ptr < 1) {
		printf("not enough operands in the stack to execute this");
	}
	else {
		stack[stack_ptr - 1] = (stack[stack_ptr - 1] & stack[stack_ptr]);
		stack_ptr--;
	}
}

void add() {
	if (stack_ptr < 1) {
		printf("not enough operands in the stack to execute this");
	}
	else {
		stack[stack_ptr - 1] = (stack[stack_ptr - 1] + stack[stack_ptr]);
		stack_ptr--;
	}
}

void subtract() {
	if (stack_ptr < 1) {
		printf("not enough operands in the stack to execute this");
	}
	else {
		stack[stack_ptr - 1] = (stack[stack_ptr - 1] - stack[stack_ptr]);
		stack_ptr--;
	}
}

void display() {
	for (int i = stack_ptr; i >= 0; i--) {
		printf("[%4s%d%5s\n", " ", stack[i], "]");
	}
}

cmd input_to_enum(const char* str) {
	int j;
	for (j = 0; j < sizeof(conversion) / sizeof(conversion[0]); ++j) {
		if (!strcmp(str, conversion[j].str)) {
			return conversion[j].command;
		}
	}

	return EXIT;
}