CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lraylib -lm

TARGET = tower_defense
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run