/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_decimal_unsigned_long.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/23 17:27:08 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:49:19 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		find_base(char c)
{
	if (c >= '0' && c <= '9')
		return ((int)c - '0');
	else
		return ((int)c - 'A' + 10);
}

unsigned long	ft_get_decimal_unsigned_long(char *str, int base)
{
	unsigned long	result;
	unsigned long	power;
	int				x;

	x = ft_strlen(str) - 1;
	result = 0;
	power = 1;
	while (x >= 0)
	{
		result = result + find_base(str[x]) * power;
		power = power * base;
		x--;
		if (str[x] == '-')
			x--;
	}
	return (result);
}
