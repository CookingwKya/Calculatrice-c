#define utils_h
void remove_spaces(char *str);
int is_operator(char c);
int get_precedence(char op);
int is_left_associative(char op);
