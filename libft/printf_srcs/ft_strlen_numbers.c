/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen_numbers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/12 13:47:07 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:50:56 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_hex_numbers(char *str)
{
	int x;
	int rtnvalue;

	rtnvalue = 0;
	x = 0;
	while (str[x] != '\0')
	{
		if (ft_strchr(HEXSTRING, str[x]))
			rtnvalue++;
		x++;
	}
	return (rtnvalue);
}

int	ft_strlen_numbers(char *str)
{
	int x;
	int rtnvalue;

	rtnvalue = 0;
	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] <= '9' && str[x] >= '0')
			rtnvalue++;
		x++;
	}
	return (rtnvalue);
}
