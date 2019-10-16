/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_long_long_itoa.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 16:52:47 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:55:48 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlength_unsigned_ll(unsigned long long n, int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_unsigned_long_long_itoa(unsigned long long int n)
{
	unsigned long long	x;
	unsigned long long	sign;
	int					y;
	char				*str;

	sign = 1;
	y = 2;
	n = n * sign;
	x = n;
	y = ft_strlength_unsigned_ll(n, y);
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
