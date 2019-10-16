/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_flags.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 18:26:44 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:47:40 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags		*ft_get_flags(char *str)
{
	unsigned char	flags;
	size_t			x;

	flags = 0;
	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '#')
			return (0);
	}
	return (0);
}
