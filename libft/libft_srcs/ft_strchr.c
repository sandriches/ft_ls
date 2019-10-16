/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 20:04:36 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/30 11:19:49 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		x;
	int		y;
	char	l;

	l = (char)c;
	x = 0;
	y = 0;
	while (s[x] != '\0')
	{
		if (s[x] == l)
			return ((char *)&s[x]);
		x++;
	}
	if (l == '\0')
		return ((char *)&s[x]);
	return (NULL);
}
