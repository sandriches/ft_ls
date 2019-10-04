/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_dirent.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:13:11 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/04 17:05:40 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_path(t_ls *ls, char *path)
{
	if (ls->G == 1)
		ft_printf(BOLD_CYAN);
	ft_printf("%s:\n", path);
}

int			print_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
{
	struct dirent	*ds;
	t_dir_list		*current;
	int				list_size;

	ds = get_ds_init_values(dptr, &list_size, &current);
	if (*list)
		print_path(ls, (*list)->path);
	if (!ds || !list || !*list)
	{
		if (*list)
			pop_first_list(list);
		return (0);
	}
	while (ds)
	{
		add_to_dir_list(ds, &current, (*list)->path, 'e');
		if (ds->d_type == 4 && ((ls->a == 0 && ds->d_name[0] != '.') || ls->a == 1))
		{
			// ft_printf("ADDING TO LIST LIST\n");
			list_size += add_to_dir_list(ds, list, (*list)->path, 's');
		}
		ds = readdir(dptr);
	}
	sort_print_free(ls, &current, &dptr);
	// ft_printf("FIRST IN LIST: %s\n", (*list)->name);
	pop_first_list(list);
	// ft_printf("SECOND IN LIST: %s\n", (*list)->name);
	while (list_size > 0 && *list)
	{
		dptr = opendir((*list)->path);
		// ft_printf("LIST PATH: %s\n", (*list)->path);
		if (print_dirent(list, dptr, ls) == 0)
			return (0);
		list_size--;
	}
	return (1);
}
