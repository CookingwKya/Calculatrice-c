#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Déclarations du parser (remplace #include "parser.h")
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END,
    TOKEN_ERROR,
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char operator;
} Token;

// Déclaration de la fonction du parser
Token get_next_token(const char **expression);

int main() {
    char input[256];
    printf("Calculatrice Simple\n");
    printf("Tapez 'quit' pour quitter\n\n");
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        if (strcmp(input, "quit\n") == 0) break;
        
        // Supprimer le \n ajouté par fgets
        input[strcspn(input, "\n")] = '\0';
        
        printf("Analyse de: \"%s\"\n", input);
        const char *ptr = input;
        
        // Boucle d'analyse des tokens
        while (1) {
            Token token = get_next_token(&ptr);
            
            if (token.type == TOKEN_NUMBER) {
                printf("  NOMBRE: %.0f\n", token.value);
            } else if (token.type == TOKEN_OPERATOR) {
                printf("  OPERATEUR: %c\n", token.operator);
            } else if (token.type == TOKEN_END) {
                printf("  FIN\n");
                break;
            } else {
                printf("  ERREUR\n");
                break;
            }
        }
        printf("\n");
    }
    
    return 0;
}