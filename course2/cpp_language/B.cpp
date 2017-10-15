#include <unistd.h>
#include <stdio.h>

void cat() {
    const int BUFFER_SIZE = 512;
    const int INPUT = fileno(stdin);
    const int OUTPUT = fileno(stdout);

    char buffer[BUFFER_SIZE + 1];
    ssize_t read_count, write_count, written;

    while((read_count = read(INPUT, buffer, BUFFER_SIZE)) > 0) {
        written = 0;
        while (written < read_count) {
            write_count = write(OUTPUT, buffer + written, (unsigned int) read_count - written);
            written += write_count;
        }
    }

    fflush(stdout);
}