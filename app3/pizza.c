#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#define MAX_PIZZAS 100

typedef struct {
    char pizza_name[MAX_NAME_LENGTH];
    int total_quantity;
} PizzaSales;


// Function to print a Pizza structure
void print_pizza(const Pizza *pizza) {
    printf("Pizza ID: %d\n", pizza->pizza_id);
    printf("Order ID: %d\n", pizza->order_id);
    printf("Pizza Name ID: %s\n", pizza->pizza_name_id);
    printf("Quantity: %d\n", pizza->quantity);
    printf("Order Date: %s\n", pizza->order_date);
    printf("Order Time: %s\n", pizza->order_time);
    printf("Unit Price: %.2f\n", pizza->unit_price);
    printf("Total Price: %.2f\n", pizza->total_price);
    printf("Pizza Size: %s\n", pizza->pizza_size);
    printf("Pizza Category: %s\n", pizza->pizza_category);
    printf("Pizza Ingredients: %s\n", pizza->pizza_ingredients);
    printf("Pizza Name: %s\n\n", pizza->pizza_name);
}

// Function to parse a line from the CSV file into a Pizza structure
int parse_pizza_line(const char *line, Pizza *pizza) {
    printf("Parsing line: %s\n", line);
    if (sscanf(line, "%f,%f,%[^,],%d,%[^,],%[^,],%f,%f,%[^,],%[^,],\"%[^\"]\",%[^\n]",
               &pizza->pizza_id,        // Use %f for floating-point numbers
               &pizza->order_id,        // Use %f for floating-point numbers
               pizza->pizza_name_id,
               &pizza->quantity,
               pizza->order_date,
               pizza->order_time,
               &pizza->unit_price,
               &pizza->total_price,
               pizza->pizza_size,
               pizza->pizza_category,
               pizza->pizza_ingredients,
               pizza->pizza_name) != 12) { // Ensure all 12 fields are parsed
        fprintf(stderr, "Error parsing line: %s\n", line);
        return 0;
    }
    return 1;
}

// Function to find the best-sold pizza
void find_best_sold_pizza(Pizza pizzas[], int pizza_count) {
    PizzaSales sales[MAX_PIZZAS];
    int sales_count = 0;

    // Aggregate sales by pizza name
    for (int i = 0; i < pizza_count; i++) {
        int found = 0;
        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].pizza_name, pizzas[i].pizza_name) == 0) {
                sales[j].total_quantity += pizzas[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(sales[sales_count].pizza_name, pizzas[i].pizza_name);
            sales[sales_count].total_quantity = pizzas[i].quantity;
            sales_count++;
        }
    }

    // Find the pizza with the highest quantity
    int max_quantity = 0;
    char best_sold_pizza[MAX_NAME_LENGTH];
    for (int i = 0; i < sales_count; i++) {
        if (sales[i].total_quantity > max_quantity) {
            max_quantity = sales[i].total_quantity;
            strcpy(best_sold_pizza, sales[i].pizza_name);
        }
    }

    // Print the result
    printf("Best Sold Pizza: %s (Total Quantity: %d)\n", best_sold_pizza, max_quantity);
}
// Function to find the worst-sold pizza
void find_worst_sold_pizza(Pizza pizzas[], int pizza_count) {
    PizzaSales sales[MAX_PIZZAS];
    int sales_count = 0;

    // Aggregate sales by pizza name
    for (int i = 0; i < pizza_count; i++) {
        int found = 0;
        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].pizza_name, pizzas[i].pizza_name) == 0) {
                sales[j].total_quantity += pizzas[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(sales[sales_count].pizza_name, pizzas[i].pizza_name);
            sales[sales_count].total_quantity = pizzas[i].quantity;
            sales_count++;
        }
    }

    // Find the pizza with the lowest quantity
    int min_quantity = sales[0].total_quantity;
    char worst_sold_pizza[MAX_NAME_LENGTH];
    strcpy(worst_sold_pizza, sales[0].pizza_name);

    for (int i = 1; i < sales_count; i++) {
        if (sales[i].total_quantity < min_quantity) {
            min_quantity = sales[i].total_quantity;
            strcpy(worst_sold_pizza, sales[i].pizza_name);
        }
    }

    // Print the result
    printf("Worst Sold Pizza: %s (Total Quantity: %d)\n", worst_sold_pizza, min_quantity);
}