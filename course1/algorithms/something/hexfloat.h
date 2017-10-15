#include <stdio.h>
#include <stdarg.h>

int c99printf(char* buffer, size_t size, const char* format, ...){
    va_list args;
    va_start(args, format);
    int n = vsnprintf(buffer, size, format, args);
    va_end (args);
    return n;
}
