/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_long.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 13:42:04 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 14:55:20 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlength(unsigned long int n)
{
	int y;

	y = 1;
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_unsigned_long_itoa(unsigned long int n)
{
	unsigned long int	x;
	char				*str;

	x = ft_strlength(n);
	str = (char *)malloc(sizeof(char) * x + 1);
	if (str == NULL)
		return (NULL);
	str[x] = '\0';
	while (x > 0)
	{
		x--;
		str[x] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
