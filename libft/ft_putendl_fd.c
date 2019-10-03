/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 13:49:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/24 15:39:20 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(const char *s, int fd)
{
	int x;

	x = 0;
	if (s)
	{
		while (s[x] != '\0')
			ft_putchar_fd(s[x++], fd);
		ft_putchar_fd('\n', fd);
	}
}
