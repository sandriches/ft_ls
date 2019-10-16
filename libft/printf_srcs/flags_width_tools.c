/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_width_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 17:26:49 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/04 14:42:58 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		width_path_normal(t_flags *data, char *rtn)
{
	if ((data->flags & 4) == 4)
		width_min_path(data->result, data->width, rtn);
	else if ((data->flags & 1) == 1 && data->precision < 0 && \
	data->result[0] != '\0')
		width_zero_path(data->result, data->width, rtn);
	else
		width_nothing(data->result, data->width, rtn);
}

static void		width_path_string(t_flags *data, char *rtn)
{
	if ((data->flags & 4) == 4)
		width_min_path(data->result, data->width, rtn);
	else if ((data->flags & 1) == 1)
		width_zero_path(data->result, data->width, rtn);
	else
		width_nothing(data->result, data->width, rtn);
}

char			*make_width_null(t_flags *data)
{
	char	*rtn;
	int		i;

	i = 1;
	rtn = ft_strnew(data->width);
	while (i < data->width + 1)
	{
		rtn[i] = ' ';
		i++;
	}
	return (rtn);
}

char			*make_width(t_flags *data)
{
	int		str_len;
	char	*rtn;

	str_len = ft_strlen(data->result);
	rtn = 0;
	if (str_len < data->width)
	{
		rtn = ft_strnew(data->width + 1);
		if (data->result && (data->result[0] == '-' || data->result[0] == \
		'+' || data->result[0] == ' '))
			width_path_flags(data, rtn);
		else
		{
			if (data->specifier == 's')
				width_path_string(data, rtn);
			else
				width_path_normal(data, rtn);
		}
		ft_strdel(&data->result);
		return (rtn);
	}
	free(rtn);
	return (data->result);
}
