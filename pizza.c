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
//Average pizzas per order
char* apo(int *size, Pizza *pizzas) {
    int orders = 0;
    int total = 0;
    int last_order_id = -1;

    for (int i = 0; i < *size; i++) {
        total += pizzas[i].quantity;
        if (pizzas[i].order_id != last_order_id) {
            orders++;
            last_order_id = pizzas[i].order_id;
        }
    }

    float avg = (float)total / orders;
    char *result = malloc(64);
    snprintf(result, 64, "Average pizzas per order: %.2f", avg);
    return result;
}

#include <stdbool.h>
//Average pizzas per day
char* apd(int *size, Pizza *pizzas) {
    char unique_dates[1000][MAX_NAME_LENGTH];
    int date_count = 0;
    int total = 0;

    for (int i = 0; i < *size; i++) {
        total += pizzas[i].quantity;
        bool found = false;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(pizzas[i].order_date, unique_dates[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            strcpy(unique_dates[date_count++], pizzas[i].order_date);
        }
    }

    float avg = (float)total / date_count;
    char *result = malloc(64);
    snprintf(result, 64, "Average pizzas per day: %.2f", avg);
    return result;
}
//Most used Ingredient
char* ims(int *size, Pizza *pizzas) {
    struct {
        char name[64];
        int count;
    } ingredients[1000];

    int ing_count = 0;

    for (int i = 0; i < *size; i++) {
        char line[MAX_INGREDIENTS_LENGTH];
        strcpy(line, pizzas[i].pizza_ingredients);
        char *token = strtok(line, ",");

        while (token != NULL) {
            while (*token == ' ') token++; // Trim space
            bool found = false;
            for (int j = 0; j < ing_count; j++) {
                if (strcmp(ingredients[j].name, token) == 0) {
                    ingredients[j].count += pizzas[i].quantity;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(ingredients[ing_count].name, token);
                ingredients[ing_count].count = pizzas[i].quantity;
                ing_count++;
            }
            token = strtok(NULL, ",");
        }
    }

    int max = 0;
    char top[64];
    for (int i = 0; i < ing_count; i++) {
        if (ingredients[i].count > max) {
            max = ingredients[i].count;
            strcpy(top, ingredients[i].name);
        }
    }

    char *result = malloc(128);
    snprintf(result, 128, "Most used ingredient: %s (%d units)", top, max);
    return result;
}
//Count pizzas by category
char* hp(int *size, Pizza *pizzas) {
    struct {
        char category[MAX_NAME_LENGTH];
        int count;
    } categories[100];

    int cat_count = 0;
    for (int i = 0; i < *size; i++) {
        bool found = false;
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(categories[j].category, pizzas[i].pizza_category) == 0) {
                categories[j].count += pizzas[i].quantity;
                found = true;
                break;
            }
        }
        if (!found) {
            strcpy(categories[cat_count].category, pizzas[i].pizza_category);
            categories[cat_count].count = pizzas[i].quantity;
            cat_count++;
        }
    }

    char *result = malloc(512);
    strcpy(result, "Pizza count by category:\n");
    for (int i = 0; i < cat_count; i++) {
        char line[128];
        snprintf(line, 128, "- %s: %d\n", categories[i].category, categories[i].count);
        strcat(result, line);
    }
    return result;
}
