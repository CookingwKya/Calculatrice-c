#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_END, TOKEN_ERROR } TokenType;
typedef struct { TokenType type; double value; char operator; char par; } Token;
extern Token get_next_token(const char **expression);

int main() {
    char input[256];
    printf("Calculatrice Simple\n");
    printf("Tapez 'quit' pour quitter\n\n");
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        if (strcmp(input, "quit\n") == 0) break;
        
        input[strcspn(input, "\n")] = '\0';
        printf("Analyse de: \"%s\"\n", input);
        const char *ptr = input;
        
        while (1) {
            Token token = get_next_token(&ptr);

           if (token.type == TOKEN_NUMBER) {
                printf("  NOMBRE: %.1f\n", token.value);
            } else if (token.type == TOKEN_OPERATOR) {
                printf("  OPERATEUR: %c\n", token.operator);
            } else if (token.type == TOKEN_LPAREN) {        // ← Ajouter
                printf("  LPAREN: %c\n", token.par);
            } else if (token.type == TOKEN_RPAREN) {        // ← Ajouter
                printf("  RPAREN: %c\n", token.par);
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
