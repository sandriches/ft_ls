/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 13:49:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 15:38:41 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(const char *s)
{
	int x;

	x = 0;
	if (s)
	{
		while (s[x] != '\0')
			ft_putchar(s[x++]);
		ft_putchar('\n');
	}
}
