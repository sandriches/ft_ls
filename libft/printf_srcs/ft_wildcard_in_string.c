/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_wildcard_in_string.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/27 12:48:08 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/29 14:11:50 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_wildcard_in_string(char *str)
{
	int x;

	x = 0;
	while (ft_strchr("1234567890*", str[x]))
	{
		if (str[x] == '*')
			return (x);
		x++;
	}
	return (-1);
}
