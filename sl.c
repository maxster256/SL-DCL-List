// Exercise 2.
// Single-linked list.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*
ARC4RANDOM() DESCRIPTION
     The arc4random() function uses the key stream generator employed by the arc4 cipher, which uses 8*8 8
     bit S-Boxes.  The S-Boxes can be in about (2**1700) states.  The arc4random() function returns pseudo-random pseudorandom
     random numbers in the range of 0 to (2**32)-1, and therefore has twice the range of rand(3) and
     random(3).

     arc4random_buf() function fills the region buf of length nbytes with ARC4-derived random data.

     arc4random_uniform() will return a uniformly distributed random number less than upper_bound.
     arc4random_uniform() is recommended over constructions like ``arc4random() % upper_bound'' as it avoids
     "modulo bias" when the upper bound is not a power of two.
*/

// Defines a structure which holds the value of an element of the list and the reference to the next element on the list.
typedef struct node {
    int value;
    struct node *next;
} node_t;

// Prints out the entire list's contents to the stdout.
void print_list(node_t *first_element) {
    node_t *current_node = first_element;

    while (current_node != NULL) {
        printf("%d  ", current_node->value);
        current_node = current_node->next;
    }
    printf("\n");
}

// Adds the new element to the end of the list.
void add(node_t *first_element, int value) {
    node_t *current_node = first_element;

    // Goes through the queue until the last elements is found.
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    // Adds the reference to the new element and its' value to the queue.
    current_node->next = malloc(sizeof(node_t));
    current_node->next->value = value;
    current_node->next->next = NULL;
}

// Adds the new element to the beginning of the list.
void add_to_front(node_t **first_element, int value) {
    node_t *new_node;
    new_node = malloc(sizeof(node_t));

    new_node->value = value;
    new_node->next = *first_element;
    *first_element = new_node;
}

// Adds the new element to the list after a given node.
void add_after_element(node_t *previous_node, int new_data) {

    // Checks if the given node is NULL.
    if (previous_node == NULL) {
       printf("error: the given previous node cannot be NULL");
       return;
    }

    // Allocates the new node and initializes its' contents
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_data;
    new_node->next = previous_node->next;  // The new node will point to the next element in the queue.

    // Set the reference to the next element of the given node to our newly created node.
    previous_node->next = new_node;
}

// Returns the first element from the queue.
int pop(node_t **first_element) {       // **first_element, because we want to modify it inside a function.
    int return_value = -1;              // We pass the pointer to the first_element pointer, basically.
    node_t *next_node = NULL;

    // Checks if the queue is not empty.
    if (*first_element == NULL) {
        printf("error: fifo queue empty.\n");
        return -1;
    }

    // Gets the contents of the next element.
    next_node = (*first_element)->next;
    return_value = (*first_element)->value;

    free(*first_element);

    // Makes the next_node the first_element of the queue.
    *first_element = next_node;

    return return_value;
}

// Removes an element from the list with the index given.
int remove_by_index(node_t **first_element, int n) {
    int i = 0;
    int return_value = -1;

    node_t *current_node = *first_element;
    node_t *temp_node = NULL;

    // If it's the first element on the list, we can use the pop function.
    if (n == 0)
        return pop(first_element);

    // Iterates to the node before the one we wish to delete.
    for (i = 0; i < n-1; i++) {
        if (current_node->next == NULL) {
            return -1;
        }
        current_node = current_node->next;
    }

    // Saves the node to delete in a temporary pointer.
    temp_node = current_node->next;
    return_value = temp_node->value;

    // The previous pointer will point to the pointer the deleted one was referring to.
    current_node->next = temp_node->next;
    free(temp_node);

    return return_value;
}

// Returns a value by the index
int value_from_index(node_t **first_element, int n) {
    int return_value = -1;
    node_t *current_node = *first_element;

    for (int i = 0; i < n; i++) {
        if (current_node->next == NULL) {
            return -1;
        }
        current_node = current_node->next;
    }
    return_value = current_node->value;

    return return_value;
}

// Checks if the given value is held on the list.
int check_for_value(node_t **first_element, int n) {
    int return_value = -1;
    node_t *current_node = *first_element;

    // Checks the first_element for the value.
    if (current_node->value == n)
        return 1;

    // Goes through the queue until the last elements is found.
    while (current_node->next != NULL) {
        current_node = current_node->next;
        if (current_node->value == n)
            return 1;
    }
    return return_value;
}

// Counts the number of the elements on the list
int count_elements(node_t **first_element) {
    int count = 0;  // Initialize count
    node_t *current_node = *first_element;  // Initialize current_node

    while (current_node != NULL) {
        count++;
        current_node = current_node->next;
    }
    return count;
}

// Merges two separate single-linked lists together.
void merge(node_t **first_list, node_t **second_list) {
    node_t *current_node = *first_list;
    node_t *next_first = *second_list;

    // Goes through the first list until the last element is found.
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    // Adds the reference to the first element of the second list to the last element of the first list, resulting in two lists combining into one.
    current_node->next = next_first;
}

int main () {

    node_t *test_list = malloc(sizeof(node_t));
    test_list->value = 0;
    test_list->next = NULL;

    for (int i = 1; i <= 10; i++) {
        add(test_list, i);
    }

    printf("--- Default operations tests ---\n-> The contents of the list is as follows:\n");
    print_list(test_list);

    add_to_front(&test_list, 154);
    printf("-> Contents after the element was added to the front of the list:\n");
    print_list(test_list);

    node_t *node_to_add_after = test_list;

    for (int i = 0; i < 5; i++) {
        node_to_add_after = node_to_add_after->next;
    }

    add_after_element(node_to_add_after, 320);
    printf("-> Contents after the new element was added after the element with value %d:\n", node_to_add_after->value);
    print_list(test_list);

    remove_by_index(&test_list, 8);
    printf("-> Contents after the element with index 8 was deleted:\n");
    print_list(test_list);

    int value_from_5 = value_from_index(&test_list, 5);
    if (value_from_5 != -1)
        printf("-> Value held on index 5 is: %d\n", value_from_5);
    else
        printf("-> An incorrect index was provided.");

    int is_10_on_list = check_for_value(&test_list, 10);
    if (is_10_on_list == -1)
        printf("-> Value 10 was not found on the list.\n");
    else
        printf("-> Value 10 was found on the list.\n");

    // Merging two lists together
    node_t *second_test = malloc(sizeof(node_t));
    second_test->value = 100;
    second_test->next = NULL;

    for (int i = 100; i <= 110; i++) {
        add(second_test, i);
    }

    printf("--- List merging test ---\n-> The contents of the second list is as follows:\n");
    print_list(second_test);

    merge(&test_list, &second_test);
    printf("-> The contents of the merged lists:\n");
    print_list(test_list);

    // Average time calculations.
    // Prepares the list consisting of 1000 average elements.

    node_t *list = malloc(sizeof(node_t));
    list->value = arc4random_uniform(1000);
    list->next = NULL;

    for (int i = 1; i < 1000; i++) {
        add(list, arc4random_uniform(1001));
    }

    // Calculates the average time it takes to access the element at the constant index.
    int selected, index = arc4random_uniform(1000);
    struct timeval  tv1, tv2;

    gettimeofday(&tv1, NULL);

    for(int i = 0; i < 1000; i++) {
        selected = value_from_index(&list, index);
    }

    gettimeofday(&tv2, NULL);

    printf ("--- Time tests ---\nSelecting the element with the index %d takes up %f30 seconds\n", index, (double) ((tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (tv2.tv_sec - tv1.tv_sec)) / 1000.0);

    // Calculates the average time it takes to access the element at randomly selected index.
    selected = 0;

    gettimeofday(&tv1, NULL);

    for(int i = 0; i < 1000; i++) {
        int random_index = arc4random_uniform(1000);
        //printf("%d  ", value);

        selected = value_from_index(&list, random_index);
    }

    gettimeofday(&tv2, NULL);

    printf ("Selecting the element with the randomly selected index takes up %f30 seconds\n", (double) ((tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (tv2.tv_sec - tv1.tv_sec)) / 1000.0);

    return 0;
}
