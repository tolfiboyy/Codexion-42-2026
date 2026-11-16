# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asavidan <asavidan@learner.42.tech>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/03 12:46:40 by asavidan          #+#    #+#              #
#    Updated: 2026/11/03 12:51:00 by asavidan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

