/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 16:49:30 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/10 16:29:23 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct dirent	*get_ds_init_values(DIR *ptr, t_dir_list **current, t_ls *ls, \
char *path)
{
	struct dirent *d_s;

	*current = NULL;
	if (!ptr)
		return (NULL);
	d_s = readdir(ptr);
	if (!d_s)
		return (NULL);
	if (ls->a == 1)
		add_to_dir_list(d_s, current, ls, path);
	d_s = readdir(ptr);
	if (ls->a == 1)
		add_to_dir_list(d_s, current, ls, path);
	d_s = readdir(ptr);
	return (d_s);
}

static int		print_first_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
{
	struct dirent	*ds;
	int				size;
	t_dir_list		*current;

	size = 0;
	ds = get_ds_init_values(dptr, &current, ls, ls->folder);
	if (!ds && ls->a == 0)
		return (0);
	print_head_folder(ls);
	while (ds)
	{
		if ((ls->a == 0 && ds->d_name[0] != '.') || ls->a == 1)
			add_to_dir_list(ds, &current, ls, ls->folder);
		if (ds->d_type == 4 && ((ls->a == 0 && ds->d_name[0] != \
		'.') || ls->a == 1) && ls->R == 1)
			size += add_to_dir_list(ds, list, ls, ls->folder);
		ds = readdir(dptr);
	}
	sort_print_free(ls, &current, &dptr);
	ft_printf("\n");
	return (size);
}

static void		print_single_file(struct stat st, t_ls *ls, char *path)
{
	t_dir_list	*new;

	if (ls->l == 1)
	{
		new = (t_dir_list *)ft_memalloc(sizeof(t_dir_list));
		new->name = ft_strdup(path);
		copy_stat_to_new(&st, &new);
		new->permissions = ft_strdup("---------");
		copy_permissions_to_new(&st, &new->permissions);
		print_info(ls, new);
		free_singular_node(&new);
	}
	else
		ft_printf("%s", path);
	NL;
}

static void		ft_ls(t_ls *ls, char *path)
{
	t_dir_list	*list;
	DIR			*dptr;
	int			folders_in_first_directory;
	struct stat	st;
	int			st_rtn;

	list = NULL;
	dptr = opendir(path);
	st_rtn = lstat(path, &st);
	if (!dptr && st_rtn == -1)
		return (perror(path));
	else if (!dptr)
		return (print_single_file(st, ls, path));
	ls->folder = path;
	folders_in_first_directory = print_first_dirent(&list, dptr, ls);
	while (ls->R == 1 && folders_in_first_directory > 0 && list)
	{
		dptr = opendir(list->path);
		if (dptr)
		{
			print_dirent(&list, dptr, ls);
			folders_in_first_directory--;
		}
		else
		{
			no_folder_error(ls, list);
			pop_first_list(&list);
		}
	}
}

int				main(int argc, char **argv)
{
	int		start_file;
	t_ls	*ls;

	ls = (t_ls *)ft_memalloc(sizeof(t_ls));
	if (!ls)
		return (1);
	ls->head_folder = 0;
	ls->folder = NULL;
	if (argc > 1)
	{
		start_file = set_flags(argc, argv, ls);
		if (start_file + 1 < argc)
			ls->head_folder = 1;
		else if (start_file == argc)
			ft_ls(ls, ".");
		while (start_file < argc)
		{
			ft_ls(ls, argv[start_file]);
			start_file++;
		}
	}
	else
		ft_ls(ls, ".");
	free_everything(ls, NULL);
	return (0);
}
