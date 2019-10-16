/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 20:03:32 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 14:52:30 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	x;
	int result;
	int	pn;

	pn = 1;
	result = 0;
	x = 0;
	while (str[x] == '\f' || str[x] == '\v' || str[x] == '\r' || str\
	[x] == '\t' || str[x] == '\n' || str[x] == ' ')
		x++;
	if (str[x] == '-')
	{
		pn = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		result = result * 10 + (str[x] - 48);
		x++;
	}
	return (result * pn);
}
