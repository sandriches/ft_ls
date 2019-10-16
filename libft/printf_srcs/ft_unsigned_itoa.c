/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_itoa.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 13:07:18 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:55:31 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlength(unsigned int n, int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

static int	ft_strlength_int_max(intmax_t n, int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_max_int_itoa(intmax_t n)
{
	int		sign;
	int		y;
	char	*str;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	sign = (n >= 0) ? 1 : -1;
	y = (sign > 0) ? 1 : 2;
	n = n * sign;
	y = ft_strlength_int_max(n, y);
	str = ft_strnew(y);
	if (sign == -1)
		str[0] = '-';
	y--;
	sign = (sign == -1) ? 1 : 0;
	while (y >= sign)
	{
		str[y] = (n % 10) + 48;
		n = n / 10;
		y--;
	}
	return (str);
}

char		*ft_unsigned_itoa(unsigned int n)
{
	unsigned int	x;
	int				y;
	unsigned int	sign;
	char			*str;

	sign = 1;
	y = 2;
	n = n * sign;
	x = n;
	y = ft_strlength(n, y);
	str = (char *)malloc(sizeof(char) * y);
	str[y - 1] = '\0';
	y -= 2;
	x = 10;
	while (y >= 0)
	{
		str[y] = (n % x) + 48;
		n = n / x;
		y--;
	}
	return (str);
}
