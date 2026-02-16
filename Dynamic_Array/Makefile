CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Werror

SRC = Dynamic.c
OBJ = $(SRC:.c=.o)
TARGET = ArrayList

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

