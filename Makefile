NAME=phil
CC=gcc
FLAGS=-pthread -g

INCLUDES=includes

SOURCES=\
	main.c \
	philosophers/entry.c \
	philosophers/action.c \
	philosophers/logger.c \
	philosophers/starve.c \
	philosophers/communication-shared.c \
	utils/string.c \
	utils/int.c \
	starters/thread.c \
	boot/starter.c \
	boot/arg_parse.c

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
