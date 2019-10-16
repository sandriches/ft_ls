/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_octal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 20:06:44 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/02 20:47:09 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_tmpstring(t_flags *data, va_list list,
char *tmpstring, int *zero_value)
{
	unsigned int		storage;
	unsigned long long	u_long_storage;
	uintmax_t			uint_storage;

	if (data->length == 0)
	{
		storage = va_arg(list, unsigned int);
		*zero_value = (storage == 0) ? 1 : 0;
		tmpstring = ft_long_itoa(storage);
	}
	else if ((data->length & 1) == 1 || (data->length & 2) == 2)
	{
		u_long_storage = va_arg(list, unsigned long long);
		*zero_value = (u_long_storage == 0) ? 1 : 0;
		tmpstring = ft_unsigned_long_long_itoa(u_long_storage);
	}
	else if ((data->length & 32) == 32)
	{
		uint_storage = va_arg(list, uintmax_t);
		*zero_value = (uint_storage == 0) ? 1 : 0;
		tmpstring = ft_unsigned_long_long_itoa(uint_storage);
	}
	return (tmpstring);
}

static char		*get_tmpstring_2(t_flags *data, va_list list,
char *tmpstring, int *zero_value)
{
	unsigned char	char_storage;
	unsigned short	short_storage;
	size_t			size_t_storage;

	if (data->length == 64)
	{
		size_t_storage = va_arg(list, size_t);
		*zero_value = (size_t_storage == 0) ? 1 : 0;
		tmpstring = ft_unsigned_long_itoa((unsigned long)size_t_storage);
	}
	else if ((data->length & 4) == 4)
	{
		char_storage = va_arg(list, unsigned int);
		*zero_value = (char_storage == 0) ? 1 : 0;
		tmpstring = ft_unsigned_itoa(char_storage);
	}
	else if ((data->length & 8) == 8)
	{
		short_storage = va_arg(list, unsigned int);
		*zero_value = (short_storage == 0) ? 1 : 0;
		tmpstring = ft_unsigned_itoa(short_storage);
	}
	return (tmpstring);
}

void			octal_path(t_flags *data, va_list list)
{
	char		*tmpstring;
	int			zero_value;

	tmpstring = 0;
	if (data->length == 64 || (data->length & 8) == 8 || \
		(data->length & 4) == 4)
		tmpstring = get_tmpstring_2(data, list, tmpstring, &zero_value);
	else
		tmpstring = get_tmpstring(data, list, tmpstring, &zero_value);
	tmpstring = ft_change_base(tmpstring, 10, 8, 1);
	data->result = tmpstring;
	if (data->precision == -12 && zero_value == 1)
		ft_strclr(data->result);
	if ((data->flags & 16) == 16 && zero_value == 0)
		data->result = ft_strjoin_free_char_left(data->result, '0');
	if (data->precision != 0)
		add_precision(data);
	data->result = make_width(data);
}
