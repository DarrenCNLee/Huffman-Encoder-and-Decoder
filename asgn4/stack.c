// Darren Lee
// CSE13S Spring 2021
// This program implements the stack ADT and its functions.

#include "stack.h"

#include <inttypes.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0; // initialize the top
        s->capacity = capacity; // initialize the capacity
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items); // free the stack's items
        free(*s); // free the stack
        *s = NULL; // set the pointer to null
    }
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) { // return false if the stack is full
        return false;
    }
    (s->items)[s->top] = x; // set value at the top of the stack to x
    s->top++; // increment top of stack
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) { // return false if the stack is empty
        return false;
    }
    //    stack_pop(s, x);
    //    stack_push(s, *x);
    *x = s->items[s->top - 1]; // pass last added item to x
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) { // return false if the stack is empty
        return false;
    }
    s->top--; // decrement top
    *x = s->items[s->top]; // pass item at top to x
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    if (dst) {
        for (uint32_t i = 0; i < stack_size(src); i++) {
            dst->items[i] = src->items[i]; // copy the stack items
        }
        dst->top = src->top; // copy the top of the stack
    }
}

// code provided by Professor Long in assignment pdf
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
