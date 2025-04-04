#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#define MAX_PIZZAS 100
#define MAX_LINE_LENGTH 1024

// Function to read and process pizzas from the CSV file
int read_pizzas(const char *filename, Pizza pizzas[], int *pizza_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    Pizza pizza;

    // Read and skip the header line
    if (fgets(line, MAX_LINE_LENGTH, file)) {
        // Skip header
    }

    // Read and parse each line of the CSV file
    *pizza_count = 0;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (parse_pizza_line(line, &pizza)) {
            pizzas[(*pizza_count)++] = pizza;
        } else {
            fprintf(stderr, "Error parsing line: %s", line);
        }
    }

    fclose(file);
    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <command>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *command = argv[2];

    Pizza pizzas[MAX_PIZZAS];
    int pizza_count;

    if (read_pizzas(filename, pizzas, &pizza_count)) {
        if (strcmp(command, "pms") == 0) {
            find_best_sold_pizza(pizzas, pizza_count);
        } else if (strcmp(command, "pls") == 0) { // New command for worst-sold pizza
            find_worst_sold_pizza(pizzas, pizza_count);
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}