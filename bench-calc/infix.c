#include "infix.h"

int symbolType(char *symbol);

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs) {
    struct double_stack *stack = double_stack_new(25);
    char **expression = malloc(sizeof(char *) * nargs);
    int expressionIdx = 0;
    printf("Infix\n");
    for (int i = 0; i < nargs; i++) {
        printf("%c ", *args[i]);
        // double numVal = atof(args[i]);
        int symbol = symbolType(args[i]);
        switch (symbol) {
        case 0: // Is number
            expression[expressionIdx] = args[i];
            expressionIdx++;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:                    // Case for all operators
            if (stack->top != 0) { // If stack not empty
                char *firstOut = args[(int)(stack->items[stack->top - 1])];
                int newSym = symbol;
                int oldSym = symbolType(firstOut);
                while (oldSym >= newSym && stack->top != 0 && oldSym < 6) {
                    expression[expressionIdx] = firstOut;
                    printf("Added expression %s", firstOut);
                    double_stack_pop(stack);
                    expressionIdx++;
                    firstOut = args[(int)(stack->items[stack->top - 1])];
                    oldSym = symbolType(firstOut);
                }
            }
            double_stack_push(stack, i);
            break;
        case 6:
            double_stack_push(stack, i); // Always push "(" to stack
            break;
        case 7:
            while (strcmp(args[(int)(stack->items[stack->top - 1])], "(") != 0) {
                double expIndex = double_stack_pop(stack);
                expression[expressionIdx] = args[(int)expIndex];
                expressionIdx++;
            }
            double_stack_pop(stack);
            break;
        default:
            break;
        }
    }
    while(stack->top != 0) { // add remaining expressions to expression
        double expIndex = double_stack_pop(stack);
        expression[expressionIdx] = args[(int)expIndex];
        expressionIdx++;
    }
    return evaluate_postfix_expression(expression, expressionIdx);
}

int symbolType(char *symbol) {
    if (strcmp(symbol, "+") == 0) {
        return 1;
    } else if (strcmp(symbol, "-") == 0) {
        return 2;
    } else if (strcmp(symbol, "X") == 0) {
        return 3;
    } else if (strcmp(symbol, "/") == 0) {
        return 4;
    } else if (strcmp(symbol, "^") == 0) {
        return 5;
    } else if (strcmp(symbol, "(") == 0) {
        return 6;
    } else if (strcmp(symbol, ")") == 0) {
        return 7;
    } else {
        return 0;
    }
}