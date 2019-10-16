/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_unsigned_int.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 10:29:20 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 14:50:27 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_tmpstring(t_flags *data, va_list list, char *tmp, int *zero)
{
	unsigned int		int_storage;
	unsigned long long	long_storage;

	if (data->length == 0)
	{
		int_storage = va_arg(list, unsigned int);
		*zero = (int_storage == 0) ? 1 : 0;
		tmp = ft_unsigned_itoa(int_storage);
	}
	else if ((data->length & 2) == 2 || (data->length & 1) == 1)
	{
		long_storage = va_arg(list, unsigned long long);
		*zero = (long_storage == 0) ? 1 : 0;
		tmp = ft_unsigned_long_long_itoa(long_storage);
	}
	return (tmp);
}

static char	*get_tmpstring_2(t_flags *data, va_list list, char *tmp, int *zero)
{
	unsigned short	short_storage;
	unsigned char	char_storage;
	uintmax_t		max_int_storage;

	if ((data->length & 4) == 4)
	{
		char_storage = va_arg(list, unsigned int);
		*zero = (char_storage == 0) ? 1 : 0;
		tmp = ft_unsigned_itoa(char_storage);
	}
	else if ((data->length & 8) == 8)
	{
		short_storage = va_arg(list, unsigned int);
		*zero = (short_storage == 0) ? 1 : 0;
		tmp = ft_unsigned_itoa(short_storage);
	}
	else if ((data->length & 32) == 32)
	{
		max_int_storage = va_arg(list, uintmax_t);
		*zero = (max_int_storage == 0) ? 1 : 0;
		tmp = ft_unsigned_long_long_itoa((unsigned long long)max_int_storage);
	}
	return (tmp);
}

void		unsigned_int_path(t_flags *data, va_list list)
{
	char	*tmpstring;
	int		zero;
	size_t	size_t_storage;

	zero = 0;
	tmpstring = 0;
	if ((data->length & 8) == 8 || (data->length & 4) == 4 \
		|| (data->length & 32) == 32)
		tmpstring = get_tmpstring_2(data, list, tmpstring, &zero);
	else if ((data->length & 64) == 64)
	{
		size_t_storage = va_arg(list, size_t);
		tmpstring = ft_unsigned_long_long_itoa(size_t_storage);
	}
	else
		tmpstring = get_tmpstring(data, list, tmpstring, &zero);
	data->result = tmpstring;
	if (data->precision == -12 && zero == 1)
		ft_strclr(data->result);
	if (data->precision != 0)
		add_precision(data);
	data->result = make_width(data);
}
