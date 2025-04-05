#ifndef PIZZA_H
#define PIZZA_H

#define MAX_INGREDIENTS_LENGTH 256
#define MAX_NAME_LENGTH 128

// Define a structure to represent a pizza
typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[MAX_NAME_LENGTH];
    int quantity;
    char order_date[MAX_NAME_LENGTH];
    char order_time[MAX_NAME_LENGTH];
    float unit_price;
    float total_price;
    char pizza_size[MAX_NAME_LENGTH];
    char pizza_category[MAX_NAME_LENGTH];
    char pizza_ingredients[MAX_INGREDIENTS_LENGTH];
    char pizza_name[MAX_NAME_LENGTH];
} Pizza;

// Function declarations
void print_pizza(const Pizza *pizza);
int parse_pizza_line(const char *line, Pizza *pizza);


// New function declarations for best-sold pizza
int read_pizzas(const char *filename, Pizza pizzas[], int *pizza_count);
void find_best_sold_pizza(Pizza pizzas[], int pizza_count);
void find_worst_sold_pizza(Pizza pizzas[], int pizza_count);

// Metrics using function pointers
char* apo(int *size, Pizza *pizzas); // average pizzas per order
char* apd(int *size, Pizza *pizzas); // average pizzas per day
char* ims(int *size, Pizza *pizzas); // most used ingredient
char* hp(int *size, Pizza *pizzas);  // pizzas per category


#endif // PIZZA_H