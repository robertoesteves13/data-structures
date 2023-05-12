#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Stack {
    Node* head;
} Stack;

Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Stack* create_stack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

void stack_push(Stack* stack, int value) {
    Node* node = create_node(value);

    if (!stack->head) {
        stack->head = node;
    } else {
        Node* old = stack->head;
        node->next = old;
        stack->head = node;
    }
}

Node* stack_pop(Stack* stack) {
    if (stack->head) {
        int value = stack->head->value;

        Node* old = stack->head;
        stack->head = stack->head->next;

        return old;
    } else return NULL;
}

void stack_print(Stack *stack) {
    Node* current = stack->head;

    do {
        printf("[%d]\n", current->value);
        current = current->next;
    } while (current);
}

void stack_destroy(Stack* stack) {
    Node* current = stack->head;

    while (current->next) {
        Node* previous = current;
        current = current->next;
        free(previous);
    }
    free(current);

    stack->head = NULL;
    free(stack);
}
int main() {
    Stack* stack = create_stack();

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    stack_print(stack);

    stack_destroy(stack);
}
