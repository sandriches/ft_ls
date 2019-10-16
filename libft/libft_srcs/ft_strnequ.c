/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 13:39:19 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 15:02:59 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(const char *s1, const char *s2, size_t n)
{
	size_t x;

	x = 0;
	if (s1 && s2)
	{
		while ((s1[x] != '\0' || s2[x] != '\0') && x < n)
		{
			if (s1[x] != s2[x])
				return (0);
			x++;
		}
		return (1);
	}
	return (0);
}
