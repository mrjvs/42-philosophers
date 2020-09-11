NAME=phil
CC=gcc
FLAGS=-pthread -g

INCLUDES=includes

SOURCES=\
	main.c \
	philosophers/entry.c \
	philosophers/action.c \
	philosophers/logger.c \
	state/has_died.c \
	boot/starter.c

OBJ=$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I $(INCLUDES) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -I $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
