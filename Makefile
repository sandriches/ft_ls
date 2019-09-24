# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcorke <rcorke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/23 10:33:18 by rcorke         #+#    #+#                 #
#    Updated: 2019/09/23 11:28:16 by rcorke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME=ft_ls

FLAGS= -Wall -Werror -Wextra

SRCS= ft_ls.c

OBJECTS:=${SRCS:c=o}

all: $(NAME)

$(NAME):
	gcc -c $(SRCS)
	gcc $(OBJECTS) libftprintf.a -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf *~

fclean: clean
	rm -rf $(NAME)

re: fclean all
