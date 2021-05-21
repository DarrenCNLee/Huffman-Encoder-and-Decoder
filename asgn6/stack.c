// Darren Lee
// CSE13S
// This program implements the stack ADT.

#include "stack.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// struct code provided by Professor Long in assignment pdf
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); // allocate memory for stack
    if (s) { // if memory allocation succeeds
        s->top = 0; // set top to 0
        s->capacity = capacity; // set capacity to capacity
        // allocate memory for items and initialize them to 0
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) { // if item memory allocation fails
            free(s); // free the stack
            s = NULL; // set the pointer to null
        }
    }
    return s; // return the stack
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) { // if the stack and stack items are not null
        free((*s)->items); // free the items
        free(*s); // free the stack
        *s = NULL; // set the pointer to null
    }
}
bool stack_empty(Stack *s) {
    return !s->top; // if top is 0, stack is empty
}

bool stack_full(Stack *s) { // if top equals capacity, stack is full
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false; // return false if the stack is full
    }
    s->items[s->top] = n; // set the item at top to n
    s->top++; // increment the top
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false; // if stack is empty, return false
    }
    s->top--; // decrement the top
    *n = s->items[s->top]; // set the node to the item at the top
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < stack_size(s); i++) {
        node_print(s->items[i]); // print each node in the stack
    }
}
