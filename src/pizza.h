#ifndef PIZZA_H
#define PIZZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de Pizza
typedef struct {
    int id;
    char nombre[50];
    char ingredientes[200];
    char tamano[20];
    int precio;
    int cantidad_vendida;
    char fecha[20];
    int ingresos;
} Pizza;

// Declaración de funciones
void menu();
void cargar_pizzas(Pizza pizzas[], int *num_pizzas);
void mostrar_estadisticas(Pizza pizzas[], int num_pizzas, const char* comando);
void pizza_mas_vendida(Pizza pizzas[], int num_pizzas);
void pizza_menos_vendida(Pizza pizzas[], int num_pizzas);
void fecha_mas_ventas(Pizza pizzas[], int num_pizzas);
void fecha_menos_ventas(Pizza pizzas[], int num_pizzas);
void fecha_mas_ventas_por_cantidad(Pizza pizzas[], int num_pizzas);
void fecha_menos_ventas_por_cantidad(Pizza pizzas[], int num_pizzas);
void ingrediente_mas_vendido(Pizza pizzas[], int num_pizzas);
void promedio_pizzas_por_orden(Pizza pizzas[], int num_pizzas);
void promedio_pizzas_por_dia(Pizza pizzas[], int num_pizzas);
void cantidad_pizzas_por_categoria(Pizza pizzas[], int num_pizzas);

#endif
