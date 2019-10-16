/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 12:18:19 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 17:28:18 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	needlectr(const char *needle)
{
	int x;

	x = 0;
	while (needle[x] != '\0')
		x++;
	return (x);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	int x[3];
	int needlecount;

	needlecount = needlectr(needle);
	if (needlecount < 1)
		return ((char *)haystack);
	x[0] = -1;
	x[1] = 0;
	while (haystack[++x[0]] != '\0')
	{
		if (x[1] > 0 && haystack[x[0]] != needle[x[1]])
			x[1] = 0;
		if (haystack[x[0]] == needle[x[1]])
		{
			x[2] = x[0];
			while (haystack[x[2]] == needle[x[1]])
			{
				if (x[1] + 1 == needlecount)
					return ((char *)&haystack[x[0]]);
				x[2]++;
				x[1]++;
			}
		}
	}
	return (0);
}
