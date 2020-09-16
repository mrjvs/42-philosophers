# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mrjvs <mrjvs@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/14 16:00:56 by mrjvs         #+#    #+#                  #
#    Updated: 2020/09/16 15:59:37 by mrjvs         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=phil
CC=gcc
FLAGS=-pthread -Werror -Wall -Wextra -g

INCLUDES=./

SOURCES=\
	main.c \
	logger.c \
	starter.c \
	state.c \
	time.c \
	action.c \
	starve.c

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
