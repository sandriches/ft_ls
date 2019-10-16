/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_char_hexa.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 16:45:21 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 17:28:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_tmpstring(t_flags *data, va_list list, char *tmpstring)
{
	int		storage;
	long	long_storage;

	if (data->length == 0 || (data->length & 8) == 8 || (data->length & 4) == 4)
	{
		storage = va_arg(list, unsigned int);
		tmpstring = ft_long_itoa(storage);
	}
	else if ((data->length & 1) == 1 || (data->length & 2) == 2)
	{
		long_storage = va_arg(list, unsigned long);
		tmpstring = ft_unsigned_long_itoa(long_storage);
	}
	return (tmpstring);
}

void		hexa_char_path(t_flags *data, va_list list)
{
	char	*tmpstring;

	tmpstring = 0;
	tmpstring = get_tmpstring(data, list, tmpstring);
	tmpstring = ft_change_base(tmpstring, 10, 16, 1);
	data->result = tmpstring;
	if ((data->flags & 16) == 16)
		data->result = ft_strjoin_free_char_left(data->result, '0');
	if (data->precision != 0)
		add_precision(data);
	if ((data->flags & 2) == 2 && (data->flags & 8) != 8 && (data->flags & 16) \
	!= 16)
		data->result = ft_strjoin_free_char_left(data->result, ' ');
	if ((data->flags & 8) == 8 && (data->flags & 2) != 2 && (data->flags & 16) \
	!= 16)
		data->result = ft_strjoin_free_char_left(data->result, '+');
	data->result = make_width(data);
}
