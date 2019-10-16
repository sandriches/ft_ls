/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 18:07:25 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 12:41:17 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	x;
	char	*str;
	char	l;

	l = (char)c;
	x = 0;
	str = (char *)s;
	while (x < n)
	{
		if (str[x] == l)
			return (&str[x]);
		x++;
	}
	return (0);
}
