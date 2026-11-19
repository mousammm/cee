/*
 * [x] skip the preprocessor (handle multi line macro)
 * [x] skip whitespace ' \n\t\r'
 * [x] skip c89 comments
 * [x] identifier vs keyword
 * [ ] literals and constant
 * [x] operators (not all)
 * [x] puncuators (...)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* return 1 if c is a-z or A-Z */
int is_azAZ(char c) {
    if ((c >= 'a' && c <='z') || (c >= 'A' && c <='Z')) return 1;
    return 0;
}

/* return true if c is 0-9 */
int is_09(char c) {
    if (c >= '0' && c <='9') return 1;
    return 0;
}

/* return 1 if c is ' \n\t\r' */
int is_white_space(int c) {
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r') return 1;
    return 0;
}

int is_keyword(const char *word) {
    int i;
    const char *keywords[] = {
        "char", "int", "float", "double", "void",
        "signed", "unsigned", "short", "long",
        "struct", "enum", "union",

        "auto", "const", "extern", "register", "static", "volatile",

        "break", "case", "continue", "default", "do", "else",
        "for", "goto", "if", "return", "switch", "while",

        "sizeof", "typedef"
    };
    
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; /* It is a keyword */
        }
    }
    return 0; /* It is a regular identifier */
}
int is_punc(char c) {
    /* (){}[];,: ... */
    int i;
    char *punc = "(){}[];,:";
    for (i = 0; punc[i] != '\0'; i++) {
        if (punc[i] == c) {
            return 1;
        }
    }
    return 0;
}

int is_operator(char c) {
    /* */
    int i;
    char *op = "+-*/%=<>!&|^~?:.";
    for (i = 0; op[i] != '\0'; i++) {
        if (op[i] == c) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int i;
#if 1
    char *src;
    FILE *f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    long src_len = ftell(f);
    rewind(f);
    src = (char *)malloc(src_len + 1);
    size_t bytes_read = fread(src, 1, src_len, f);
    src[bytes_read] = '\0';
#else
    char *src = 
        "int main() {\n"
        "    /*this is a comment\n"
        "     * multi line commetn\n"
        "     */ \n"
        "    int hello = 0;\n"
        "    return 0;\n"
        "}\0";
    int src_len = strlen(src);
#endif

    for (i = 0; i < src_len; ++i) {

        /* [x] TODO: trim whitespace */
        if (is_white_space(src[i])) {
#if 0
            if (src[i] == ' ') {
                printf("WSP: SPACE\n");
            } else if (src[i] == '\n') {
                printf("WSP: NEW_LINE\n");
            } else if (src[i] == '\t') {
                printf("WSP: TABS\n");
            } else if (src[i] == '\r') {
                printf("WSP: CARRIGE_RET\n");
            } else {
                printf("WSP: UNKNOWN\n");
            }
#endif
            continue;
        }

        /* skip the preprocessor */
        if (src[i] == '#') {
            char buff[256]; /* 1byte reserver for bull byte */
            int buff_len = 0;
            while (src[i] != '\n' && src[i] != '\0') {
                if (buff_len < 255) buff[buff_len++] = src[i];
                i++;
            }
            buff[buff_len] = '\0';
            --i;
            printf("PREPROCESSOR: \t%s\n", buff);
        }

        /* [x] single line comments */
        else if (src[i] == '/' && src[i+1] == '*') {
            i += 2;
            while (src[i] != '\0' && !(src[i] == '*' && src[i+1] == '/')) i++;
            if (src[i] == '\0') {
                printf("ERROR: Unclosed comment\n");
            }
            /*  --X  */
            /*    ^  */
            i++; /* place in backslace the for loop put in X pos */
        }

        /* identifier or keyword (a-zA-Z_)(a-zA-Z0-9_)* */
        else if(is_azAZ(src[i]) || src[i] == '_') {
            char buffer[256];
            int buff_len = 0;

            /* keep reading while c == (a-zA-Z0-9_)
             * and copy the word to buffer
             * */
            while (is_azAZ(src[i]) || is_09(src[i]) || src[i] == '_') {
                if (buff_len < 256) buffer[buff_len++] = src[i];
                i++;
            }
            buffer[buff_len] = '\0';
            --i;

            if (is_keyword(buffer)) {
                printf("KEYWORD: \t%s\n", buffer);
            } else {
                printf("IDENTIFIER: \t%s\n", buffer);
            }
        } 

        else if (is_operator(src[i])) {
            /* operator in c 3, 2, 1 */
            char op[4] = {0}; /* +1 for null byte */

            /* check 3char operator */
            if ((src[i] == '<' && src[i] == '<' && src[i] == '=') ||
                (src[i] == '>' && src[i] == '>' && src[i] == '=') ||
                (src[i] == '.' && src[i] == '.' && src[i] == '.')) {
                op[0] = src[i];
                op[1] = src[i+1];
                op[2] = src[i+2];
                i += 2; /* skip the operator now */
            }

            /* check for 2 char operator */
            else if (
                /* ++, --, &&, ||, <<, >> */
                ((src[i] == '+' || src[i] == '-' || src[i] == '&' || src[i] == '|' || src[i] == '>' || src[i] == '<') && src[i+1] == src[i]) ||
                /* compound assignment & comparision: ==, !=, <=, >=, +=, -=, *=, /=, %=, &=, |=, ^= */
                ((src[i] == '=' || src[i] == '!' || src[i] == '<' || src[i] == '>' || src[i] == '+' || src[i] == '-' || src[i] == '*' || src[i] == '/' || src[i] == '%' || src[i] == '&' || src[i] == '|' || src[i] == '^') && src[i] == '=') ||
                /* pointer arrow: -> */
                (src[i] == '-' && src[i+1] == '>')) {
                op[0] = src[i];
                op[1] = src[i+1];
                i += 1; /* skip the operator now */
            }
            else {
                op[0] = src[i];
            }

            printf("OPERATOR: \t%s\n", op);
        }
        
        /* puncuators */
        else if (is_punc(src[i])) {
            printf("PUNCUATOR: \t%c\n", src[i]);
        }

        else {
            printf("---------: \t%c\n", src[i]);
        }

    }

    return 0;
}
