# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mrjvs <mrjvs@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/14 16:00:56 by mrjvs         #+#    #+#                  #
#    Updated: 2020/09/23 16:27:29 by mrjvs         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=philo_two
CC=gcc
FLAGS=-pthread -Werror -Wall -Wextra

HEADERS=./philosophers.h
INCLUDES=./

SOURCES=\
	main.c \
	logger.c \
	starter.c \
	state.c \
	time.c \
	action.c \
	starve.c \
	parse.c \
	destroy.c

OBJ=$(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I $(INCLUDES) -o $@ $(OBJ)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -I $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
