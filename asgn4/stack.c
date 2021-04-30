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
        s->top = 0;
        s->capacity = capacity;
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
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
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

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    (s->items)[s->top] = x;
    s->top++;
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_pop(s, x)) {
        stack_push(s, *x);
        return true;
    }
    return false;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    if (dst) {
        dst->items = src->items;
        dst->top = src->top;
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

//int main(void) {
//    char *cities[] = { "march town", "june", "april", "disneyland" };
//   uint32_t x;
//    Stack *s = stack_create(5);
//    Stack *d = stack_create(5);
//    stack_push(s, 3);
//    stack_push(s, 1);
//    stack_push(s, 2);
//    stack_push(s, 0);
//    stack_push(s, 3);
//    stack_peek(s, &x);
//    printf("x=%" PRIu32 "\n", x);
//    stack_print(s, stdout, cities);
//    stack_copy(d, s);
//    stack_print(d, stdout, cities);
//    stack_print(s, stdout, cities);
//    return 0;
//}
