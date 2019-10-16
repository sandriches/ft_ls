/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buff_manager_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 15:34:03 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/04 14:58:32 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		clear_buf(char *buf)
{
	int i;

	i = 0;
	while (i < BUF_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
}

int			print_buf(char *buf, int *buffer_length)
{
	write(1, buf, BUF_SIZE);
	clear_buf(buf);
	*buffer_length = 0;
	return (BUF_SIZE);
}

int			print_buf_nf(char *buf, int j, t_flags *data, int *buffer_length)
{
	write(1, &buf[0], j);
	clear_buf(buf);
	free(data);
	*buffer_length = 0;
	return (j);
}

static int	find_strlength_null_string(char *buf, int backslashes)
{
	int x;

	x = 0;
	while (x < BUF_SIZE)
	{
		if (buf[x] == '\0')
		{
			if (backslashes > 0)
				backslashes--;
			else
				return (x);
		}
		x++;
	}
	return (x);
}

int			put_on_buf(char *buf, t_flags *data, int *integers, int len)
{
	int		i;
	int		j;

	j = 0;
	i = find_strlength_null_string(buf, integers[3]);
	while (j < len)
	{
		if (i < BUF_SIZE)
		{
			buf[i] = data->result[j];
			j++;
			i++;
		}
		if (i == BUF_SIZE)
		{
			integers[2] += print_buf(buf, &integers[3]);
			i = 0;
		}
	}
	if (data->specifier == 'c' && data->precision == -21)
		integers[3]++;
	ft_strdel(&data->result);
	return (0);
}
