#ifndef EVALUATOR.H
#define EVALUATOR.H
#include <stdio.h>

// Structures
typedef struct {
    double *data;
    int top;
    int capacity;
} NumberStack;

typedef struct {
    char *operators;
    int top;
    int capacity;
} OpStack;

// Gestion pile de nombres
NumberStack* create_number_stack(int capacity);
void push_number(NumberStack *stack, double value);
double pop_number(NumberStack *stack);
int is_number_stack_empty(NumberStack *stack);
void free_number_stack(NumberStack *stack);

// Gestion pile d'opérateurs
OpStack* create_operator_stack(int capacity);
void push_operator(OpStack *stack, char op);
char pop_operator(OpStack *stack);
char top_operator(OpStack *stack);
int is_operator_stack_empty(OpStack *stack);
void free_operator_stack(OpStack *stack);

// Évaluation
double perform_operation(double a, double b, char op);
double evaluate_expression(const char *expression);

#endif
