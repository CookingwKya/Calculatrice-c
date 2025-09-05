#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"
// Déclaration de la fonction d'évaluation
double evaluate_expression(const char *expression);

int main() {
    char input[256];
    
    printf("=== Calculatrice en Ligne de Commande ===\n");
    printf("Opérateurs supportés: +, -, *, /, %%, ^\n");
    printf("Parenthèses supportées: ( )\n");
    printf("Tapez 'quit' pour quitter\n\n");
    
    while (1) {
        printf("> ");
        
        // Lecture sécurisée
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nFin de programme.\n");
            break;
        }
        
        // Vérifier si l'utilisateur veut quitter
        if (strcmp(input, "quit\n") == 0) {
            printf("Au revoir !\n");
            break;
        }
        
        // Supprimer le retour à la ligne
        input[strcspn(input, "\n")] = '\0';
        
        // Ignorer les lignes vides
        if (strlen(input) == 0) {
            continue;
        }
        
        // Supprimer les espaces avec la fonction utils
        remove_spaces(input);
        
        // Vérifier si l'expression est vide après suppression des espaces
        if (strlen(input) == 0) {
            printf("Expression vide\n\n");
            continue;
        }
        
        printf("Expression: %s\n", input);
        
        // Évaluer l'expression
        double resultat = evaluate_expression(input);
        
        
        // Afficher le résultat
        if (resultat == (int)resultat) {
            printf("Résultat: %.0f\n\n", resultat);
        } else {
            printf("Résultat: %.6g\n\n", resultat);
        }
    }
    
    return 0;
}