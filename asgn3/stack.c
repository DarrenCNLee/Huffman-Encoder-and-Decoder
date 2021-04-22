#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// struct definition code provided by Professor Long in assignment pdf
struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
}

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

bool stack_empty(Stack *s){
	return !(s->items);
}

bool stack_full(Stack *s){
	return sizeof(s->items)/sizeof(int64_t)==s->capacity;
}

uint32_t stack_size(Stack *s){
	return sizeof(s->items)/int64_t;
}

bool stack_push(Stack *s, int 64_t x){
	if (stack_full()){i
		return false;
	}else{
		s->top++;
		(s->items)[s->top]=x;
		return true;
	}
}

bool stack_pop(Stack *s,int64_t *x){
	if (stack_empty()){
		return false;
	}else{
		*x->(s->items)[s->top]; // code provided by Professor Long in assignment pdf
		s->top--;
		return true;
	}
}

void stack_print(Stack *s){
	for (i=0;i<sizeof(s->items)/sizeof(int64_t);i++){
		printf("%" PRId64,s->items[i]);
	}
	return
}

// main function code provided by Professor Long in assignment pdf
int main (void){
	Stack *s = stack_create();
	stack_delete(&s);
	assert(s==NULL);
	return 0;
}
