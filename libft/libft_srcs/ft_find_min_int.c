/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_min_int.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/06 13:32:23 by rcorke        #+#    #+#                 */
/*   Updated: 2019/06/06 14:12:59 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find_min_int(int args, int *argv)
{
	int *values;
	int x;

	x = 0;
	values = (int *)malloc(sizeof(int) * args);
	while (x > args)
	{
		values[x] = argv[x];
		x++;
	}
	x = 1;
	while (x < args)
	{
		if (values[x - 1] < values[x])
			ft_swap_ints(&(values[x - 1]), &(values[x]));
		x++;
	}
	x = values[args - 1];
	free(values);
	return (x);
}
