#include <stdio.h>
#include <string.h>

int main() {
    const char correct[] = "tffqwamfwvupqhxnivmw";
    char string[64];
    printf("Enter password:\n");
    int result = scanf("%64s", string);
    if (strcmp(string, correct) == 0 && result >= 0) {
        printf("Correct!\n");
    } else {
        printf("Incorrect!\n");
    }
}