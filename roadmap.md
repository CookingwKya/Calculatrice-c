# Roadmap Calculatrice C - Guide par Fichiers

## 📁 Structure du Projet

```
calculatrice/
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── evaluator.c
│   └── utils.c
├── include/
│   ├── parser.h
│   ├── evaluator.h
│   └── utils.h
├── Makefile
└── README.md
```

---

## 📄 include/utils.h

### Consignes
Créez les déclarations pour les fonctions utilitaires de base.

### Fonctions à déclarer
```c
void remove_spaces(char *str);
int is_operator(char c);
int get_precedence(char op);
int is_left_associative(char op);
```

### Contenu requis
- Guards d'inclusion (`#ifndef`, `#define`, `#endif`)
- Inclusions nécessaires : `<stdio.h>`

---

## 📄 src/utils.c

### Consignes
Implémentez les fonctions utilitaires qui manipulent les chaînes et analysent les opérateurs.

### Fonctions à implémenter

#### `void remove_spaces(char *str)`
**Utilité :** Supprime tous les espaces d'une chaîne  
**Fonctions C à utiliser :**
- `isspace(char c)` : Vérifie si un caractère est un espace
- Manipulation directe des caractères avec indices

**Comment l'utiliser :**
```c
char expr[] = "2 + 3 * 4";
remove_spaces(expr);  // expr devient "2+3*4"
```

#### `int is_operator(char c)`
**Utilité :** Vérifie si un caractère est un opérateur valide  
**Logique :** Retourne 1 si c'est +, -, *, /, ^, %, sinon 0

#### `int get_precedence(char op)`
**Utilité :** Retourne la priorité d'un opérateur  
**Règles :**
- `+`, `-` : priorité 1
- `*`, `/`, `%` : priorité 2  
- `^` : priorité 3
- Autres : priorité 0

#### `int is_left_associative(char op)`
**Utilité :** Détermine l'associativité d'un opérateur  
**Règle :** Tous les opérateurs sont associatifs à gauche sauf `^`

---

## 📄 include/parser.h

### Consignes
Définissez les structures et fonctions pour l'analyse syntaxique.

### Structures à définir
```c
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char operator;
} Token;
```

### Fonction à déclarer
```c
Token get_next_token(const char **expression);
```

---

## 📄 src/parser.c

### Consignes
Implémentez l'analyseur lexical qui découpe l'expression en tokens.

### Fonction à implémenter

#### `Token get_next_token(const char **expression)`
**Utilité :** Extrait le prochain token d'une expression  
**Fonctions C à utiliser :**
- `isdigit(char c)` : Vérifie si c'est un chiffre
- `isspace(char c)` : Vérifie si c'est un espace
- `atof(const char *str)` : Convertit une chaîne en double

**Logique à implémenter :**
1. Ignorer les espaces avec une boucle `while`
2. Détecter la fin de chaîne (`'\0'`)
3. Reconnaître les nombres (chiffres et point décimal)
4. Reconnaître les parenthèses `(` et `)`
5. Reconnaître les opérateurs avec `is_operator()`
6. Mettre à jour le pointeur `*expression`

**Comment l'utiliser :**
```c
const char *expr = "2+3";
const char *ptr = expr;
Token token = get_next_token(&ptr);  // ptr avance automatiquement
```

---

## 📄 include/evaluator.h

### Consignes
Définissez les structures de piles et les fonctions d'évaluation.

### Structures à définir
```c
typedef struct {
    double *data;
    int top;
    int capacity;
} NumberStack;

typedef struct {
    char *data;
    int top;
    int capacity;
} OperatorStack;
```

### Fonctions à déclarer
```c
// Gestion pile de nombres
NumberStack* create_number_stack(int capacity);
void push_number(NumberStack *stack, double value);
double pop_number(NumberStack *stack);
int is_number_stack_empty(NumberStack *stack);
void free_number_stack(NumberStack *stack);

// Gestion pile d'opérateurs
OperatorStack* create_operator_stack(int capacity);
void push_operator(OperatorStack *stack, char op);
char pop_operator(OperatorStack *stack);
char top_operator(OperatorStack *stack);
int is_operator_stack_empty(OperatorStack *stack);
void free_operator_stack(OperatorStack *stack);

// Évaluation
double perform_operation(double a, double b, char op);
double evaluate_expression(const char *expression);
```

---

## 📄 src/evaluator.c

### Consignes
Implémentez toutes les fonctions de gestion des piles et l'algorithme d'évaluation.

### Fonctions à implémenter

#### Gestion de la pile de nombres

#### `NumberStack* create_number_stack(int capacity)`
**Utilité :** Crée une pile dynamique pour les nombres  
**Fonctions C à utiliser :**
- `malloc(size_t size)` : Alloue la mémoire
- Initialiser `top = -1` (pile vide)

#### `void push_number(NumberStack *stack, double value)`
**Utilité :** Ajoute un nombre sur la pile  
**Logique :** Incrémenter `top`, puis assigner la valeur

#### `double pop_number(NumberStack *stack)`
**Utilité :** Retire et retourne le nombre du sommet  
**Logique :** Récupérer la valeur, puis décrémenter `top`

#### `int is_number_stack_empty(NumberStack *stack)`
**Utilité :** Vérifie si la pile est vide  
**Logique :** Retourne 1 si `top < 0`

#### Gestion de la pile d'opérateurs
Même principe que pour les nombres, mais avec `char` au lieu de `double`.

#### `char top_operator(OperatorStack *stack)`
**Utilité :** Regarde l'opérateur du sommet sans le retirer  
**Logique :** Retourne `stack->data[stack->top]`

#### `double perform_operation(double a, double b, char op)`
**Utilité :** Effectue une opération mathématique  
**Fonctions C à utiliser :**
- `pow(double base, double exp)` : Pour l'exponentiation (^)
- `fmod(double x, double y)` : Pour le modulo (%)

**Logique :** Switch sur l'opérateur, gérer la division par zéro

#### `double evaluate_expression(const char *expression)`
**Utilité :** Fonction principale qui évalue une expression complète  
**Algorithme (Shunting Yard) :**

1. Créer deux piles (nombres et opérateurs)
2. Boucle sur tous les tokens :
   - **Nombre** : Empiler directement
   - **Opérateur** : Gérer les priorités avant d'empiler
   - **`(`** : Empiler directement
   - **`)`** : Dépiler jusqu'à trouver `(`
3. Vider la pile d'opérateurs restants
4. Le résultat final est le seul nombre restant

**Gestion des priorités :**
```c
while (!is_operator_stack_empty(operators) &&
       top_operator(operators) != '(' &&
       (get_precedence(top_operator(operators)) > get_precedence(token.operator) ||
        (get_precedence(top_operator(operators)) == get_precedence(token.operator) &&
         is_left_associative(token.operator)))) {
    // Dépiler et calculer
}
```

---

## 📄 src/main.c

### Consignes
Créez l'interface utilisateur et l'intégration de tous les modules.

### Fonctions C à utiliser
- `fgets(char *str, int size, FILE *stream)` : Lecture sécurisée
- `strcmp(const char *s1, const char *s2)` : Comparaison de chaînes
- `printf(const char *format, ...)` : Affichage

### Structure du main
1. Déclaration du buffer d'entrée : `char input[256]`
2. Messages d'accueil
3. Boucle infinie `while(1)` avec :
   - Affichage du prompt `"> "`
   - Lecture avec `fgets`
   - Vérification de fin (`fgets` retourne `NULL`)
   - Test de sortie (`strcmp(input, "quit\n") == 0`)
   - Nettoyage de l'entrée avec `remove_spaces`
   - Appel à `evaluate_expression`
   - Affichage du résultat

### Gestion d'erreurs
Vérifier que `fgets` ne retourne pas `NULL` avant de traiter l'entrée.

---

## 📄 Makefile

### Consignes
Automatisez la compilation avec les règles suivantes.

### Contenu requis
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lm
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = calculatrice

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
```

### Explications
- `LDFLAGS = -lm` : Lie la bibliothèque mathématique pour `pow()` et `fmod()`
- `CFLAGS` : Options de compilation avec warnings et répertoire d'inclusion
- Règles automatiques pour compiler tous les `.c` en `.o`

---

## 🧪 Tests à Effectuer

### Tests simples
```
2 + 3        → 5
10 - 4       → 6
5 * 6        → 30
15 / 3       → 5
```

### Tests avec priorités
```
2 + 3 * 4    → 14
(2 + 3) * 4  → 20
2 ^ 3 ^ 2    → 512
```

### Tests d'erreurs
```
5 / 0        → Message d'erreur
2 + + 3      → Erreur de syntaxe
(2 + 3       → Parenthèses non équilibrées
```

---

## 📋 Ordre de Développement Recommandé

1. **utils.h** et **utils.c** → Testez chaque fonction individuellement
2. **parser.h** et **parser.c** → Testez la tokenisation
3. **evaluator.h** → Définissez les structures
4. **evaluator.c** → Implémentez les piles puis l'évaluation
5. **main.c** → Intégrez tout
6. **Makefile** → Automatisez la compilation

### Conseils de débogage
- Utilisez `printf` pour afficher les tokens et l'état des piles
- Testez chaque fonction séparément avant l'intégration
- Commencez par des expressions très simples : `"2"`