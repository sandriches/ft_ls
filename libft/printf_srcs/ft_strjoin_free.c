/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 18:27:32 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:50:30 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin_free_char(char *s1, char new_character)
{
	char	*new_string;
	int		x;
	int		strlength;

	strlength = ft_strlen(s1) + 1;
	new_string = (char *)malloc(sizeof(char) * (strlength + 1));
	x = 0;
	while (s1[x] != '\0')
	{
		new_string[x] = s1[x];
		x++;
	}
	new_string[x] = new_character;
	x++;
	new_string[x] = '\0';
	free(s1);
	return (new_string);
}

char	*ft_strjoin_free_char_left(char *s1, char new_character)
{
	char	*new_string;
	int		x;
	int		strlength;

	strlength = ft_strlen(s1) + 1;
	new_string = (char *)malloc(sizeof(char) * (strlength + 1));
	new_string[0] = new_character;
	x = 1;
	while (s1[x - 1] != '\0')
	{
		new_string[x] = s1[x - 1];
		x++;
	}
	new_string[x] = '\0';
	free(s1);
	return (new_string);
}

char	*ft_strnjoin_free(char *s1, char *s2)
{
	char	*newstring;
	int		x;
	int		y;
	int		strlength;

	strlength = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	newstring = (char *)malloc(sizeof(char) * strlength + 1);
	x = 0;
	while (s1[x] != '\0')
	{
		newstring[x] = s1[x];
		x++;
	}
	y = 0;
	while (s2[y] != '\0')
	{
		newstring[x] = s2[y];
		x++;
		y++;
	}
	newstring[x] = '\0';
	free(s1);
	free(s2);
	return (newstring);
}

char	*ft_malloc_copy(char *s1)
{
	int		x;
	char	*rtnstring;

	x = 0;
	rtnstring = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	while (s1[x] != '\0')
	{
		rtnstring[x] = s1[x];
		x++;
	}
	rtnstring[x] = '\0';
	return (rtnstring);
}
