# Compiler and flags
CC = gcc
CFLAGS = -I./raylib-5.5_linux_amd64/include
LDFLAGS = ./raylib-5.5_linux_amd64/lib/libraylib.a -lm -ldl -lpthread -lGL -lrt -lX11

# Output binary name
TARGET = mandelbrot

# Source files
SRC = main.c

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
