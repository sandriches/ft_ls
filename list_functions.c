/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 13:33:20 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/06 16:05:28 by sandRICH      ########   odam.nl         */
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

void			pop_last_list(t_dir_list **list)
{
	t_dir_list	*to_free;
	
	if (!list || !*list)
		return ;
	to_free = *list;
	while (to_free && to_free->next)
		to_free = to_free->next;
	free_singular_node(&to_free);
}

void			sort_print_free(t_ls *ls, t_dir_list **current, DIR **dptr)
{
	if (*current)
	{
		// ft_printf("CURRENT BEFORE: %s\tSIZE BEFORE SORT: %d\n", (*current)->path, dir_list_size(*current));
		sort_list(ls, current);
		if (*current)
		{
			// ft_printf("PRINTING IN PRINT FREE, CURRENT: %s\tSIZE: %d\n", (*current)->path, dir_list_size(*current));
			print_dir_list(ls, *current);
			free_current(current);
		}
	}
	closedir(*dptr);
}

void			join_lists(t_dir_list **to_add, t_dir_list **main_list)
{
	t_dir_list *iter;

	if (!*to_add)
		return ;
	iter = *to_add;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = *main_list;
	*main_list = *to_add;
}