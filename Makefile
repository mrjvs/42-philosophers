NAME=phil
CC=gcc
FLAGS=

SOURCES=\
	main.c

OBJ=$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) -c -o $@ $<
