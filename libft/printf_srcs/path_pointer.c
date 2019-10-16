/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_pointer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 15:48:17 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 15:48:29 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pointer_path_norminette(t_flags *data, char *str_to_add)
{
	if (data->precision > 0)
		add_precision(data);
	if ((data->flags & 1) == 1)
	{
		data->result = make_width(data);
		data->result = ft_strnjoin_free(str_to_add, data->result);
	}
	else
	{
		data->result = ft_strnjoin_free(str_to_add, data->result);
		data->result = make_width(data);
	}
}

void		pointer_path(t_flags *data, va_list list)
{
	unsigned long long	storage;
	char				*tmpstring;
	char				*str_to_add;

	str_to_add = ft_strnew(3);
	str_to_add[0] = '0';
	str_to_add[1] = 'x';
	storage = va_arg(list, unsigned long long);
	if (data->width > 1 && (data->flags & 1) == 1)
		data->width -= 2;
	tmpstring = ft_long_long_itoa(storage);
	tmpstring = ft_change_base_small(tmpstring, 10, 16, 1);
	data->result = tmpstring;
	if (storage == 0 && data->precision == -12)
		ft_strclr(data->result);
	pointer_path_norminette(data, str_to_add);
}
