# Compiler and flags
CC = gcc
IFLAGS = -I./raylib-5.5_linux_amd64/include
CFLAGS = -Wall -Wextra -O2
LDFLAGS = ./raylib-5.5_linux_amd64/lib/libraylib.a -lm -ldl -lpthread -lGL -lrt -lX11

# Output binary name
TARGET = mandelbrot

# Source files
SRC = main.c

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(IFLAGS) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
