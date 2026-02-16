CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Werror

SRC = Dynamic_Array.c
OBJ = $(SRC:.c=.o)
TARGET = ArrayList

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)



