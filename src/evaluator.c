//récupère les token et évalue les prioritées
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.c"
#include "main.c"

typedef enum { TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_END, TOKEN_ERROR } TokenType;
typedef struct { TokenType type; double value; char operator; char par; } Token;
extern Token get_next_token(const char **expression);

//evaluer l'expression 
typedef struct{ //last in first out 
    double *data; //élément dans lequel nos items sont rangés
    int capacity; //taille maximale de la stack
    int top; //dernier élément de la pile, premier élément à être dépilé 
}NumberStack;

typedef struct{
    char *operators;
    int capacity;
    int top;
}OpStack;

//création des piles
NumberStack* create_number_stack(int capacity){
    NumberStack* pile_nb=malloc(sizeof(NumberStack)); //variable pile de type NumberStack
    pile_nb->data=malloc(capacity*sizeof(double));
    if (pile_nb == NULL) {  // Vérification d'erreur
        printf("Erreur : malloc a échoué !\n");
        return NULL;
    }
    pile_nb->top = -1;      // Initialisation du sommet
    pile_nb->capacity=capacity;
    printf("Stack créée à l'adresse %p\n", (void*)pile_nb);
    return pile_nb;
}

OpStack* create_operator_stack(int capacity){
    OpStack* pile_op=malloc(sizeof(OpStack));
    pile_op->operators=malloc(capacity*sizeof(char));
    if (pile_op == NULL) {  // Vérification d'erreur
        printf("Erreur : malloc a échoué !\n");
        return NULL;
    }
    pile_op->top = -1;      // Initialisation
    pile_op->capacity=capacity;
    printf("Stack créée à l'adresse %p\n", (void*)pile_op);
    return pile_op;
}


//fonctions sous-jacentes aux piles (push, pop, is_empty, is_full)
void is_full(NumberStack* pile_nb, OpStack* pile_op) {
    if (pile_nb->top== pile_nb->capacity-1){
        printf("la pile de nombre est pleine\n");
    }
    if (pile_op->top==pile_op->capacity-1){
        printf("la pile d'opérateurs est pleine\n");
    }
}

void is_empty(NumberStack* pile_nb, OpStack* pile_op){
    if (pile_nb->top==-1){
        printf("la pile de nombre est vide\n");
    }
    if (pile_op->top==-1){
        printf("la pile d'opérateur est vide\n");
    }
}

void push_number (NumberStack* pile_nb,double value){
    pile_nb->top++;
    pile_nb->data[pile_nb->top]=value;
}

void push_operator (OpStack* pile_op, char operator){
    pile_op->top++;
     pile_op->operators[pile_op->top]=operator;
}

double pop_number (NumberStack* pile_nb){
   return pile_nb->data[pile_nb->top--]; 
}

char pop_operator (OpStack* pile_op){
    return pile_op->operators[pile_op->top--];
}

//fonctions de test individuelles, pour la fonction principale evaluator
int is_number_stack_empty(NumberStack *stack) {
    return stack->top == -1;
}

int is_operator_stack_empty(OpStack *stack) {
    return stack->top == -1;
}


