// Exercise 3.
// Doubly-circular linked list.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct node {
    int value;
    struct node *next;      // Pointer to next node
    struct node *previous;  // Pointer to previous node
} node_t;

typedef struct dcl_list {
    node_t *first_element;
    int size;
} dcl_list_t;

void add();
void print_list();
void delete_node();

// Adds a new node to the end of the doubly-circular linked list.
void add(dcl_list_t *list, int value) {

    node_t *first_element = list->first_element;

    if (first_element == NULL) {
        // If the list is empty, a new node is created. Both the next and the previous pointers point to this node, since it's the only element on the list.
        node_t *new_node = malloc(sizeof(node_t));
        new_node->value = value;
        new_node->next = new_node->previous = new_node;

        list->first_element = new_node;
        list->size++;
    }
    else {
        // If the list is not empty.

        // Gets the last node currently on the list, which is a node that is previous to the first node.
        node_t *last = first_element->previous;

        // Prepares new node for use.
        node_t* new_node = malloc(sizeof(node_t));
        new_node->value = value;
        new_node->next = first_element;   // Next will point out to the first node on the list.
        new_node->previous = last;        // Previous will point to the last node currently on the list.

        // Previous pointer of the first_element will reference our new node.
        list->first_element->previous = new_node;
        // Next pointer of the last node currently on the list will point to the newly-added node.
        last->next = new_node;
        list->size++;
    }
}

// Displays the contents of the list.
void print_list(dcl_list_t *list) {
    node_t *temp_node = list->first_element;

    while (temp_node->next != list->first_element) {
        printf("%d  ", temp_node->value);
        temp_node = temp_node->next;
    }
    printf("%d  \n", temp_node->value);
}

// Deletes a node from the doubly-linked circular list.
void delete_node(dcl_list_t *list, int node_index) {

    int current_index;

    // Checks if the node_index fits in the list's dimensions.
    if (node_index >= list->size) {
        printf("error: node_index out of list's bounds.");
        return;
    }

    if (node_index == 0) {
        // If the first element is to be removed.
        node_t *temp_node = list->first_element;

        temp_node->previous->next = temp_node->next;  // Updates the references.
        temp_node->next->previous = temp_node->previous;
        list->first_element = temp_node->next;

        free(temp_node);
        list->size--;
        return;
    }

    if (node_index < (list->size)/2) {
        // Goes through the list in a normal order (clockwise).
        node_t *temp_node = list->first_element;
        current_index = 0;

        while (current_index != node_index) {
            current_index++;
            temp_node = temp_node->next;
        }

        temp_node->previous->next = temp_node->next;
        temp_node->next->previous = temp_node->previous;

        free(temp_node);
        list->size--;

    }
    else {
        // Goes through the list in a reverse order (counter-clockwise).
        node_t *temp_node = list->first_element->previous;
        current_index = list->size - 1;

        while (current_index != node_index) {
            current_index--;
            temp_node = temp_node->previous;
        }

        temp_node->previous->next = temp_node->next;
        temp_node->next->previous = temp_node->previous;

        free(temp_node);
        list->size--;
    }
}

int value_from_index(dcl_list_t *list, int node_index) {
    // Declares helper variables.
    node_t *curr = list->first_element;
    int current_index;

    if (node_index > list->size) {
        printf("error: invalid node_index.");
        return -1;
    }
    else if (node_index <= (list->size)/2) {
        // Iterates thorugh the list by going right.
        current_index = 0;

        while (current_index != node_index) {
            current_index++;
            curr = curr->next;
        }
    }
    else if (node_index > (list->size)/2) {
        // Iterates through the list by going left.
        current_index = list->size - 1;
        curr = list->first_element->previous;

        while(current_index != node_index) {
            current_index--;
            curr = curr->previous;
        }
    }
    return curr->value;
}

dcl_list_t *merge_lists(dcl_list_t *a, dcl_list_t *b){
    dcl_list_t *new = malloc(sizeof(dcl_list_t));
    new->first_element = NULL;
    new->size = 0;

    node_t *temp_node = a->first_element;
    int current_index = 0;

    while (current_index < a->size){
        add(new, temp_node->value);
        temp_node = temp_node->next;
        current_index++;
    }

    temp_node = b->first_element;
    current_index = 0;

    while (current_index < b->size){
        add(new, temp_node->value);
        temp_node = temp_node->next;
        current_index++;
    }
    return new;
}

int main(int argc, char const *argv[]) {
    // Creates an empty list for testing purpouses.
    dcl_list_t *list =  malloc(sizeof(struct dcl_list));
    list->first_element = NULL;
    list->size = 0;

    // Inserts some values to the list.
    for (int i = 1; i < 13; i++) {
        add(list, i);
    }

    // Displays the contents of the list.
    printf("--- Feature tests ---\n");
    print_list(list);

    // Performs tests of the deletion algorithm.
    delete_node(list, 1);
    delete_node(list, 3);
    delete_node(list, 5);
    print_list(list);

    printf("-> Current size of the list: %d.\n", list->size);
    printf("-> Value from node_index 3 is: %d.\n", value_from_index(list, 3));

    // Merge tests
    dcl_list_t *list2 =  malloc(sizeof(struct dcl_list));
    list2->first_element = NULL;
    list2->size = 0;

    for (int i = 0; i < 5; i++) {
        add(list2, arc4random_uniform(1000));
    }

    dcl_list_t *merged = merge_lists(list, list2);

    printf("-> Merging two lists together:\n");
    print_list(merged);

    // Average time calculations
    // Prepares a list consisting of 1000 elements
    dcl_list_t *time_test_list =  malloc(sizeof(struct dcl_list));
    time_test_list->first_element = NULL;
    time_test_list->size = 0;

    for (int i = 0; i < 1000; i++) {
        add(time_test_list, i);
    }

    // Calculates the average time it takes to access the element at the constant node_index.
    int selected, node_index = arc4random_uniform(1001);
    struct timeval tv1, tv2;

    gettimeofday(&tv1, NULL);

    for(int i = 0; i < 1000; i++) {
        selected = value_from_index(time_test_list, node_index);
    }

    gettimeofday(&tv2, NULL);

    printf ("--- Time tests ---\nSelecting the element with the node_index %d takes up %f30 seconds\n", node_index, (double) ((tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (tv2.tv_sec - tv1.tv_sec)) / 1000.0);

    // Calculates the average time it takes to access the element at the random node_index.
    selected = 0;

    gettimeofday(&tv1, NULL);

    for(int i = 0; i < 1000; i++) {
        selected = value_from_index(time_test_list, arc4random_uniform(1000));
    }

    gettimeofday(&tv2, NULL);

    printf ("Selecting the element with the random node_index takes up %f30 seconds\n", (double) ((tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (tv2.tv_sec - tv1.tv_sec)) / 1000.0);

    return 0;
}
