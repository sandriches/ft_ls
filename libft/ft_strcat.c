/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 17:25:24 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/17 18:52:32 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t x;
	size_t y;

	x = ft_strlen(s1);
	y = 0;
	while (s2[y] != '\0')
		s1[x++] = s2[y++];
	s1[x] = '\0';
	return (s1);
}
