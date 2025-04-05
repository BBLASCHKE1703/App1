CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
OBJS    = main.o metrics.o

all: pizzas

pizzas: $(OBJS)
	$(CC) $(CFLAGS) -o pizzas $(OBJS)

main.o: main.c pizza.h
	$(CC) $(CFLAGS) -c main.c

metrics.o: metrics.c pizza.h
	$(CC) $(CFLAGS) -c metrics.c

clean:
	rm -f *.o pizzas
