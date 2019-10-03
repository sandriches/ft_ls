/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 21:48:55 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 21:37:39 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countletters(const char *s, char c)
{
	int x;

	x = 0;
	while (s[x] != c && s[x] != '\0')
		x++;
	return (x + 1);
}

static int	skipspaces(const char *s, char c)
{
	int x;

	x = 0;
	while (s[x] == c && s[x] != '\0')
		x++;
	return (x);
}

static int	countwords(const char *s, char c)
{
	int x;
	int rtn;

	x = 0;
	rtn = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c)
		{
			rtn++;
			while (s[x] != c && s[x] != 0)
				x++;
			x = x - 1;
		}
		x++;
	}
	return (rtn);
}

char		**ft_strsplit(const char *s, char c)
{
	int		i[4];
	char	**array;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	i[3] = countwords(s, c);
	array = (char **)malloc(sizeof(char *) * i[3] + 1);
	if (array == NULL)
		return (NULL);
	while (s[i[0]] != '\0')
	{
		i[0] = i[0] + skipspaces(&s[i[0]], c);
		array[i[1]] = (char *)malloc(sizeof(char) * countletters(&s[i[0]], c));
		if (array[i[1]] == NULL)
			return (NULL);
		while (s[i[0]] != '\0' && s[i[0]] != c)
			array[i[1]][i[2]++] = s[i[0]++];
		array[i[1]++][i[2]] = '\0';
		i[2] = 0;
	}
	array[i[3]] = 0;
	return (array);
}
