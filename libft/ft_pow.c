/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 17:18:55 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/23 17:41:18 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int n, int p)
{
	int x;
	int result;

	if (p < 0 || p > 31)
		return (-1);
	if (p == 0)
		return (1);
	x = 1;
	result = n;
	while (x++ < p)
		result = result * n;
	return (result);
}
