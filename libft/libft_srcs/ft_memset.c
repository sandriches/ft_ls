/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 14:44:06 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/15 16:13:53 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			x;
	unsigned char	*str;

	str = (unsigned char *)b;
	x = 0;
	while (x < len)
	{
		str[x] = c;
		x++;
	}
	return (str);
}
