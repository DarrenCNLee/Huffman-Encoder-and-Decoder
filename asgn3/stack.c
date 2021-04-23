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
    return !(s->items);
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return sizeof(s);
}

bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        s->top++;
        (s->items)[s->top] = x;
        return true;
    }
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top]; // code provided by Professor Long in assignment pdf
        //        free(s->top);
        s->top--;
        return true;
    }
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < sizeof(s); i++) {
        printf(" %" PRId64 "\n", s->items[i]);
    }
    return;
}

// main function code provided by Professor Long in assignment pdf
//int main(void) {
//    int64_t y;
//    int64_t *x = &y;
//    Stack *s = stack_create(80);
//    stack_push(s, 5);
//    stack_push(s, 4);
//    stack_push(s, 3);
//    stack_push(s, 2);
//    stack_push(s, 2);
//    stack_push(s, 2);
//   stack_push(s, 2);
//    stack_push(s, 2);
//    printf("empty?: %d\n", stack_empty(s));
//    printf("full?: %d\n", stack_full(s));
//  stack_print(s);
//    stack_pop(s, x);
//   stack_print(s);
//    stack_delete(&s);
//    assert(s == NULL);
//    return 0;
//}
