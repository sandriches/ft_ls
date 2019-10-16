/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_width.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 16:16:36 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/02 20:46:53 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** width with -
** width with 0
** width with nothing
*/

void	width_nothing(char *str, int width, char *rtn)
{
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < width - str_len)
	{
		rtn[i] = ' ';
		i++;
	}
	rtn[i] = '\0';
	ft_strcat(rtn, str);
}

void	width_zero_path(char *str, int width, char *rtn)
{
	int		i;
	int		str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < width - str_len)
	{
		rtn[i] = '0';
		i++;
	}
	rtn[i] = '\0';
	ft_strcat(rtn, str);
}

void	width_min_path(char *str, int width, char *rtn)
{
	int		str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(str);
	while (i < str_len)
	{
		rtn[i] = str[i];
		i++;
	}
	while (i < width)
	{
		rtn[i] = ' ';
		i++;
	}
	rtn[i] = '\0';
}

void	width_fzero_path(char *str, int width, char *rtn)
{
	int		i;
	int		str_len;

	i = 1;
	rtn[0] = str[0];
	str_len = ft_strlen(str) - 1;
	while (i < width - str_len)
	{
		rtn[i] = '0';
		i++;
	}
	rtn[i] = '\0';
	str++;
	ft_strcat(rtn, str);
}

void	width_path_flags(t_flags *data, char *rtn)
{
	if ((data->flags & 4) == 4)
		width_min_path(data->result, data->width, rtn);
	else if ((data->flags & 1) == 1 && data->precision <= 0)
		width_fzero_path(data->result, data->width, rtn);
	else
		width_nothing(data->result, data->width, rtn);
}
