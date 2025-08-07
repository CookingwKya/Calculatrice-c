#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END,
    TOKEN_ERROR,
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char operator;
    char par;
} Token;

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Token get_next_token(const char **expression) {
    Token token;
    const char *expr = *expression;
   
    // Ignorer les espaces
    while (*expr == ' ') {
        expr++;
    }
   
    // Fin de chaîne
    if (*expr == '\0') {
        token.type = TOKEN_END;
        *expression = expr;
        return token;
    }
   
        //si il y a une parenthèse
    if (*expr == '(') {    // parenthèse gauche
        token.type = TOKEN_LPAREN;
        token.par = '(';   
        expr++;                     
        *expression = expr;         
        return token;              
    }

    if (*expr == ')') {             // parenthèse droite
        token.type = TOKEN_RPAREN;
        token.par = ')';            
        expr++;                      
        *expression = expr;         
        return token;                
    }

    // Nombre multi-chiffres
    if (isdigit(*expr)) {
        char number_str[64];
        int i = 0;
       
        // Lire tous les chiffres consécutifs
        while (isdigit(*expr)) {
            number_str[i++] = *expr++;
        }
       
        // Si il s'agit d'un nombre décimal
        if (*expr == '.') {
            number_str[i++] = '.';
            expr++;
            while (isdigit(*expr)) {
                number_str[i++] = *expr++;
            }
        }
        
        // Terminer la chaîne UNE SEULE FOIS
        number_str[i] = '\0';
        
        token.type = TOKEN_NUMBER;
        token.value = atof(number_str);
        *expression = expr;
        return token;
    }
    
    // Opérateur
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
