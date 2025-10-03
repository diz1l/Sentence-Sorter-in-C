#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMS ".?!"

static void append_sentence(char ***arr, size_t *n, const char *s) {
    char **tmp = realloc(*arr, (*n + 1) * sizeof(char*));
    if (!tmp) return;
    *arr = tmp;

    size_t len = strlen(s) + 1;
    (*arr)[*n] = malloc(len);
    if (!(*arr)[*n]) return;
    memcpy((*arr)[*n], s, len);

    (*n)++;
}

void trim(char *str) {
    int start = 0;
    int end = (char)strlen(str) - 1;

    while (isspace((unsigned char)str[start])) {
        start++;
    }

    while (end >= start && isspace((unsigned char)str[end])) {
        str[end] = '\0';
        end--;
    }

    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
}

void toLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            str[i] = (char)tolower(str[i]);
        }
    }
}

int readFile(FILE *fileName, char *buffer, int bufferSize,
             char ***out_arr, size_t *out_n) {
    while (fgets(buffer, bufferSize, fileName) != NULL) {
        char *token = strtok(buffer, DELIMS);
        while (token) {
            toLower(token);
            trim(token);
            if (*token) {
                append_sentence(out_arr, out_n, token);
            }
            token = strtok(NULL, DELIMS);
        }
    }
    return 0;
}

int sortFile(const void *a, const void *b) {
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    return strcmp(sa, sb);
}

int main()
{
    FILE *file = fopen("abc.txt", "r");
    if (!file)
    {
        perror("ERROR");
        return 1;
    }

    int bufferSize = 2024;
    char* buffer = malloc(bufferSize *sizeof(char));

    char **sentences = NULL;
    size_t count = 0;

    readFile(file, buffer, bufferSize, &sentences, &count);
    qsort(sentences, count, sizeof(char*), sortFile);

    for (size_t i = 0; i < count; i++) {
        printf("[%s]\n", sentences[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(sentences[i]);
    }
    free(sentences);
    free(buffer);
    fclose(file);
    return 0;
}
