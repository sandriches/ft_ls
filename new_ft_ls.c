/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_ft_ls.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 16:49:30 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/04 17:06:18 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct dirent	*get_ds_init_values(DIR *ptr, int *num, t_dir_list **current)
{
	struct dirent *d_s;

	*num = 0;
	*current = NULL;
	d_s = readdir(ptr);
	d_s = readdir(ptr);
	d_s = readdir(ptr);
	return (d_s);
}

static int	print_first_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
{
	struct dirent	*ds;
	int				size;
	t_dir_list		*current;

	ds = get_ds_init_values(dptr, &size, &current);
	if (!ds)
		return (0);
	print_head_folder(ls);
	while (ds)
	{
		add_to_dir_list(ds, &current, ls->folder, 'e');
		if (ds->d_type == 4 && ((ls->a == 0 && ds->d_name[0] != '.') || ls->a == 1))
			size += add_to_dir_list(ds, list, ls->folder, 'e');
		ds = readdir(dptr);
	}
	sort_print_free(ls, &current, &dptr);
	ft_printf("\n");
	return (size);
}

static void	ft_ls(t_ls *ls, char *path)
{
	t_dir_list	*list;
	DIR			*dptr;
	int			folders_in_first_directory;

	list = NULL;
	dptr = opendir(path);
	if (!dptr)
		no_folder_error(ls, path);
	ls->folder = path;
	folders_in_first_directory = print_first_dirent(&list, dptr, ls);
	while (ls->R == 1 && folders_in_first_directory > 0)
	{
		dptr = opendir(list->path);
		if (!dptr)
			break ;
		print_dirent(&list, dptr, ls);
		folders_in_first_directory--;
	}
}

int			main(int argc, char **argv)
{
	int		start_file;
	t_ls	*ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
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
	// while (1);
	return (0);
}
