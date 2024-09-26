#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return precedence of operators
int prec(char c) {
	if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// Function to return associativity of operators
char associativity(char c) {
	if (c == '^')
		return 'R';
	return 'L'; // Default to left-associative
}

// Structure to represent stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to initialize a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element to the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Full\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return '$'; // Assuming '$' as an invalid character
    }
    return stack->array[stack->top--];
}

// The main function to convert infix expression
// to postfix expression
void infixToPostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    char result[strlen(exp)];
    int resultIndex = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        // If the scanned character is
        // an operand, add it to the output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result[resultIndex++] = c;

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (c == '(')
            push(stack, '(');

        // If the scanned character is an ‘)’,
        // pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (stack->top != -1 && stack->array[stack->top] != '(') {
                result[resultIndex++] = pop(stack);
            }
            pop(stack); // Pop '('
        }

        // If an operator is scanned
        else {
            while (!isEmpty(stack) && prec(exp[i]) < prec(stack->array[stack->top]) ||
                !isEmpty(stack) && prec(exp[i]) == prec(stack->array[stack->top]) &&
                associativity(exp[i]) == 'L') {
                result[resultIndex++] = pop(stack);
            }
            push(stack, c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!isEmpty(stack)) {
        result[resultIndex++] = pop(stack);
    }

    result[resultIndex] = '\0'; // Null-terminate the result string

    printf("%s\n", result);
}

// Driver code
int main() {
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
    // Function call
    infixToPostfix(exp);
    return 0;
}
