/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_small_hexa.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:29:08 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 14:43:42 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*make_str_to_add(void)
{
	char *rtnstring;

	rtnstring = ft_strnew(3);
	rtnstring[0] = '0';
	rtnstring[1] = 'x';
	return (rtnstring);
}

static char		*get_tmpstring(t_flags *data, va_list list, char *tmpstring,
int *zero_value)
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

static char		*get_tmpstring_2(t_flags *data, va_list list, char *tmpstring,
int *zero_value)
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

static void		flags_hexa(t_flags *data)
{
	if ((data->flags & 1) == 1)
	{
		if ((data->flags & 16) == 16 && ((data->precision == -12 || \
		data->precision == 0) || (data->precision > 0 && \
		data->precision < data->width)))
		{
			data->flags -= 1;
			data->result = ft_strnjoin_free(make_str_to_add(), \
			data->result);
			data->result = make_width(data);
		}
		else
		{
			data->width = (data->width >= 2) ? data->width - 2 \
			: data->width;
			data->result = make_width(data);
			data->result = ft_strnjoin_free(make_str_to_add(), \
			data->result);
		}
	}
	else
	{
		data->result = ft_strnjoin_free(make_str_to_add(), data->result);
		data->result = make_width(data);
	}
}

void			small_hexa_path(t_flags *data, va_list list)
{
	char			*tmpstring;
	int				zero_value;

	tmpstring = 0;
	if (data->length == 64 || (data->length & 8) == 8 || \
		(data->length & 4) == 4)
		tmpstring = get_tmpstring_2(data, list, tmpstring, &zero_value);
	else
		tmpstring = get_tmpstring(data, list, tmpstring, &zero_value);
	tmpstring = ft_change_base_small(tmpstring, 10, 16, 1);
	ft_strdel(&data->result);
	data->result = tmpstring;
	if (data->precision == -12 && zero_value == 1)
		ft_strclr(data->result);
	if (data->precision != 0)
		add_precision(data);
	if ((data->flags & 16) == 16 && zero_value == 0)
		flags_hexa(data);
	else
		data->result = make_width(data);
}
