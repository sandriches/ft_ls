/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_int.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 14:10:40 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 15:30:51 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_tmpstring(t_flags *data, va_list list, char *tmpstring)
{
	int			int_storage;
	long		long_storage;
	long long	long_long_storage;

	if (data->length == 0)
	{
		int_storage = va_arg(list, int);
		tmpstring = ft_itoa(int_storage);
	}
	else if ((data->length & 1) == 1)
	{
		long_long_storage = va_arg(list, long long);
		tmpstring = ft_long_long_itoa(long_long_storage);
	}
	else if ((data->length & 2) == 2)
	{
		long_storage = va_arg(list, long);
		tmpstring = ft_long_long_itoa(long_storage);
	}
	return (tmpstring);
}

static char		*get_tmpstring_2(t_flags *data, va_list list, char *tmpstring)
{
	short		short_storage;
	char		char_storage;
	intmax_t	max_int_storage;

	if ((data->length & 4) == 4)
	{
		char_storage = va_arg(list, int);
		tmpstring = ft_itoa(char_storage);
	}
	else if ((data->length & 8) == 8)
	{
		short_storage = va_arg(list, int);
		tmpstring = ft_itoa(short_storage);
	}
	else if ((data->length & 32) == 32)
	{
		max_int_storage = va_arg(list, intmax_t);
		tmpstring = ft_max_int_itoa(max_int_storage);
	}
	return (tmpstring);
}

static void		int_path_norminette(t_flags *data, int sign)
{
	if (!ft_strchr(data->result, '-'))
		sign = 1;
	if (!ft_strcmp("0", data->result) && data->precision == -12)
		ft_strclr(data->result);
	if (data->precision != 0)
		add_precision(data);
	if ((data->flags & 2) == 2 && sign == 1 && (data->flags & 8) != 8)
		data->result = ft_strjoin_free_char_left(data->result, ' ');
	if ((data->flags & 8) == 8 && sign == 1)
		data->result = ft_strjoin_free_char_left(data->result, '+');
	data->result = make_width(data);
}

void			int_path(t_flags *data, va_list list)
{
	char		*tmpstring;
	int			sign;
	size_t		size_t_storage;

	tmpstring = 0;
	if ((data->length & 4) == 4 || (data->length & 8) == 8 || \
		(data->length & 32) == 32)
		tmpstring = get_tmpstring_2(data, list, tmpstring);
	else if ((data->length & 64) == 64)
	{
		size_t_storage = va_arg(list, size_t);
		tmpstring = ft_long_itoa(size_t_storage);
	}
	else
		tmpstring = get_tmpstring(data, list, tmpstring);
	sign = -1;
	data->result = tmpstring;
	if (!ft_strchr(data->result, '-'))
		sign = 1;
	int_path_norminette(data, sign);
}
