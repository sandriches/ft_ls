/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_struct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 17:31:25 by kpereira       #+#    #+#                */
/*   Updated: 2019/05/02 17:40:05 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_spcs(char *percent, int len)
{
	int		i;

	i = 1;
	while (i < len)
	{
		if (ft_strchr(SPECIFIERS, percent[i]))
			return (0);
		i++;
	}
	return (1);
}

char			get_specifier(char *percent)
{
	int		i;
	int		y;

	i = 1;
	y = 1;
	while (percent[i] && ft_strchr(FULLSTRING, percent[i]))
		i++;
	if (ft_strchr(SPECIFIERS, percent[i]))
		return (percent[i]);
	while (percent[y] && ft_strchr(LENGTHSTRING, percent[y]))
		y++;
	if (!percent[y])
		return (-1);
	else if (check_spcs(percent, y))
	{
		i = 1;
		while (ft_strchr(LENGTHSTRING, percent[i]))
			i++;
		return (percent[i]);
	}
	return (0);
}

unsigned char	get_length(char *percent, t_flags *data)
{
	int		i;

	i = 1;
	while (ft_strchr(LENGTHSTRING, percent[i]))
		i++;
	if (percent[i] == 'h' && percent[i + 1] && percent[i + 1] == 'h' && \
	(ft_strchr("diouxX", data->specifier)))
		return (4);
	else if (percent[i] == 'h' && (ft_strchr("diouxX", data->specifier)))
		return (8);
	else if (percent[i] == 'l' && percent[i + 1] && percent[i + 1] == 'l' \
	&& (ft_strchr("diouxXs", data->specifier)))
		return (1);
	else if (percent[i] == 'l' && (ft_strchr("diouxXs", data->specifier)))
		return (2);
	else if (percent[i] == 'L' && data->specifier == 'f')
		return (16);
	else if (percent[i] == 'j' && (ft_strchr("diouxX", data->specifier)))
		return (32);
	else if (percent[i] == 'z' && (ft_strchr("diouxX", data->specifier)))
		return (64);
	else
		return (0);
}

unsigned char	get_flags(char *percent)
{
	unsigned char	rtn;
	int				i;

	rtn = 0;
	i = 1;
	while (ft_strchr(FLAGSTRING, percent[i]))
	{
		if (percent[i] == '#' && (rtn & 16) != 16)
			rtn += 16;
		if (percent[i] == '+' && (rtn & 8) != 8)
			rtn += 8;
		if (percent[i] == '-' && (rtn & 4) != 4)
			rtn += 4;
		if (percent[i] == ' ' && (rtn & 2) != 2)
			rtn += 2;
		if (percent[i] == '0' && (rtn & 1) != 1)
			rtn += 1;
		i++;
	}
	return (rtn);
}

t_flags			*make_struct_minus_result(va_list list, const char *percent)
{
	t_flags		*options;

	options = (t_flags *)malloc(sizeof(t_flags));
	options->specifier = get_specifier((char *)percent);
	if (options->specifier == -1)
		return (0);
	options->length = get_length((char *)percent, options);
	options->flags = get_flags((char *)percent);
	options->width = get_width((char *)percent, list, &options->flags);
	options->precision = get_precision((char *)percent, list, 1, options);
	options->len = 0;
	options->result = NULL;
	return (options);
}
