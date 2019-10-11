# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcorke <rcorke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/23 10:33:18 by rcorke         #+#    #+#                 #
#    Updated: 2019/10/11 13:32:49 by rcorke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME=ft_ls

FLAGS= -Wall -Werror -Wextra

SRCS= ft_ls.c print_functions.c utility_functions.c free_functions.c \
flags_and_error.c add_to_dir_list.c list_functions.c print_dirent.c \
merge_sort_list.c

OBJECTS:=${SRCS:c=o}

all: $(NAME)

$(NAME):
	gcc -g $(SRCS) libftprintf.a -o $(NAME)
#	gcc $(OBJECTS) libftprintf.a -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf *~

fclean: clean
	rm -rf $(NAME)

re: fclean all

poop:
	yes poop

#.PHONY: make re clean all
