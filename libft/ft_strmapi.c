/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 13:11:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 15:01:52 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	x;
	char	*newstring;

	if (s)
	{
		newstring = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (newstring == NULL)
			return (NULL);
		x = 0;
		while (s[x] != '\0')
		{
			newstring[x] = f(x, s[x]);
			x++;
		}
		newstring[x] = '\0';
		return (newstring);
	}
	return (0);
}
