/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 16:20:08 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/17 18:28:26 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	x;
	char	*dest;
	char	*source;

	x = 0;
	dest = (void *)dst;
	source = (void *)src;
	while (x < n)
	{
		dest[x] = source[x];
		x++;
	}
	return (dest);
}
