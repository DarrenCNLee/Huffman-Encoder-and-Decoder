#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern uint32_t max_stack_size;

// struct definition code provided by Professor Long in assignment pdf
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// stack destructor code provided by Professor Long in assignment pdf
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// stack destructor code provided by Professor Long in assignment pdf
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return !(s->top);
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        (s->items)[s->top] = x;
        s->top++;
        return true;
    }
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        s->top--;
        *x = s->items[s->top]; // code provided by Professor Long in assignment pdf
        return true;
    }
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i++) {
        printf("%" PRId64 " ", s->items[i]);
    }
    return;
}

// main function code provided by Professor Long in assignment pdf
//int main(void) {
//    int64_t y;
//    int64_t *x = &y;
//    printf("empty?: %d\n", stack_empty(s));
//    printf("full?: %d\n", stack_full(s));
//    printf("x: %" PRId64 "\n", *x);
//    stack_delete(&s);
//    assert(s == NULL);
//    return 0;
//}
