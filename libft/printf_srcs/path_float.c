/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_float.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 11:14:23 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 19:32:44 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	precision_ftoa(t_flags *data)
{
	if (data->precision == -42)
		data->precision = 6;
	else if (data->precision == -12)
		data->precision = 0;
}

static char	*ftoa(long double n, t_flags *data)
{
	char	*rtnstring;
	int		string_length;
	int		loop_number;

	precision_ftoa(data);
	loop_number = data->precision;
	string_length = ft_strlen(ft_itoa((int)n));
	rtnstring = ft_strnew(string_length + loop_number + 2);
	rtnstring = ft_strcpy(rtnstring, ft_itoa((int)n));
	n = n - (int)n;
	if (data->precision != 0)
		rtnstring[string_length] = '.';
	string_length++;
	while (loop_number > 0)
	{
		n = n * 10;
		rtnstring[string_length] = ((long long)n % 10) + 48;
		n = n - (long long)n;
		string_length++;
		loop_number--;
	}
	rtnstring[string_length] = '\0';
	return (rtnstring);
}

static void	check_edge_cases(char *nbr, int len)
{
	if (nbr[len] == '9')
	{
		nbr[len] = '0';
		check_edge_cases(nbr, len - 1);
	}
	else if (nbr[len] == '.')
		check_edge_cases(nbr, len - 1);
	else
		nbr[len]++;
}

static void	round_float(char *nbr, t_flags *data, long double n)
{
	int		tmp_precision;
	int		str_len;

	str_len = ft_strlen(nbr);
	tmp_precision = data->precision;
	n = n - (long)n;
	while (tmp_precision > 0)
	{
		n *= 10;
		n = n - (long)n;
		tmp_precision--;
	}
	n = n * 2;
	if ((long double)1 < n)
		check_edge_cases(nbr, str_len - 1);
}

void		float_path(t_flags *data, va_list list)
{
	double		small_storage;
	long double	long_storage;
	char		*tmpstring;

	if ((data->length & 16) == 16)
	{
		long_storage = va_arg(list, long double);
		tmpstring = ftoa(long_storage, data);
		round_float(tmpstring, data, long_storage);
	}
	else
	{
		small_storage = va_arg(list, double);
		tmpstring = ftoa(small_storage, data);
		round_float(tmpstring, data, small_storage);
	}
	if ((data->flags & 16) == 16 && (!ft_strchr(tmpstring, '.')))
		tmpstring = ft_strjoin_free_char(tmpstring, '.');
	data->result = tmpstring;
	data->result = make_width(data);
}
