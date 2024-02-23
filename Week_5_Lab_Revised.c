#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

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
    snprintf(cmd, sizeof(cmd), "wc -c < %s", argv[1]);
    system(cmd);

    return 0;
}
