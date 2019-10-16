/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buff_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/21 16:10:15 by kpereira       #+#    #+#                */
/*   Updated: 2019/05/04 19:23:07 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	reset_j(int *j, int *rtn, char *buf, int *buffer_length)
{
	*rtn += print_buf(buf, buffer_length);
	*j = 0;
}

static void	assign_char_to_buf(char *buf, char *format, int *j, int i)
{
	buf[*j] = format[i];
	*j += 1;
}

static void	assign_int_zero(int *i, char *str, t_flags **data)
{
	*i = 0;
	i++;
	*i = 0;
	i++;
	*i = 0;
	i++;
	*i = 0;
	i++;
	*i = 0;
	clear_buf(str);
	*data = 0;
}

static void	free_data(t_flags **data)
{
	if (data)
	{
		free(*data);
		*data = NULL;
	}
}

int			buff_management(char *format, va_list list)
{
	t_flags	*data;
	char	buf[BUF_SIZE + 1];
	int		i[5];

	assign_int_zero(&i[0], buf, &data);
	while (format[i[0]] != '\0')
	{
		if (i[1] == BUF_SIZE)
			reset_j(&i[1], &i[2], buf, &i[3]);
		if (format[i[0]] == '%' && format[i[0] + 1])
		{
			data = get_string_to_print(list, (const char *)&format[i[0]]);
			if (!data)
				break ;
			i[4] = (data->len >= 1 ? data->len : ft_strlen(data->result));
			i[1] = (i[1] + i[4]) % BUF_SIZE;
			i[2] += put_on_buf(buf, data, i, i[4]);
			i[0] += ft_search_until_specifier(&format[i[0]], data);
			free_data(&data);
		}
		else if (format[i[0]] != '%')
			assign_char_to_buf(buf, format, &i[1], i[0]);
		i[0]++;
	}
	return (i[2] += print_buf_nf(buf, i[1], data, &i[3]));
}
