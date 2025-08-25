#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}

int validate_expression(const char *expr) {
    int i = 0;
    int len = strlen(expr);
    int paren_count = 0;
    int last_was_operator = 0;
    int last_was_operand = 0;

    while (i < len && isspace(expr[i])) i++;

    if (is_operator(expr[i]) && expr[i] != '-') {
        return 0;
    }

    for (; i < len; i++) {
        char c = expr[i];

        if (isspace(c)) {
            continue;
        }
        else if (c == '(') {
            paren_count++;
            last_was_operator = 1;  
            last_was_operand = 0;
        }
        else if (c == ')') {
            paren_count--;
            if (paren_count < 0) return 0;
            last_was_operator = 0;
            last_was_operand = 1;
        }
        else if (is_operator(c)) {
            if (c == '=') {
                if (last_was_operator || i == 0) return 0; 
            }
            if (last_was_operator) {
                if (!(c == '-' && expr[i-1] == '(')) {
                    return 0;
                }
            }
            last_was_operator = 1;
            last_was_operand = 0;
        }
        else if (isalnum(c)) {
            last_was_operator = 0;
            last_was_operand = 1;
        }
        else {
            return 0;
        }
    }

    if (last_was_operator) return 0;

    if (paren_count != 0) return 0;

    return 1;
}

int main() {
    char expr[256];

    printf("Enter expression: ");
    fgets(expr, sizeof(expr), stdin);

    expr[strcspn(expr, "\n")] = 0;

    if (validate_expression(expr)) {
        printf("Expression is valid.\n");
    } else {
        printf("Expression is invalid.\n");
    }

    return 0;
}

