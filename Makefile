
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = main.c mem.c

# Object files
OBJS = $(SRCS:.c=.o)

# Library path
LIB_PATH = ./build

# Library name
LIB_NAME = lib65816.a

# Include directories
INCLUDES = -Ilib65816 -I.

# Output executable
TARGET = emu65816

# Link the object files and library to create the executable
all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIB_PATH)/$(LIB_NAME)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)