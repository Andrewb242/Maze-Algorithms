# Compiler
CC = gcc

# Compiler flags: enable warnings, use C11 standard, optimize.
CFLAGS = -Wall -Wextra -std=c11 -O2

# Source files: include eller.c which now has arguments and any other sources like set.c.
SRCS = maze.c set.c pos.c eller.c backtrack.c kruskal.c

# Object files: automatically derived from source file names.
OBJS = $(SRCS:.c=.o)

# The target executable name.
TARGET = maze

# Default target: build the executable.
all: $(TARGET)

# Link object files to create the executable.
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c files into .o files.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# A "debug" target that will allow debugging
debug: CFLAGS += -g
debug: $(TARGET)
	@echo "Starting gdb..."
	gdb --args ./$(TARGET) $(ARGS)


# A "run" target that passes default command-line arguments (modify as needed).
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Clean up generated files.
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run

