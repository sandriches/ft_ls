/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_dirent.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:13:11 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/08 18:09:40 by rcorke        ########   odam.nl         */
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

static void	confirm_list(t_ls *ls, char **path, t_dir_list **list)
{
	*path = NULL;
	if (*list)
	{
		*path = ft_strdup((*list)->path);
		pop_first_list(list);
		print_path(ls, *path);
	}
}

static void	print_loop(t_dir_list **list, DIR *dptr, t_ls *ls, int list_size)
{
	while (list_size > 0 && *list)
	{
		dptr = opendir((*list)->path);
		if (dptr)
		{
			if (print_dirent(list, dptr, ls) == 1)
				continue ;
		}
		else
		{
			no_folder_error(ls, *list);
			pop_first_list(list);
		}
		list_size--;
	}
}

int			print_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
{
	struct dirent	*ds;
	t_dir_list		*current;
	t_dir_list		*new_list;
	int				list_size;
	char			*path;

	ds = get_ds_init_values(dptr, &list_size, &current);
	confirm_list(ls, &path, list);
	if (!ds)
		return (free_str(&path));
	while (ds)
	{
		add_to_dir_list(ds, &current, ls, path);
		if (ds->d_type == 4 && ((ls->a == 0 && \
		ds->d_name[0] != '.') || ls->a == 1) && \
		ft_strequ(ds->d_name, ".") != 1 && \
		ft_strequ(ds->d_name, "..") != 1)
			list_size += add_to_dir_list(ds, &new_list, ls, path);
		ds = readdir(dptr);
	}
	free_str(&path);
	sort_print_free(ls, &current, &dptr);
	join_lists(&new_list, list);
	print_loop(list, dptr, ls, list_size);
	return (1);
}
