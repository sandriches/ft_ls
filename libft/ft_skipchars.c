/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipspaces.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 17:42:13 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 12:56:13 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skipchars(char *s, char c)
{
	size_t x;

	x = 0;
	while (s[x] == c)
		x++;
	return (&s[x]);
}