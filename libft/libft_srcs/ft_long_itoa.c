/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_long_itoa.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 13:07:18 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 16:34:07 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlength(long int n, long int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_long_itoa(long int n)
{
	long int		x[3];
	char			*str;

	x[2] = (n >= 0) ? 1 : -1;
	x[1] = (x[2] > 0) ? 1 : 2;
	n = n * x[2];
	x[0] = n;
	x[1] = ft_strlength(n, x[1]);
	str = (char *)malloc(sizeof(char) * x[1] + 1);
	if (str == NULL)
		return (NULL);
	str[x[1]] = '\0';
	x[0] = 10;
	if (x[2] == -1)
		str[0] = '-';
	x[2] = (x[2] > 0) ? 0 : 1;
	while (x[1]-- > x[2])
	{
		str[x[1]] = (n % x[0]) + 48;
		n = n / x[0];
	}
	return (str);
}
