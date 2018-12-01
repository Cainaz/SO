#include <stdio.h>
#include <stdlib.h>

int vetor[40];

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void push(struct Node** head_ref, int new_data)
{

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;

    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    (*head_ref) = new_node;
}
void insertAfter(struct Node* prev_node, int new_data)
{

    if (prev_node == NULL) {
        printf("O nó previamente dado não pode ser NULL");
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;

    new_node->next = prev_node->next;

    prev_node->next = new_node;

    new_node->prev = prev_node;


    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

void append(struct Node** head_ref, int new_data)
{

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref;

    new_node->data = new_data;

    new_node->next = NULL;

    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;

    new_node->prev = last;

    return;
}

void re_move(struct Node* node)
{
    struct Node* trash;
    trash = node->next;
    node->next = trash->next;
    free(trash);
}

void printList(struct Node* node)
{
    printf("\nPrintando Lista \n");
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main()
{
    struct Node* head = NULL;

    append(&head, 4);

    push(&head, 23);

    push(&head, 2);

    append(&head, 1);

    append(&head, 200);
    insertAfter(head->next, 100);

    printf("Lista duplamente encadeada: ");
    printList(head);
    re_move(head->next);
    re_move(head);
    printList(head);

    getchar();
    return 0;
}
