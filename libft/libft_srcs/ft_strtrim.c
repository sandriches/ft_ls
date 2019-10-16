/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 16:16:13 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 17:35:52 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skipspaces(const char *s)
{
	int x;
	int y;
	int z;
	int a;

	x = 0;
	y = 0;
	z = 0;
	while ((s[x] == ' ' || s[x] == '\n' || s[x] == '\t') && s[x] != '\0')
		x++;
	if (s[x] == '\0')
		return (x);
	while (s[y] != '\0')
		y++;
	a = y;
	y--;
	while (s[y] == ' ' || s[y] == '\n' || s[y] == '\t')
	{
		y--;
		z++;
	}
	return (a - (x + z));
}

char		*ft_strtrim(const char *s)
{
	int		x[3];
	char	*newstring;

	if (s)
	{
		newstring = (char *)malloc(sizeof(char) * ft_skipspaces(s) + 1);
		if (newstring == NULL)
			return (NULL);
		x[0] = 0;
		while (s[x[0]] == ' ' || s[x[0]] == '\n' || s[x[0]] == '\t')
			x[0]++;
		x[1] = x[0];
		while (s[x[0]] != '\0')
			x[0]++;
		x[0]--;
		while (s[x[0]] == ' ' || s[x[0]] == '\n' || s[x[0]] == '\t')
			x[0]--;
		x[2] = x[0];
		x[0] = 0;
		while (x[1] <= x[2])
			newstring[x[0]++] = s[x[1]++];
		newstring[x[0]] = '\0';
		return (newstring);
	}
	return (0);
}
