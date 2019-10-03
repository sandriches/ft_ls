/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 16:20:08 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/21 11:18:45 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			x;
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	t;

	t = (unsigned char)c;
	x = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (t > 255)
		return (NULL);
	while (x < n)
	{
		dest[x] = source[x];
		if (source[x] == t)
			return (&dest[x + 1]);
		x++;
	}
	return (NULL);
}
