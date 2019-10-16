/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 19:06:33 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 14:53:28 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t x;
	size_t y;

	x = ft_strlen(s1);
	y = 0;
	while (y < n && s2[y] != '\0')
		s1[x++] = s2[y++];
	s1[x] = '\0';
	return (s1);
}
