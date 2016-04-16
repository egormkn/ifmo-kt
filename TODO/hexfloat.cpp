#include <stdio.h>
#include <stdarg.h>
int printfc(char* buffer, const char* format, ...){
    va_list args;
    va_start(args, format);
    int n = vsprintf(buffer, format, args);
    va_end (args);
    return n;
}