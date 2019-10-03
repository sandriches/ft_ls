/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 15:01:54 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/18 15:07:16 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	size_t	x;
	char	*str;

	x = 0;
	str = (char *)s;
	if (len > 0)
	{
		while (x < len)
		{
			str[x] = 0;
			x++;
		}
	}
}
