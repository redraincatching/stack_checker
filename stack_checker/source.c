#include <stdio.h>
#include <string.h>
#include <limits.h>		// to use INT_MIN as an error code

#define SIZE 50

typedef enum { 
	DEFAULT,
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

typedef struct {
	int stack[SIZE];
	int ptr;		// this is more of a pseudo-pointer tbh
} Stack;

void init_stack(Stack *s);
void push(Stack *s);
int pop(Stack *s);
void or(Stack *s);
void and(Stack *s);
void add(Stack *s);
void subtract(Stack *s);
void display(Stack *s);
cmd input_to_enum(const char *str);

int main() {
	int running = 1;
	char input[10] = { 0 };
	cmd inp;
	int push_val;

	Stack stack;
	init_stack(&stack);

	while (running) {
		// read user input
		printf("enter a command: ");
		scanf_s("%s", input, sizeof(input));

		inp = input_to_enum(input);

		switch (inp) {
			case PUSH:
				printf("enter a value: ");
				scanf_s("%d", &push_val);
				push(&stack, push_val);
				display(&stack);
				break;
			case POP:
				pop(&stack);
				display(&stack);
				break;
			case OR:
				or(&stack);
				display(&stack);
				break;
			case AND:
				and(&stack);
				display(&stack);
				break;
			case ADD:
				add(&stack);
				display(&stack);
				break;
			case SUB:
				subtract(&stack);
				display(&stack);
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

void init_stack(Stack *s) {
	s->ptr = -1;
}

void push(Stack *s, int val) {
	if (s->ptr >= SIZE - 1) {
		printf("overflow, cannot execute\n");
	}
	else {
		s->ptr++;
		s->stack[(s->ptr)] = val;
	}	
}

int pop(Stack *s) {
	if (s->ptr < 0) {
		printf("underflow, cannot execute\n");
		return INT_MIN;
	}
	else if (s->ptr >= SIZE - 1) {
		printf("error: stack is full\n");
		return INT_MIN;
	}
	else {
		int temp = s->stack[s->ptr];
		s->ptr--;
		return temp;
	}
}

void or(Stack *s) {
	if (s->ptr < 1) {
		printf("not enough operands in the stack to execute this\n");
	}
	else {
		int x = pop(s);
		int y = pop(s);
		push(s, (x | y));
	}
}

void and(Stack *s) {
	if (s->ptr < 1) {
		printf("not enough operands in the stack to execute this\n");
	}
	else {
		int x = pop(s);
		int y = pop(s);
		push(s, (x & y));
	}
}

void add(Stack *s) {
	if (s->ptr < 1) {
		printf("not enough operands in the stack to execute this\n");
	}
	else {
		int x = pop(s);
		int y = pop(s);
		push(s, (x + y));
	}
}

void subtract(Stack *s) {
	if (s->ptr < 1) {
		printf("not enough operands in the stack to execute this\n");
	}
	else {
		int x = pop(s);
		int y = pop(s);
		push(s, (y - x));
	}
}

void display(Stack *s) {
	for (int i = s->ptr; i >= 0; i--) {
		printf("[%4s%d%5s\n", " ", s->stack[i], "]");
	}
}

cmd input_to_enum(const char *str) {
	int j;
	for (j = 0; j < sizeof(conversion) / sizeof(conversion[0]); ++j) {
		if (!strcmp(str, conversion[j].str)) {
			return conversion[j].command;
		}
	}

	return DEFAULT;
}