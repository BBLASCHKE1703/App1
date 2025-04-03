#include "pizza.h"

int main(int argc, char *argv[]) {
    Pizza pizzas[100];
    int num_pizzas;

    // Cargar pizzas desde el archivo CSV
    cargar_pizzas(pizzas, &num_pizzas);

    // Si no se pasa ningún comando, mostrar el menú
    if (argc < 2) {
        menu();
        return 0;
    }

    // Mostrar estadísticas según el comando pasado como argumento
    mostrar_estadisticas(pizzas, num_pizzas, argv[1]);
    return 0;
}
