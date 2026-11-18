/*
 * [x] skip whitespace ' \n\t\r'
 * [x] skip c89 comments
 * [x] identifier vs keyword
 * [ ] literals and constant
 * [ ] operators
 * [ ] puncuators
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
    int k;
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

    for (k = 0; k < num_keywords; k++) {
        if (strcmp(word, keywords[k]) == 0) {
            return 1; /* It is a keyword */
        }
    }
    return 0; /* It is a regular identifier */
}

int main(int argc, char **argv)
{
    int i;
#if 0
    char *src;
    FILE *f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    rewind(f);
    src = (char *)malloc(file_size + 1);
    size_t bytes_read = fread(src, 1, file_size, f);
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
                printf("KEYWORD: %s\n", buffer);
            } else {
                printf("IDENT: %s\n", buffer);
            }
        } 
        
        else if () {
        }

        else {
            printf("NA: %c\n", src[i]);
        }

    }

    return 0;
}
