/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_long_long_itoa.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 13:07:18 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 14:53:31 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlength(long long n, int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_long_long_itoa(long long int n)
{
	long long	x;
	int			sign;
	int			y;
	char		*str;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	sign = (n >= 0) ? 1 : -1;
	y = (sign > 0) ? 1 : 2;
	n = n * sign;
	x = n;
	y = ft_strlength(n, y);
	str = ft_strnew(y);
	if (sign == -1)
		str[0] = '-';
	y--;
	x = 10;
	sign = (sign == -1) ? 1 : 0;
	while (y >= sign)
	{
		str[y] = (n % x) + 48;
		n = n / x;
		y--;
	}
	return (str);
}
