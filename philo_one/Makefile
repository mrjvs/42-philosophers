# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mrjvs <mrjvs@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/14 16:00:56 by mrjvs         #+#    #+#                  #
#    Updated: 2020/09/14 16:03:59 by mrjvs         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=phil
CC=gcc
FLAGS=-pthread -g

INCLUDES=./

SOURCES=\
	main.c \
	philosopher/entry.c \
	philosopher/action.c \
	philosopher/logger.c \
	philosopher/starve.c \
	philosopher/lock.c \
	philosopher/communication.c \
	philosopher/starter.c \
	utils.c \
	args.c

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