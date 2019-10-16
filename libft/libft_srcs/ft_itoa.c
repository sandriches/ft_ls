/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 00:43:09 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/17 13:45:05 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*min_int(char *min)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, min);
	return (str);
}

static int	strlength(int n, int y)
{
	while (n > 9)
	{
		n = n / 10;
		y++;
	}
	return (y);
}

char		*ft_itoa(int n)
{
	int		x[3];
	char	*str;

	if (n == -2147483648)
		return (min_int("-2147483648"));
	x[2] = (n >= 0) ? 1 : -1;
	x[1] = (x[2] > 0) ? 1 : 2;
	n = n * x[2];
	x[0] = n;
	x[1] = strlength(n, x[1]);
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
