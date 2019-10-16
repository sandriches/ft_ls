/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   binary_path.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 18:23:01 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 15:25:47 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	binary_path(t_flags *data, va_list list)
{
	unsigned long long	storage;
	char				*tmpstring;

	storage = va_arg(list, unsigned long long);
	tmpstring = ft_long_long_itoa(storage);
	tmpstring = ft_change_base(tmpstring, 10, 2, 1);
	data->result = ft_malloc_copy(tmpstring);
	if (data->precision != 0)
		add_precision(data);
	data->result = make_width(data);
}
