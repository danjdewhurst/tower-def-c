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

format:
	clang-format -i $(SOURCES) src/*.h

format-check:
	clang-format --dry-run --Werror $(SOURCES) src/*.h

lint:
	/opt/homebrew/opt/llvm/bin/clang-tidy $(SOURCES) -- $(CFLAGS)

analyze:
	clang --analyze $(CFLAGS) $(SOURCES)

debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

release: CFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

.PHONY: all clean run format format-check lint analyze debug release