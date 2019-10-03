/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rmchars.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 17:47:48 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 12:56:32 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rplchars(char *s, char a, char c)
{
	size_t x;

	x = 0;
	while (s[x] != '\0')
	{
		if (s[x] == a)
			s[x] = c;
		x++;
	}
	return (s);
}
