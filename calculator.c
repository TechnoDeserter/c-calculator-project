#include <stdio.h>
#include <stdlib.h>

void show_history() {
    FILE *logFile = fopen("calculations.log", "r");
    if (logFile == NULL) {
        printf("No history yet! Do some calculations first.\n\n");
        return;
    }
    printf("\n=== Calculation History ===\n");
    char line[100];
    while (fgets(line, sizeof(line), logFile)) {
        printf("%s", line);
    }
    fclose(logFile);
    printf("===========================\n\n");
}

int main() {
    double num1, num2, result;
    char operator;
    int choice = 1;

    printf("=== Mika's Professional C Calculator (Version 2) ===\n\n");

    while (choice != 0) {
        printf("1. New Calculation\n");
        printf("2. Show History\n");
        printf("0. Quit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\nEnter first number: ");
            scanf("%lf", &num1);

            printf("Enter operator (+, -, *, /): ");
            scanf(" %c", &operator);

            printf("Enter second number: ");
            scanf("%lf", &num2);

            if (operator == '+')      result = num1 + num2;
            else if (operator == '-') result = num1 - num2;
            else if (operator == '*') result = num1 * num2;
            else if (operator == '/') {
                if (num2 == 0) {
                    printf("Error: Cannot divide by zero!\n\n");
                    continue;
                }
                result = num1 / num2;
            }
            else {
                printf("Invalid operator! Use +, -, *, or /\n\n");
                continue;
            }

            printf("Result: %.2f\n\n", result);

            // Save to log (same logging you already understand)
            FILE *logFile = fopen("calculations.log", "a");
            if (logFile != NULL) {
                fprintf(logFile, "%.2f %c %.2f = %.2f\n", num1, operator, num2, result);
                fclose(logFile);
            }

        } else if (choice == 2) {
            show_history();
        } else if (choice == 0) {
            printf("Thank you for using the calculator!\n");
        } else {
            printf("Invalid option! Try 0, 1 or 2.\n\n");
        }
    }

    return 0;
}