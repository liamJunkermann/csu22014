#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs) {
    struct double_stack *numStack = double_stack_new(15);
    // printf("%d\n", args);
    for (int i = 0; i < nargs; i++) {
        printf("%f ", *args[i]);

        if (*args[i] == '+') {
            printf("add\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 + val2);
        } else if (*args[i] == '-') {
            printf("sub\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 - val2);
        } else if (*args[i] == 'X') {
            printf("mul\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 * val2);
        } else if (*args[i] == '/') {
            printf("div\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, val1 / val2);
        } else if (*args[i] == '^') {
            printf("exp\n");
            double val1 = double_stack_pop(numStack);
            double val2 = double_stack_pop(numStack);
            double_stack_push(numStack, pow(val1, val2));
        } else {
            printf("push\n");
            double val = atof(args[i]);
            double_stack_push(numStack, val);
        }
    }
    return double_stack_pop(numStack);
}
