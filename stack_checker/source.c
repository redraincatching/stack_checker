#include <stdio.h>

#define SIZE 50

enum command { push, pop, or , and, add, display };

int stack[SIZE];
int stack_ptr = 0;		// this is more of a pseudo-pointer tbh

void push();
void pop();
void or();
void and();
void add();
void subtract();
void display();

int main() {

	while (1) {
		// read user input
		// change to enum
		// switch case
		// perform
		// display stack
	}
}

void push() {
	int val;

	printf("enter a value: ");
	scanf_s("%d", &val);

	
}