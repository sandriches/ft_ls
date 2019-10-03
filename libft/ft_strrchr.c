/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 20:04:36 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/30 11:24:09 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x[3];
	char	*rtn;
	char	l;

	l = (char)c;
	rtn = (char *)malloc(sizeof(char *));
	if (rtn == NULL)
		return (NULL);
	x[2] = 0;
	x[0] = 0;
	x[1] = 0;
	while (s[x[0]] != '\0')
	{
		if (s[x[0]] == l)
		{
			rtn = (char *)&s[x[0]];
			x[2] = 1;
		}
		x[0]++;
	}
	if (l == '\0')
		return ((char *)&s[x[0]]);
	if (x[2] == 0)
		return (NULL);
	return (rtn);
}
