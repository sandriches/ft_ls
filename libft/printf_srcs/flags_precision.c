/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_precision.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 13:43:58 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 15:42:29 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	reset_ints(int *i)
{
	*i = 1;
	i++;
	*i = 1;
}

static char	*add_0s_to_neg_string(char *str, int spaces, char is_hex)
{
	char	*rtnstring;
	int		length;
	int		x[2];

	length = ft_strlen(str) + spaces + 1;
	rtnstring = ft_strnew(length + 1);
	rtnstring[0] = '-';
	reset_ints(x);
	if (is_hex == 'x' || is_hex == 'X')
		length = spaces - ft_strlen_hex_numbers(str);
	else
		length = spaces - ft_strlen_numbers(str);
	while (x[0] <= length)
	{
		rtnstring[x[0]] = '0';
		x[0]++;
	}
	while (str[x[1]] != '\0')
	{
		rtnstring[x[0]] = str[x[1]];
		x[0]++;
		x[1]++;
	}
	free(str);
	return (rtnstring);
}

static char	*add_0s_to_pos_string(char *str, int spaces, char is_hex)
{
	char	*rtnstring;
	int		length;
	int		x[2];

	length = ft_strlen(str) + spaces + 1;
	rtnstring = ft_strnew(length + 1);
	x[0] = 0;
	x[1] = 0;
	if (is_hex == 'x' || is_hex == 'X' || is_hex == 'p')
		length = spaces - ft_strlen_hex_numbers(str);
	else
		length = spaces - ft_strlen_numbers(str);
	while (x[0] < length)
	{
		rtnstring[x[0]] = '0';
		x[0]++;
	}
	while (str[x[1]] != '\0')
	{
		rtnstring[x[0]] = str[x[1]];
		x[0]++;
		x[1]++;
	}
	free(str);
	return (rtnstring);
}

char		*ft_string_precision(t_flags *data)
{
	int		current_length;
	int		x;

	x = data->precision;
	current_length = ft_strlen(data->result);
	if (current_length > data->precision)
	{
		data->result[x] = '\0';
	}
	return (data->result);
}

void		add_precision(t_flags *data)
{
	int		num_length;

	if ((data->flags & 32) != 32)
	{
		if (data->precision < 0)
			return ;
		if (data->specifier == 'x' || data->specifier == 'X' || \
		data->specifier == 'p')
			num_length = ft_strlen_hex_numbers(data->result);
		else
			num_length = ft_strlen_numbers(data->result);
		if (num_length < data->precision)
		{
			if (ft_strchr(data->result, '-'))
				data->result = add_0s_to_neg_string(data->result, \
				data->precision, data->specifier);
			else
			{
				data->result = add_0s_to_pos_string(data->result, \
				data->precision, data->specifier);
			}
		}
	}
}
