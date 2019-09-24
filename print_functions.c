/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 13:17:16 by rcorke         #+#    #+#                */
/*   Updated: 2019/09/24 14:19:33 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir_list(t_dir_list *list)
{
	t_dir_list *iter;

	iter = list;
	while (iter)
	{
		ft_printf("%s\n", iter->d_s->d_name);
		iter = iter->next;
	}
}

void	print_info(DIR *ptr, struct dirent *d_s)
{
	ft_printf("%s", d_s->d_name);
	return ;
}
