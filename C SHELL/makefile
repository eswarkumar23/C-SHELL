# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = mysh

# Source files
SRCS = main.c display.c utils.c builtin.c echo.c pwd.c cd.c history.c \
       execute.c redirection.c signals.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = shell.h display.h utils.h builtin.h history.h execute.h \
          redirection.h signals.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
