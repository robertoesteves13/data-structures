#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;

Node* create_node(int value);

void list_append(LinkedList *list, int value) {
    if (!list->head) {
        Node* node = create_node(value);
        list->head = node;
        return;
    }

    Node* current = list->head;
    while (current->next) { 
        current = current->next;
    }

    current->next = create_node(value);
    return;
}

void list_print(LinkedList *list) {
    Node* current = list->head;

    printf("[");
    do {
        if (current->next) {
            printf("%d, ", current->value);
        } else {
            printf("%d]\n", current->value);
        }
        current = current->next;
    } while (current);
}

Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

LinkedList* create_list() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void list_destroy(LinkedList* list) {
    Node* current = list->head;

    while (current->next) {
        Node* previous = current;
        current = current->next;
        free(previous);
    }
    free(current);

    list->head = NULL;
    free(list);
}

void create_cycle(LinkedList* list) {
    Node* current = list->head;
    while (current->next) { 
        current = current->next;
    }

    current->next = list->head;
}

// Searches for a cycle in the list
// returns the node that's causing the cycle or NULL if there's no cycle
Node* detect_cycle(LinkedList* list) {
    Node* slow = list->head;
    Node* fast = list->head;
    Node* prev_fast = list->head;

    int isCycle = 0;
    while (slow->next) {
        slow = slow->next;
        fast = fast->next;
        prev_fast = fast;

        if (fast->next) {
            fast = fast->next;
        } else break;

        if (slow == fast) {
            return prev_fast;
        }
    }

    return NULL;
}


int main() {
    LinkedList* list = create_list();

    for (int i = 1; i <= 10; ++i) {
        list_append(list, i);
    }

    list_print(list);

    char input = 0;
    printf("Create cycle? (y/n) ");
    do {
        input = getchar();
    } while(input != 'y' && input != 'n');

    if (input == 'y') {
        create_cycle(list);
    }

    Node* cycled = detect_cycle(list);
    if (cycled) {
        printf("Linked list is cycled, fixing...\n");
        cycled->next = NULL;
    } else {
        printf("No cycle found in linked list\n");
    }

    list_destroy(list);
}
