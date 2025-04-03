cmake_minimum_required(VERSION 3.10)
project(Pizzeria)

set(CMAKE_C_STANDARD 99)

# Añadir los archivos fuente en la carpeta 'src'
set(SOURCES
        src/main.c
        src/pizza.c
)

# Crear el ejecutable a partir de los archivos fuente
add_executable(pizzeria ${SOURCES})

# Incluir la carpeta 'src' donde se encuentran los archivos .h y .c
include_directories(src)
