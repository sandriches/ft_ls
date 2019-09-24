/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 14:58:13 by rcorke         #+#    #+#                */
/*   Updated: 2019/09/24 15:00:16 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			dir_list_size(t_dir_list *list)
{
	t_dir_list	*iter;
	int			i;

	if (!list)
		return (0);
	iter = list;
	i = 0;
	while (iter)
	{
		iter = iter->next;
		i++;
	}
	return (i);
}