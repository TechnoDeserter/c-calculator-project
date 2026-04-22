#include <stdio.h>

static FILE *open_file(const char *path, const char *mode) {
    FILE *file = NULL;
#ifdef _MSC_VER
    fopen_s(&file, path, mode);
#else
    file = fopen(path, mode);
#endif
    return file;
}

static int scan_int(const char *format, int *value) {
#ifdef _MSC_VER
    return scanf_s(format, value);
#else
    return scanf(format, value);
#endif
}

static int scan_double(const char *format, double *value) {
#ifdef _MSC_VER
    return scanf_s(format, value);
#else
    return scanf(format, value);
#endif
}

static int scan_operator(char *value) {
#ifdef _MSC_VER
    return scanf_s(" %c", value, 1);
#else
    return scanf(" %c", value);
#endif
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_menu_choice(void) {
    int choice;
    if (scan_int("%d", &choice) != 1) {
        clear_input_buffer();
        return -1;
    }
    clear_input_buffer();
    return choice;
}

static int read_double_input(const char *prompt, double *value) {
    while (1) {
        printf("%s", prompt);
        if (scan_double("%lf", value) == 1) {
            clear_input_buffer();
            return 1;
        }
        printf("Invalid number. Please try again.\n");
        clear_input_buffer();
    }
}

static void show_menu(void) {
    printf("========================================\n");
    printf("1. New Calculation\n");
    printf("2. Show History\n");
    printf("3. Clear History\n");
    printf("0. Quit\n");
    printf("========================================\n");
    printf("Choose an option: ");
}

void clear_history() {
    FILE *logFile = open_file("calculations.log", "w");
    if (logFile == NULL) {
        printf("Unable to clear history right now.\n\n");
        return;
    }
    fclose(logFile);
    printf("History cleared successfully.\n\n");
}


void show_history() {
    FILE *logFile = open_file("calculations.log", "r");
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
        show_menu();
        choice = read_menu_choice();
        if (choice == -1) {
            printf("Invalid option! Please enter a number from the menu.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                read_double_input("\nEnter first number: ", &num1);

                printf("Enter operator (+, -, *, /): ");
                scan_operator(&operator);

                read_double_input("Enter second number: ", &num2);

                switch (operator) {
                    case '+':
                        result = num1 + num2;
                        break;
                    case '-':
                        result = num1 - num2;
                        break;
                    case '*':
                        result = num1 * num2;
                        break;
                    case '/':
                        if (num2 == 0) {
                            printf("Error: Cannot divide by zero!\n\n");
                            continue;
                        }
                        result = num1 / num2;
                        break;
                    default:
                        printf("Invalid operator! Use +, -, *, or /\n\n");
                        continue;
                }

                printf("Result: %.2f\n\n", result);

                // Save to log (same logging you already understand)
                FILE *logFile = open_file("calculations.log", "a");
                if (logFile != NULL) {
                    fprintf(logFile, "%.2f %c %.2f = %.2f\n", num1, operator, num2, result);
                    fclose(logFile);
                }
                break;

            case 2:
                show_history();
                break;

            case 3:
                clear_history();
                break;

            case 0:
                printf("Thank you for using the calculator!\n");
                break;

            default:
                printf("Invalid option! Try 0, 1, 2 or 3.\n\n");
                break;
        }
    }

    return 0;
}