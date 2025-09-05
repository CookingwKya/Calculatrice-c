#ifndef TYPES_H
#define TYPES_H

typedef enum {
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char operator;
    char par;
} Token;

#endif