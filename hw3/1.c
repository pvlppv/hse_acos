#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void replace_regex(const char *pattern, const char *text, const char *replacement) {
    regex_t regex;
    regmatch_t match;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed\n");
        return;
    }

    size_t bufsize = strlen(text) + 1;
    char *buffer = (char*)malloc(bufsize);
    if (!buffer) {
        printf("Memory allocation failed\n");
        regfree(&regex);
        return;
    }
    buffer[0] = '\0';

    const char *current = text;

    while (regexec(&regex, current, 1, &match, 0) == 0) {
        size_t prefix_len = match.rm_so;
        size_t replace_len = strlen(replacement);
        size_t current_len = strlen(buffer);
        size_t needed = current_len + prefix_len + replace_len + 1;

        if (needed >= bufsize) {
            bufsize = needed * 2;
            char *new_buf = (char*)realloc(buffer, bufsize);
            if (!new_buf) {
                printf("Memory reallocation failed\n");
                free(buffer);
                regfree(&regex);
                return;
            }
            buffer = new_buf;
        }

        strncat(buffer, current, prefix_len);
        strcat(buffer, replacement);

        current += match.rm_eo;
    }

    strcat(buffer, current);
    printf("%s\n", buffer);

    free(buffer);
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <regex> <text> <replacement>\n", argv[0]);
        return 1;
    }

    replace_regex(argv[1], argv[2], argv[3]);
    return 0;
}