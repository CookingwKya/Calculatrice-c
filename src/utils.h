#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Déclarations des fonctions utilitaires
void remove_spaces(char *str);
int is_operator(char c);
int get_precedence(char op);
int is_left_associative(char op);

#endif