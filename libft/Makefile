# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcorke <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/19 18:09:35 by rcorke         #+#    #+#                 #
#    Updated: 2019/10/14 17:50:24 by rcorke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME = libft.a

LIBFT=libft_srcs/only_libft.a

PRINTF=printf_srcs/libftprintf.a

MAKEFLAGS += --silent

LIBMAKER = ar rc

all: $(NAME)

$(NAME):
	make -C libft_srcs/
	make -C printf_srcs/
	ar -x $(LIBFT)
	ar -x $(PRINTF)
	ar -rc $(NAME) *.o
	ranlib $(NAME)

clean:
	make clean -C libft_srcs/
	make clean -C printf_srcs/
	rm -rf *~
	rm -rf *.o
	rm -rf __.SYMDEF\ SORTED
	rm -rf a.out

fclean: clean
	make fclean -C libft_srcs/
	make fclean -C printf_srcs/
	rm -f $(NAME)

re: fclean all
	make re -C libft_srcs/
	make re -C printf_srcs/

.PHONY: all clean fclean re
