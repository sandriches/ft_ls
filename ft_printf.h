/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/03 13:33:50 by kpereira       #+#    #+#                */
/*   Updated: 2019/07/08 12:09:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUF_SIZE 4096
# define LEN (data->len >= 1 ? data->len : ft_strlen(data->result))

# define FLAGSTRING			"+-# 0"
# define SEARCHSTRING		"1234567890+-# *"
# define LENGTHSTRING		"#+- *.1234567890"
# define NUMBERSTRING		"1234567890"
# define NO_0_NUMBERSTRING	"123456789"
# define FULLSTRING			"zjhlL#+- .*1234567890"
# define SPECIFIERS			"diouxXcspfb"
# define HEXSTRING			"1234567890ABCDEFabcdef"
# define COLORSTRING		"rRgGyYbBmMcC"

# define RED 				"\033[0;31m"
# define OUR_RED			"{red}"
# define BOLD_RED			"\033[1;31m"
# define OUR_BOLD_RED		"{RED}"
# define GREEN				"\033[0;32m"
# define OUR_GREEN			"{green}"
# define BOLD_GREEN			"\033[1;32m"
# define OUR_BOLD_GREEN		"{GREEN}"
# define YELLOW				"\033[0;33m"
# define OUR_YELLOW			"{yellow}"
# define BOLD_YELLOW		"\033[1;33m"
# define OUR_BOLD_YELLOW	"{YELLOW}"
# define BLUE				"\033[0;34m"
# define OUR_BLUE			"{blue}"
# define BOLD_BLUE			"\033[1;34m"
# define OUR_BOLD_BLUE		"{BLUE}"
# define MAGENTA			"\033[0;35m"
# define OUR_MAGENTA		"{magenta}"
# define BOLD_MAGENTA		"\033[1;35m"
# define OUR_BOLD_MAGENTA	"{MAGENTA}"
# define CYAN				"\033[0;36m"
# define OUR_CYAN			"{cyan}"
# define BOLD_CYAN			"\033[1;36m"
# define OUR_BOLD_CYAN		"{CYAN}"
# define COLOR_RESET		"\033[0m"
# define OUR_RESET			"{/}"

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h> // selihjzlshfdhgzdrhfflkzsuhlkuzhseflkfuhzselkfuhzselkfuhzkeufhzlkseufhzksuhfzklsueefhlzkssuhef (remove)
# include "./libft/libft.h"

/*
**				   16    8 4 2 1
** FLAGS: 	[0|0|0|0]	[0|0|0|0]
** 			[_|_|_|#]	[+|-| |0]
**
**			ft_value = ft_printf("%20.10f\t", 3.1415);
**
** 			   64 32 16      8 4  2 1
** Len: 	[0 |0| 0| 0]	[0|0 |0|0 ]
** 			[_ |z| j| L]	[h|hh|l|ll]
**
**				-42 PRECISION = precision of 0
**
** Bonuses:		wildcard
**				binary
**				colors
**				buffer[!]
**				jd, zd
*/

typedef struct		s_flags
{
	char			specifier;
	unsigned char	length;
	unsigned char	flags;
	int				width;
	int				precision;
	int				len;
	char			*result;
}					t_flags;

t_flags				*make_struct_minus_result(va_list list, const char \
*percent);
void				int_path(t_flags *data, va_list list);
void				percent_path(t_flags *data);
char				*ft_strnjoin_free(char *s1, char *s2);
char				*ft_strjoin_free_char(char *s1, char new_character);
char				*ft_malloc_copy(char *s1);
char				*ft_strjoin_free_char_left(char *s1, char new_character);
void				char_path(t_flags *data, va_list list);
void				string_path(t_flags *data, va_list list);
char				*ft_string_precision(t_flags *data);
char				*make_width(t_flags *data);
int					ft_strlen_numbers(char *str);
void				add_precision(t_flags *data);
void				unsigned_int_path(t_flags *data, va_list list);
void				octal_path(t_flags *data, va_list list);
char				*ft_change_base(char *nbr, int oldbase, int newbase, \
int is_long);
int					ft_get_decimal(char *str, int base);
long long int		ft_get_decimal_long(char *str, int base);
unsigned long		ft_get_decimal_unsigned_long(char *str, int base);
void				hexa_path(t_flags *data, va_list list);
int					ft_strlen_hex_numbers(char *str);
char				*ft_change_base_small(char *nbr, int oldbase, int newbase, \
int is_long);
void				small_hexa_path(t_flags *data, va_list list);
void				pointer_path(t_flags *data, va_list list);
void				binary_path(t_flags *data, va_list list);
void				float_path(t_flags *data, va_list list);
char				*ft_unsigned_long_long_itoa(unsigned long long int n);
char				*ft_unsigned_itoa(unsigned int n);
char				*ft_max_int_itoa(intmax_t n);
void				null_path(t_flags *data);
int					buff_management(char *format, va_list list);
t_flags				*get_string_to_print(va_list list, const char *percent);
char				*ft_strrpl(char *haystack, int index, int replaced_length, \
char *needle);
char				*search_for_colors(char *str);
char				*search_for_colors_2(char *str);
int					ft_search_until_specifier(char *str, t_flags *data);
int					find_wildcard_in_string(char *str);
char				*make_width_null(t_flags *data);
void				clear_buf(char *buf);
int					print_buf(char *buf, int *buffer_length);
int					print_buf_nf(char *buf, int j, t_flags *data, int *buffer_length);
int					put_on_buf(char *buf, t_flags *data, int *rtn, int len, int *buffer_length);
char				*ft_unsigned_long_long_itoa(unsigned long long int n);
void				width_path_flags(t_flags *data, char *rtn);
void				width_fzero_path(char *str, int width, char *rtn);
void				width_min_path(char *str, int width, char *rtn);
void				width_zero_path(char *str, int width, char *rtn);
void				width_nothing(char *str, int width, char *rtn);
int					get_width(char *percent, va_list list, unsigned char \
*flags);
int					get_precision(char *percent, va_list list, int i, \
t_flags *data);
int					ft_printf(const char *format, ...);

#endif
