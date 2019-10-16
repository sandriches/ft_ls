/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_struct_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 17:32:13 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/03 13:39:35 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		do_first_if(va_list list, char *percent, int i)
{
	int storage;
	int rtn;

	rtn = 0;
	storage = va_arg(list, int);
	i++;
	while (ft_strchr(NUMBERSTRING, percent[i]))
	{
		rtn = rtn * 10 + (percent[i] - 48);
		i++;
	}
	return (rtn);
}

static int		do_second_if(va_list list, unsigned char **flags)
{
	int storage;

	storage = va_arg(list, int);
	if (storage < 0)
	{
		if ((**flags & 4) != 4)
			**flags += 4;
		return (storage * -1);
	}
	return (storage);
}

int				get_width(char *percent, va_list list, unsigned char *flags)
{
	int i;
	int rtn;

	i = 1;
	rtn = 0;
	while (ft_strchr(FLAGSTRING, percent[i]))
		i++;
	if (percent[i] == '*' && percent[i + 1] && percent[i + 1] >= \
	'0' && percent[i + 1] <= '9')
		return (do_first_if(list, percent, i));
	if (find_wildcard_in_string(&percent[i]) > -1)
		return (do_second_if(list, &flags));
	while (ft_strchr(NUMBERSTRING, percent[i]))
	{
		rtn = rtn * 10 + (percent[i] - 48);
		i++;
	}
	return (rtn);
}

static int		first_precision_if(va_list list, t_flags *data)
{
	int storage;

	storage = va_arg(list, int);
	if (storage < 0)
		data->flags += 32;
	return (storage);
}

int				get_precision(char *percent, va_list list, int i, t_flags *data)
{
	int rtn;

	rtn = 0;
	i = 1;
	while (ft_strchr(SEARCHSTRING, percent[i]))
		i++;
	if (percent[i] == '.')
	{
		i++;
		if (find_wildcard_in_string(&percent[i]) > -1)
			return (first_precision_if(list, data));
		while (ft_strchr(NUMBERSTRING, percent[i]))
		{
			rtn = rtn * 10 + (percent[i] - 48);
			i++;
		}
		if (rtn == 0 && (data->specifier != 'o' || \
		(data->specifier == 'o' && (data->flags & 16) != 16)))
			rtn = -12;
	}
	else
		rtn = -42;
	return (rtn);
}
