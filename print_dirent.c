/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_dirent.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:13:11 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/06 17:37:53 by sandRICH      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_path(t_ls *ls, char *path)
{
	if (ls->G == 1)
		ft_printf(BOLD_CYAN);
	ft_printf("%s:\n", path);
	ft_printf(COLOR_RESET);
}

int			print_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
{
	struct dirent	*ds;
	t_dir_list		*current;
	t_dir_list		*new_list;
	int				list_size;
	char			*path;

	ds = get_ds_init_values(dptr, &list_size, &current);
	path = NULL;
	if (*list)
	{
		path = ft_strdup((*list)->path);
		pop_first_list(list);
		print_path(ls, path);
	}
	if (!ds)
	{
		if (path)
			free_str(&path);
		// ft_printf("LIST PATH BEFORE RETURN: %s\n", (*list)->path);
		return (0);
	}
	while (ds)
	{
		add_to_dir_list(ds, &current, path, 'e');
		if (ds->d_type == 4 && ((ls->a == 0 && ds->d_name[0] != '.') || ls->a == 1))
			list_size += add_to_dir_list(ds, &new_list, path, 'e');
		ds = readdir(dptr);
	}
	free_str(&path);
	sort_print_free(ls, &current, &dptr);
	join_lists(&new_list, list);
	// ft_printf("LIST SIZE: %d\n", list_size);
	while (list_size > 0 && *list)
	{
		dptr = opendir((*list)->path);
		if (print_dirent(list, dptr, ls) == 1)
			continue ;
		// else
		// 	pop_first_list(list);		
		// if (*list)
		// 	pop_first_list(list);
		list_size--;
	}
	return (1);
}
