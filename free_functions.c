/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/26 16:28:45 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/06 16:02:00 by sandRICH      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

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
				ft_memdel((void **)&(to_free->path));
			free(to_free);
		}
	}
}

void	free_singular_node(t_dir_list **to_free)
{
	if (to_free && *to_free)
	{
		if ((*to_free)->path)
		{
			// ft_printf("PATH TO FREE IN SINGULAR NODE: %s\n", to_free->path);
			// ft_memdel((void **)(tt_free->path));
			free_str(&(*to_free)->path);
		}
		if ((*to_free)->permissions)
			free_str(&(*to_free)->permissions);
		if ((*to_free)->name)
			free_str(&(*to_free)->name);
		if ((*to_free)->u_name)
			free_str(&(*to_free)->u_name);
		if ((*to_free)->g_name)
			free_str(&(*to_free)->g_name);
		free(*to_free);
		*to_free = NULL;
	}
}

void	free_current(t_dir_list **list)
{
	t_dir_list *iter;
	t_dir_list *to_free;

	iter = *list;
	while (iter)
	{
		to_free = iter;
		// ft_printf("ITER PATH: %s\n", to_free->path);
		iter = iter->next;
		if (to_free)
		{
			if (to_free->path)
			{
				// ft_printf("PATH TO FREE: %s\n", to_free->path);
				free(to_free->path);
			}
			if (to_free->permissions)
				ft_memdel((void **)&to_free->permissions);
			if (to_free->name)
				ft_memdel((void **)&to_free->name);
			if (to_free->u_name)
				ft_memdel((void **)&to_free->u_name);
			if (to_free->g_name)
				ft_memdel((void **)&to_free->g_name);
			free(to_free);
			to_free = NULL;
		}
	}
	*list = NULL;
}
