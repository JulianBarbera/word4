CC = gcc
CFLAGS = -Wall -g -O3
TARGET = word4
SOURCES = src/main.c src/io.c src/data.c src/calculations.c
OBJECTS = $(SOURCES:.c=.o)
LIBS = -lm

all: $(TARGET)

run: $(TARGET)
		./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
