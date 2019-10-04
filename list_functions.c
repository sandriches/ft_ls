/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 13:33:20 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/04 16:39:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*join_paths_with_slash(char *old_path, char *new_path)
{
	char	*rtn_path;
	int		len;
	int		len_old_path;

	len_old_path = ft_strlen(old_path);
	len = len_old_path + ft_strlen(new_path) + 1;
	rtn_path = ft_strnew(len);
	rtn_path = ft_strcpy(rtn_path, old_path);
	if (rtn_path[len_old_path - 1] && rtn_path[len_old_path - 1] != '/')
		rtn_path[len_old_path] = '/';
	ft_strcpy(&rtn_path[len_old_path + 1], new_path);
	return (rtn_path);
}

void			pop_first_list(t_dir_list **list)
{
	t_dir_list *to_free;

	if (!list || !(*list))
		return ;
	to_free = *list;
	*list = (*list)->next;
	if (to_free)
	{
		if (to_free->path)
			free(to_free->path);
		free(to_free);
		to_free = NULL;
	}
}

void			sort_print_free(t_ls *ls, t_dir_list **current, DIR **dptr)
{
	if (*current)
	{
		sort_list(ls, current);
		print_dir_list(ls, *current);
		free_current(*current);
	}
	closedir(*dptr);
}
