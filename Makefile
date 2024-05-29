CC = gcc
CFLAGS = -Wall
TARGET = banco
OBJS = banco.o fila.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

banco.o: banco.c fila.h
	$(CC) $(CFLAGS) -c banco.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

clean:
	rm -f *.o $(TARGET)
