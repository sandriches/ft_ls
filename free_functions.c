/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/26 16:28:45 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 18:45:19 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_everything(t_ls *ls, t_dir_list **list)
{
	t_dir_list *iter;
	t_dir_list *to_free;

	if (ls)
		free(ls);
	if (list && *list)
	{
		iter = *list;
		while (iter)
		{
			to_free = iter;
			iter = iter->next;
			if (to_free->path)
				free(to_free->path);
			free(to_free);
		}
	}
}

void	free_singular_node(t_dir_list *to_free)
{
	if (to_free)
	{
		if (to_free->path)
			free(to_free->path);
		if (to_free->permissions)
			free(to_free->permissions);
		if (to_free->name)
			free(to_free->name);
		if (to_free->u_name)
			free(to_free->u_name);
		if (to_free->g_name)
			free(to_free->g_name);
		free(to_free);
		to_free = NULL;
	}
}

void	free_current(t_dir_list *list)
{
	t_dir_list *iter;
	t_dir_list *to_free;

	iter = list;
	while (iter)
	{
		to_free = iter;
		iter = iter->next;
		if (to_free)
		{
			if (to_free->path)
				free(to_free->path);
			if (to_free->permissions)
				free(to_free->permissions);
			if (to_free->name)
				free(to_free->name);
			if (to_free->u_name)
				free(to_free->u_name);
			if (to_free->g_name)
				free(to_free->g_name);
			free(to_free);
			to_free = NULL;
		}
	}
	list = NULL;
}
