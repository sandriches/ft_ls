/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlcat.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 19:30:33 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 19:08:40 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t x;
	size_t y;
	size_t dlen;
	size_t slen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size < dlen || size == 0)
		return (size + slen);
	x = 0;
	y = dlen;
	while (src[x] != '\0' && (dlen + x) < size - 1)
		dest[y++] = src[x++];
	dest[y] = '\0';
	return (slen + dlen);
}
