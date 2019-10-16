/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 11:30:14 by kpereira       #+#    #+#                */
/*   Updated: 2019/05/03 20:58:18 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		send_struct_to_solve(t_flags *data, va_list list)
{
	if (data->specifier == 'c')
		char_path(data, list);
	else if (data->specifier == 's')
		string_path(data, list);
	else if (data->specifier == 'p')
		pointer_path(data, list);
	else if (data->specifier == 'd' || data->specifier == 'i')
		int_path(data, list);
	else if (data->specifier == 'o')
		octal_path(data, list);
	else if (data->specifier == 'u')
		unsigned_int_path(data, list);
	else if (data->specifier == 'X')
		hexa_path(data, list);
	else if (data->specifier == 'x')
		small_hexa_path(data, list);
	else if (data->specifier == 'b')
		binary_path(data, list);
	else if (data->specifier == 'f')
		float_path(data, list);
	else if (data->specifier == '%')
		percent_path(data);
	else
		null_path(data);
}

t_flags		*get_string_to_print(va_list list, const char *percent)
{
	t_flags		*data;

	data = make_struct_minus_result(list, (const char *)percent);
	if (!data)
		return (0);
	send_struct_to_solve(data, list);
	return (data);
}

int			ft_printf(const char *format, ...)
{
	va_list		list;
	int			result;
	char		*malloc_format;

	result = 0;
	malloc_format = ft_malloc_copy((char *)format);
	if (format)
	{
		va_start(list, format);
		malloc_format = search_for_colors(malloc_format);
		malloc_format = search_for_colors_2(malloc_format);
		if (!ft_strcmp(malloc_format, format))
			result = buff_management((char *)format, list);
		else
			result = buff_management(malloc_format, list);
		va_end(list);
		free(malloc_format);
		return (result);
	}
	return (0);
}
