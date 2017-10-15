#include <stdio.h>

int main() {
    FILE *in = fopen("verysecretfilename.in", "r");
    if (in != NULL) {
        FILE *out = fopen("verysecretfilename.out", "w");
        fprintf(out, "strace is a great debugging tool!\n");
        fclose(out);
        fclose(in);
    } else {
        printf("File not found\n");
    }
}