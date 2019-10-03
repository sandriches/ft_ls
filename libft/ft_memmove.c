/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 17:32:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 14:37:42 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	x;
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	x = 0;
	if ((size_t)src == (size_t)dst)
		return (dst);
	if ((size_t)src > (size_t)dst)
		while (x < len)
		{
			dest[x] = source[x];
			x++;
		}
	else
		while (len-- > 0)
			dest[len] = source[len];
	return (dest);
}
