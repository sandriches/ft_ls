/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_char.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 15:58:35 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/03 20:00:32 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_path(t_flags *data, va_list list)
{
	int			storage;
	char		tmpstring;

	storage = va_arg(list, int);
	if (!storage)
	{
		data->precision = -21;
		data->result = ft_strnew(0);
		data->len = (data->width < 1) ? 1 : data->width;
		data->width -= 1;
	}
	else
	{
		tmpstring = (char)storage;
		data->result = ft_strnew(1);
		data->result[0] = tmpstring;
	}
	if ((data->flags & 4) == 4 && data->len > 1)
		data->result = make_width_null(data);
	else
		data->result = make_width(data);
}
