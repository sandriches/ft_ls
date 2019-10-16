# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcorke <rcorke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/23 10:33:18 by rcorke         #+#    #+#                 #
#    Updated: 2019/10/16 15:12:00 by rcorke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME=ft_ls

FLAGS= -Wall -Wextra -Werror

SRCS= ft_ls.c print_functions.c utility_functions.c free_functions.c \
flags_and_error.c add_to_dir_list.c list_functions.c print_dirent.c \
merge_sort_list.c merge_compare_values.c print_first_dirent.c get_rel_time.c

LIBFT= libft/libft.a

OBJECTS:=${SRCS:c=o}

all: $(NAME)

$(NAME):
	@echo 'Making Libft && ft_printf...'
	make -C libft/
	@echo 'Making ft_ls...'
	gcc -c $(FLAGS) $(SRCS)
	gcc $(OBJECTS) $(LIBFT) -o $(NAME)
	@echo 'Success'

clean:
	make clean -C libft/
	rm -rf $(OBJECTS)
	rm -rf *~

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: make re clean all
