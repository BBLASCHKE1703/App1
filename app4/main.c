#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pizza.h"

#define MAX_PIZZAS 100
#define MAX_LINE_LENGTH 1024

// Define a type for metrics using function pointers
typedef char* (*MetricFunc)(int*, Pizza*);

// Metrics that use function pointers
const char *metric_names[] = {"apo", "apd", "ims", "hp", "pms", "pls"};
MetricFunc metrics[] = {apo, apd, ims, hp, pms, pls};
const int num_metrics = 6;

// Function to read and parse pizzas from the CSV file
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
    if (argc < 3) {
        printf("Usage: %s <filename> <metric1> [<metric2> ...]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    Pizza pizzas[MAX_PIZZAS];
    int pizza_count;

    // Load pizza data from the file
    if (!read_pizzas(filename, pizzas, &pizza_count)) {
        return 1;
    }

    // Process each command line metric
    for (int i = 2; i < argc; i++) {
        const char *command = argv[i];
        bool handled = false;

        // Check metrics handled via function pointers
        for (int j = 0; j < num_metrics; j++) {
            if (strcmp(command, metric_names[j]) == 0) {
                char *result = metrics[j](&pizza_count, pizzas);
                printf("%s: %s\n", command, result);
                free(result);
                handled = true;
                break;
            }
        }

        if (!handled) {
            fprintf(stderr, "Unknown metric: %s\n", command);
        }
    }

    return 0;
}
