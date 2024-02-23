#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

// Function to escape special characters in a string for shell execution
void escape(char* dest, const char* src, size_t dest_size) {
    size_t i = 0;
    size_t j = 0;
    while (src[i] != '\0' && j < dest_size - 1) {
        if (src[i] == '"' || src[i] == '\\' || src[i] == '$' || src[i] == '`') {
            dest[j++] = '\\';
        }
        dest[j++] = src[i++];
    }
    dest[j] = '\0';
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Validate input file name length
    if (strlen(argv[1]) >= BUFSIZE - strlen("wc -c < ")) {
        fprintf(stderr, "Input file name is too long\n");
        return 1;
    }

    char cmd[BUFSIZE];
    snprintf(cmd, sizeof(cmd), "wc -c < ");
    char escaped_filename[BUFSIZE];
    escape(escaped_filename, argv[1], sizeof(escaped_filename));
    strncat(cmd, escaped_filename, sizeof(cmd) - strlen(cmd) - 1);

    system(cmd);

    return 0;
}
