#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "types.h"
#include "utils.h"

// Déclarations des fonctions de parser.c
Token get_next_token(const char **expression);

// Structures de piles
typedef struct {
    double *data;
    int capacity;
    int top;
} NumberStack;

typedef struct {
    char *operators;
    int capacity;
    int top;
} OpStack;

// Création des piles
NumberStack* create_number_stack(int capacity) {
    NumberStack* pile_nb = malloc(sizeof(NumberStack));
    if (pile_nb == NULL) {
        printf("Erreur : malloc a échoué !\n");
        return NULL;
    }
    pile_nb->data = malloc(capacity * sizeof(double));
    if (pile_nb->data == NULL) {
        printf("Erreur : malloc a échoué !\n");
        free(pile_nb);
        return NULL;
    }
    pile_nb->top = -1;
    pile_nb->capacity = capacity;
    return pile_nb;
}

OpStack* create_operator_stack(int capacity) {
    OpStack* pile_op = malloc(sizeof(OpStack));
    if (pile_op == NULL) {
        printf("Erreur : malloc a échoué !\n");
        return NULL;
    }
    pile_op->operators = malloc(capacity * sizeof(char));
    if (pile_op->operators == NULL) {
        printf("Erreur : malloc a échoué !\n");
        free(pile_op);
        return NULL;
    }
    pile_op->top = -1;
    pile_op->capacity = capacity;
    return pile_op;
}

// Fonctions de pile
void push_number(NumberStack* pile_nb, double value) {
    pile_nb->top++;
    pile_nb->data[pile_nb->top] = value;
}

void push_operator(OpStack* pile_op, char operator) {
    pile_op->top++;
    pile_op->operators[pile_op->top] = operator;
}

double pop_number(NumberStack* pile_nb) {
    return pile_nb->data[pile_nb->top--];
}

char pop_operator(OpStack* pile_op) {
    return pile_op->operators[pile_op->top--];
}

int is_number_stack_empty(NumberStack *pile_nb) {
    return pile_nb->top == -1;
}

int is_operator_stack_empty(OpStack *pile_op) {
    return pile_op->top == -1;
}

char top_operator(OpStack* pile_op) {
    if (pile_op->top != -1) {
        return pile_op->operators[pile_op->top];
    }
    return '\0';
}

void free_number_stack(NumberStack* pile_nb) {
    if (pile_nb) {
        free(pile_nb->data);
        free(pile_nb);
    }
}

void free_operator_stack(OpStack* pile_op) {
    if (pile_op) {
        free(pile_op->operators);
        free(pile_op);
    }
}

double perform_operation(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                printf("Erreur : division par zéro\n");
                return 0;
            }
            return a / b;
        case '%':
            if (b == 0) {
                printf("Erreur : modulo par zéro\n");
                return 0;
            }
            return fmod(a, b);
        case '^':
            return pow(a, b);
        default:
            printf("Opérateur non reconnu : %c\n", op);
            return 0;
    }
}

double evaluate_expression(const char *expression) {
    NumberStack* pile_nb = create_number_stack(50);
    OpStack* pile_op = create_operator_stack(50);
    
    if (!pile_nb || !pile_op) {
        printf("Erreur d'allocation mémoire\n");
        return 0;
    }

    Token token = get_next_token(&expression);

    while (token.type != TOKEN_END) {
        if (token.type == TOKEN_NUMBER) {
            push_number(pile_nb, token.value);
        }
        else if (token.type == TOKEN_OPERATOR) {
            while (!is_operator_stack_empty(pile_op) &&
                   top_operator(pile_op) != '(' &&
                   (get_precedence(top_operator(pile_op)) > get_precedence(token.operator) ||
                    (get_precedence(top_operator(pile_op)) == get_precedence(token.operator) &&
                     is_left_associative(token.operator)))) {
                double b = pop_number(pile_nb);
                double a = pop_number(pile_nb);
                char op = pop_operator(pile_op);
                double resultat = perform_operation(a, b, op);
                push_number(pile_nb, resultat);
            }
            push_operator(pile_op, token.operator);
        }
        else if (token.type == TOKEN_LPAREN) {
            push_operator(pile_op, '(');
        }
        else if (token.type == TOKEN_RPAREN) {
            while (top_operator(pile_op) != '(') {
                double b = pop_number(pile_nb);
                double a = pop_number(pile_nb);
                char op = pop_operator(pile_op);
                double resultat = perform_operation(a, b, op);
                push_number(pile_nb, resultat);
            }
            pop_operator(pile_op); // Supprimer '('
        }
        else if (token.type == TOKEN_ERROR) {
            printf("Erreur de syntaxe dans l'expression\n");
            free_number_stack(pile_nb);
            free_operator_stack(pile_op);
            return 0;
        }
        
        token = get_next_token(&expression);
    }

    // Vider la pile d'opérateurs restants
    while (!is_operator_stack_empty(pile_op)) {
        double b = pop_number(pile_nb);
        double a = pop_number(pile_nb);
        char op = pop_operator(pile_op);
        double resultat = perform_operation(a, b, op);
        push_number(pile_nb, resultat);
    }

    double result = pop_number(pile_nb);
    free_number_stack(pile_nb);
    free_operator_stack(pile_op);
    return result;
}