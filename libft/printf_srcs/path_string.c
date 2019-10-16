/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_string.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 15:15:59 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/02 17:59:47 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string_path(t_flags *data, va_list list)
{
	char		*tmpstring;
	int			tempint;

	if ((data->length & 2) != 2)
		tmpstring = va_arg(list, char *);
	else
	{
		tempint = va_arg(list, int);
		data->result = ft_strnew(0);
		return ;
	}
	if (!tmpstring)
	{
		data->result = ft_strdup("(null)");
		ft_strdel(&tmpstring);
	}
	else
		data->result = ft_malloc_copy(tmpstring);
	if (data->precision >= 0)
		data->result = ft_string_precision(data);
	else if (data->precision == -12)
		ft_strclr(data->result);
	data->result = make_width(data);
}
