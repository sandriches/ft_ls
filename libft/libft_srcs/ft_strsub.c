/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 14:00:41 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 15:03:26 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	unsigned int	x;
	unsigned int	y;
	char			*newstring;

	y = 0;
	x = start;
	if (s)
	{
		newstring = (char *)malloc(sizeof(char) * (len + 1));
		if (newstring == NULL)
			return (NULL);
		while (y < len)
		{
			newstring[y] = s[x];
			x++;
			y++;
		}
		newstring[y] = '\0';
		return (newstring);
	}
	return (0);
}
