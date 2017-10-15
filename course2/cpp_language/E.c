#include <stdio.h>
#include <string.h>

int main() {
    const char correct[] = "strings_is_good_debugging_tool_too";
    char string[64];
    printf("Enter password:\n");
    int result = scanf("%64s", string);
    if (strcmp(string, correct) == 0 && result >= 0) {
        printf("Correct!\n");
    } else {
        printf("Incorrect!\n");
    }
}