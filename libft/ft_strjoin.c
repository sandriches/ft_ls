/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 15:38:13 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 17:29:17 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstring;
	int		x;
	int		y;
	int		strlength;

	if (s1 && s2)
	{
		strlength = (int)ft_strlen(s1) + (int)ft_strlen(s2);
		newstring = (char *)malloc(sizeof(char) * strlength + 1);
		if (newstring == NULL)
			return (NULL);
		x = 0;
		while (s1[x] != '\0')
		{
			newstring[x] = s1[x];
			x++;
		}
		y = 0;
		while (s2[y] != '\0')
			newstring[x++] = s2[y++];
		newstring[x] = '\0';
		return (newstring);
	}
	return (0);
}
