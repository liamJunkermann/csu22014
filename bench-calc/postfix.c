#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs) {
    struct double_stack *numStack = double_stack_new(15);
    // printf("%d\n", args);
    for (int i = 0; i < nargs; i++) {
        // printf("%c ", *args[i]);
        // signed char val = *args[i];
        double numVal = atof(args[i]);
        // printf("%s ", (numVal==0) ? "true" : "false");
        if (*args[i] == '+' && numVal==0) {
            // printf("add\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 + val2);
        } else if (*args[i] == '-' && numVal==0) {
            // printf("sub\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 - val2);
        } else if (*args[i] == 'X' && numVal==0) {
            // printf("mul\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 * val2);
        } else if (*args[i] == '/' && numVal==0) {
            // printf("div\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 / val2);
        } else if (*args[i] == '^' && numVal==0) {
            // printf("exp\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, pow(val1, val2));
        } else {
            // printf("push ");
            double doubleVal = atof(args[i]);
            // printf("%f\n", doubleVal);
            double_stack_push(numStack, doubleVal);
        }
    }
    return double_stack_pop(numStack);
}
