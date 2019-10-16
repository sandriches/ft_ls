# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcorke <rcorke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/09 18:10:06 by rcorke         #+#    #+#                 #
#    Updated: 2019/10/15 13:32:51 by rcorke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= libftprintf.a
SOURCES= bonus_colors.c buff_manager.c flags_precision.c flags_struct.c \
		flags_width.c ft_change_base.c ft_change_base_small.c \
		ft_get_decimal.c ft_get_decimal_long.c \
		ft_get_decimal_unsigned_long.c ft_get_flags.c ft_printf.c \
		ft_search_until_specifier.c ft_strjoin_free.c \
		ft_strlen_numbers.c ft_strrpl.c ft_unsigned_itoa.c \
		ft_wildcard_in_string.c binary_path.c path_char.c path_char_hexa.c \
		path_float.c path_hexa.c path_int.c path_null.c path_octal.c \
		path_percent.c path_pointer.c path_small_hexa.c path_string.c \
		path_unsigned_int.c buff_manager_2.c \
		ft_unsigned_long_long_itoa.c flags_width_tools.c \
		flags_struct_2.c
PRINTF_OBJS= $(SOURCES:.c=.o)
export PRINTF_OBJS
LIBFT= no_printf_libft.a
FLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -I./ -c $(SOURCES)
	@ar rc $(NAME) $(PRINTF_OBJS)
	@ranlib $(NAME)

clean:
	@rm -rf *~ $(PRINTF_OBJS)
	@rm -rf a.out
	@rm -rf .DS_Store

fclean: clean
	@rm -rf $(NAME)

re: fclean all

poop:
	@echo poop

pee:
	@echo pee
