# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Nome do executável
TARGET = huffman

# Arquivos fonte
SRCS = huffman.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos de compilação
clean:
	rm -f $(TARGET) $(OBJS)
