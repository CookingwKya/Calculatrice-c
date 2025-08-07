#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Pour isdigit


int main(){

}

typedef enum {
    TOKEN_NUMBER,    // si il s'agit d'un nombre
    TOKEN_OPERATOR,  // si il s'agit d'un opérateur
    TOKEN_END,       // il s'agit de la fin de l'expression
    TOKEN_ERROR,     // si il s'agit d'un caractère inconnu
} TokenType;

typedef struct {
    TokenType type;     // Le TYPE (qu'est-ce que c'est)
    double value;       // La VALEUR (si c'est un nombre)
    char operator;      // L'OPÉRATEUR (si c'est un opérateur)
} Token;

// Fonction utilitaire manquante
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Token get_next_token(const char **expression) {
    Token token;
    const char *expr = *expression;
   
    // Ignorer les espaces (CORRIGÉ)
    while (*expr == ' ') {
        expr++;
    }
    
    // Fin de chaîne (CORRIGÉ)
    if (*expr == '\0') {
        token.type = TOKEN_END;
        *expression = expr;
        return token;
    }
    
    // AJOUTÉ : Vérifier si c'est un nombre
    if (isdigit(*expr)) {
        token.type = TOKEN_NUMBER;
        token.value = *expr - '0';  // Conversion simple pour un chiffre
        expr++;
        *expression = expr;
        return token;
    }
    //si le caractère est un nombre et qu'il est précédé par un autre nombre ?
   if (isdigit(*expr)) {
    char number_str[64];     // Buffer pour accumuler les chiffres
    int i = 0;
    
    // Lire TOUS les chiffres consécutifs
    while (isdigit(*expr)) {
        number_str[i++] = *expr++;  // Copier le caractère ET avancer
    }
    number_str[i] = '\0';    // Terminer la chaîne
    
    token.type = TOKEN_NUMBER;
    token.value = atof(number_str);  // Convertir la chaîne complète
    *expression = expr;
    return token;
}

    // Vérifier si c'est un opérateur (CORRIGÉ)
    if (is_operator(*expr)) {
        token.type = TOKEN_OPERATOR;
        token.operator = *expr;
        expr++;
        *expression = expr;
        return token;
    }
    
    // Caractère non reconnu
    token.type = TOKEN_ERROR;
    *expression = expr;
    return token;  
}
