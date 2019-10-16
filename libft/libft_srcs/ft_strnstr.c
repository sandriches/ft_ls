/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 12:18:19 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 17:37:11 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*checkstr(const char *h, const char *n, size_t len, size_t z)
{
	size_t x;
	size_t cnt;

	cnt = ft_strlen(n);
	x = 0;
	while (h[x] == n[x] && z + x < len)
	{
		if (x + 1 == cnt)
			return ((char *)h);
		x++;
	}
	return (0);
}

char		*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t x;
	size_t length;
	size_t needlecount;
	size_t y;

	needlecount = ft_strlen(n);
	if (needlecount < 1)
		return ((char *)h);
	x = 0;
	y = 0;
	length = len;
	while (h[x] != '\0' && x < length)
	{
		if (h[x] == n[y])
		{
			if (checkstr(&h[x], n, len, x))
				return (checkstr(&h[x], n, len, x));
		}
		x++;
	}
	return (0);
}
