#ifndef PIZZA_H
#define PIZZA_H

/* ---------- límites generales ---------- */
#define MAX_PIZZAS            100          /* ajusta si necesitas más    */
#define MAX_DAYS              400
#define MAX_INGREDIENTS_LENGTH 256
#define MAX_NAME_LENGTH        128

/* ---------- registro de una fila del CSV ---------- */
typedef struct {
    int   pizza_id;
    int   order_id;
    char  pizza_name_id[MAX_NAME_LENGTH];
    int   quantity;
    char  order_date[11];                 /* YYYY-MM-DD normalizado      */
    char  order_time[MAX_NAME_LENGTH];
    float unit_price;
    float total_price;
    char  pizza_size[MAX_NAME_LENGTH];
    char  pizza_category[MAX_NAME_LENGTH];
    char  pizza_ingredients[MAX_INGREDIENTS_LENGTH];
    char  pizza_name[MAX_NAME_LENGTH];
} Pizza;

/* ---------- estructuras auxiliares ---------- */
typedef struct {
    char  date[11];
    int   total_quantity;
    float total_money;
} DateSales;

/* ---------- parser y utilidades ---------- */
void   print_pizza(const Pizza *pizza);
int    parse_pizza_line(const char *line, Pizza *pizza);
int    read_pizzas(const char *filename, Pizza pizzas[], int *pizza_count);

/* ---------- métricas (devuelven string dinámico) ---------- */
char* pms (int *size, Pizza *pizzas);   /* best‑sold pizza          */
char* pls (int *size, Pizza *pizzas);   /* worst‑sold pizza         */
char* apo (int *size, Pizza *pizzas);   /* avg pizzas per order     */
char* apd (int *size, Pizza *pizzas);   /* avg pizzas per day       */
char* ims (int *size, Pizza *pizzas);   /* most used ingredient     */
char* hp  (int *size, Pizza *pizzas);   /* pizzas per category      */
char* dms (int *size, Pizza *pizzas);   /* day max money            */
char* dls (int *size, Pizza *pizzas);   /* day min money            */
char* dmsp(int *size, Pizza *pizzas);   /* day max pizzas           */
char* dlsp(int *size, Pizza *pizzas);   /* day min pizzas           */

#endif
