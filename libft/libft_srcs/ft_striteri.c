/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/15 18:32:30 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 17:48:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int x;

	x = 0;
	if (s && f)
	{
		while (s[x] != '\0')
		{
			f(x, &s[x]);
			x++;
		}
	}
}
