#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"

void remove_spaces(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int get_precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int is_left_associative(char op) {
    return (op != '^');  // Tous les opérateurs sauf ^ sont associatifs à gauche
}