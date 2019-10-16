/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_null.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/26 22:21:58 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/03 19:59:36 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	null_path(t_flags *data)
{
	data->result = 0;
	if (data->specifier)
		data->result = ft_strdup(&data->specifier);
	if (data->precision >= 0)
		add_precision(data);
	if (data->width > 0)
		data->result = make_width(data);
}
