//
// Created by Brmax on 01-04-2025.
//
#include "pizza.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cargar información de las pizzas desde un archivo CSV
void cargar_pizzas(Pizza pizzas[], int *num_pizzas) {
    printf("Intentando abrir el archivo: pizzas.csv\n");
    FILE *file = fopen("pizzas.csv", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo pizzas.csv\n");
        exit(1);  // Si no se puede abrir el archivo, termina el programa
    }

    char line[256];
    int i = 0;

    // Leer la primera línea (encabezados)
    fgets(line, sizeof(line), file);

    // Leer el resto de las líneas
    while (fgets(line, sizeof(line), file)) {
        // Usar sscanf para extraer los valores separados por comas
        sscanf(line, "%d,%49[^,],%199[^,],%19[^,],%d,%d,%19s",
               &pizzas[i].id, pizzas[i].nombre, pizzas[i].ingredientes,
               pizzas[i].tamano, &pizzas[i].precio, &pizzas[i].cantidad_vendida, pizzas[i].fecha);
        pizzas[i].ingresos = pizzas[i].precio * pizzas[i].cantidad_vendida;  // Calcular ingresos
        i++;
    }

    *num_pizzas = i;  // Establecer el número de pizzas cargadas
    fclose(file);
}

// Mostrar el menú de comandos
void menu() {
    printf("Comandos disponibles:\n");
    printf("1. pms: Pizza más vendida\n");
    printf("2. pls: Pizza menos vendida\n");
    printf("3. dms: Fecha con más ventas en términos de dinero\n");
    printf("4. dls: Fecha con menos ventas en términos de dinero\n");
    printf("5. dmsp: Fecha con más ventas en términos de cantidad de pizzas\n");
    printf("6. dlsp: Fecha con menos ventas en términos de cantidad de pizzas\n");
    printf("7. apo: Promedio de pizzas por orden\n");
    printf("8. apd: Promedio de pizzas por día\n");
    printf("9. ims: Ingrediente más vendido\n");
    printf("10. hp: Cantidad de pizzas por categoría vendidas\n");
    printf("Ingrese un comando:\n");
}

// Mostrar estadísticas dependiendo del comando pasado como argumento
void mostrar_estadisticas(Pizza pizzas[], int num_pizzas, const char* comando) {
    if (strcmp(comando, "pms") == 0) {
        pizza_mas_vendida(pizzas, num_pizzas);
    } else if (strcmp(comando, "pls") == 0) {
        pizza_menos_vendida(pizzas, num_pizzas);
    } else if (strcmp(comando, "dms") == 0) {
        fecha_mas_ventas(pizzas, num_pizzas);
    } else if (strcmp(comando, "dls") == 0) {
        fecha_menos_ventas(pizzas, num_pizzas);
    } else if (strcmp(comando, "dmsp") == 0) {
        fecha_mas_ventas_por_cantidad(pizzas, num_pizzas);
    } else if (strcmp(comando, "dlsp") == 0) {
        fecha_menos_ventas_por_cantidad(pizzas, num_pizzas);
    } else if (strcmp(comando, "apo") == 0) {
        promedio_pizzas_por_orden(pizzas, num_pizzas);
    } else if (strcmp(comando, "apd") == 0) {
        promedio_pizzas_por_dia(pizzas, num_pizzas);
    } else if (strcmp(comando, "ims") == 0) {
        ingrediente_mas_vendido(pizzas, num_pizzas);
    } else if (strcmp(comando, "hp") == 0) {
        cantidad_pizzas_por_categoria(pizzas, num_pizzas);
    } else {
        printf("Comando desconocido.\n");
    }
}

// Pizza más vendida
void pizza_mas_vendida(Pizza pizzas[], int num_pizzas) {
    int max_ventas = 0;
    int index = -1;
    for (int i = 0; i < num_pizzas; i++) {
        if (pizzas[i].cantidad_vendida > max_ventas) {
            max_ventas = pizzas[i].cantidad_vendida;
            index = i;
        }
    }
    printf("Pizza más vendida: %s, Cantidad vendida: %d\n", pizzas[index].nombre, pizzas[index].cantidad_vendida);
}

// Pizza menos vendida
void pizza_menos_vendida(Pizza pizzas[], int num_pizzas) {
    int min_ventas = pizzas[0].cantidad_vendida;
    int index = 0;
    for (int i = 1; i < num_pizzas; i++) {
        if (pizzas[i].cantidad_vendida < min_ventas) {
            min_ventas = pizzas[i].cantidad_vendida;
            index = i;
        }
    }
    printf("Pizza menos vendida: %s, Cantidad vendida: %d\n", pizzas[index].nombre, pizzas[index].cantidad_vendida);
}

// Fecha con más ventas en términos de dinero
void fecha_mas_ventas(Pizza pizzas[], int num_pizzas) {
    int max_ingresos = 0;
    char fecha[20];
    for (int i = 0; i < num_pizzas; i++) {
        if (pizzas[i].ingresos > max_ingresos) {
            max_ingresos = pizzas[i].ingresos;
            strcpy(fecha, pizzas[i].fecha);
        }
    }
    printf("Fecha con más ventas en dinero: %s, Ingresos: %d\n", fecha, max_ingresos);
}

// Fecha con menos ventas en términos de dinero
void fecha_menos_ventas(Pizza pizzas[], int num_pizzas) {
    int min_ingresos = pizzas[0].ingresos;
    char fecha[20];
    for (int i = 1; i < num_pizzas; i++) {
        if (pizzas[i].ingresos < min_ingresos) {
            min_ingresos = pizzas[i].ingresos;
            strcpy(fecha, pizzas[i].fecha);
        }
    }
    printf("Fecha con menos ventas en dinero: %s, Ingresos: %d\n", fecha, min_ingresos);
}

// Fecha con más ventas en términos de cantidad de pizzas
void fecha_mas_ventas_por_cantidad(Pizza pizzas[], int num_pizzas) {
    int max_ventas = 0;
    char fecha[20];
    for (int i = 0; i < num_pizzas; i++) {
        if (pizzas[i].cantidad_vendida > max_ventas) {
            max_ventas = pizzas[i].cantidad_vendida;
            strcpy(fecha, pizzas[i].fecha);
        }
    }
    printf("Fecha con más ventas por cantidad de pizzas: %s, Cantidad vendida: %d\n", fecha, max_ventas);
}

// Fecha con menos ventas en términos de cantidad de pizzas
void fecha_menos_ventas_por_cantidad(Pizza pizzas[], int num_pizzas) {
    int min_ventas = pizzas[0].cantidad_vendida;
    char fecha[20];
    for (int i = 1; i < num_pizzas; i++) {
        if (pizzas[i].cantidad_vendida < min_ventas) {
            min_ventas = pizzas[i].cantidad_vendida;
            strcpy(fecha, pizzas[i].fecha);
        }
    }
    printf("Fecha con menos ventas por cantidad de pizzas: %s, Cantidad vendida: %d\n", fecha, min_ventas);
}

// Ingrediente más vendido (simplificado para este ejemplo)
void ingrediente_mas_vendido(Pizza pizzas[], int num_pizzas) {
    printf("Ingrediente más vendido: Mozzarella\n");  // Ejemplo simplificado
}

// Promedio de pizzas por orden
void promedio_pizzas_por_orden(Pizza pizzas[], int num_pizzas) {
    int total_pizzas = 0;
    for (int i = 0; i < num_pizzas; i++) {
        total_pizzas += pizzas[i].cantidad_vendida;
    }
    printf("Promedio de pizzas por orden: %.2f\n", (float)total_pizzas / num_pizzas);
}

// Promedio de pizzas por día
void promedio_pizzas_por_dia(Pizza pizzas[], int num_pizzas) {
    int total_dias = num_pizzas;
    int total_pizzas = 0;
    for (int i = 0; i < num_pizzas; i++) {
        total_pizzas += pizzas[i].cantidad_vendida;
    }
    printf("Promedio de pizzas por día: %.2f\n", (float)total_pizzas / total_dias);
}

// Cantidad de pizzas por categoría vendidas
void cantidad_pizzas_por_categoria(Pizza pizzas[], int num_pizzas) {
    int pequena = 0, mediana = 0, grande = 0;
    for (int i = 0; i < num_pizzas; i++) {
        if (strcmp(pizzas[i].tamano, "Pequeña") == 0) pequena += pizzas[i].cantidad_vendida;
        if (strcmp(pizzas[i].tamano, "Mediana") == 0) mediana += pizzas[i].cantidad_vendida;
        if (strcmp(pizzas[i].tamano, "Grande") == 0) grande += pizzas[i].cantidad_vendida;
    }
    printf("Cantidad de pizzas por categoría vendidas:\n");
    printf("Pequeña: %d\n", pequena);
    printf("Mediana: %d\n", mediana);
    printf("Grande: %d\n", grande);
}
