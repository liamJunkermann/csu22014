#include "stack.h"

struct double_stack * double_stack_new(int max_size) {
    struct double_stack * result;

    // Allocate space for stack header
    result = malloc(sizeof(struct double_stack));
    result -> max_size = max_size;
    result -> top = 0;

    // allocate space for data stored in the stack
    result -> items = malloc(sizeof(double)*max_size);
    
    // return pointer of stack
    return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
    if (this-> top == this->max_size-1) return; // check if stack is full. If it is return null;
    this->items[++this->top] = value; // if stack not full add value at next location and increment top
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
    if(this->top != 0) { // if stack not empty
        return this->items[this->top--];
    } // add condition if stack empty?
    else {
        return __INT_MAX__; // if stack empty return error code
    }

}