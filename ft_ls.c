/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 16:49:30 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/14 17:48:56 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		dptr_exists(DIR *dptr, t_dir_list **list, t_ls *ls, \
int *folders)
{
	print_dirent(list, dptr, ls);
	*folders -= 1;
}

static void		no_dptr(t_dir_list **list)
{
	no_folder_error(*list);
	pop_first_list(list);
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
	while (ls->rc == 1 && folders_in_first_directory > 0 && list)
	{
		dptr = opendir(list->path);
		if (dptr)
			dptr_exists(dptr, &list, ls, &folders_in_first_directory);
		else
			no_dptr(&list);
	}
}

static t_ls		*make_ls_struct(void)
{
	t_ls *ls;

	ls = (t_ls *)ft_memalloc(sizeof(t_ls));
	if (!ls)
		return (NULL);
	ls->head_folder = 0;
	ls->folder = NULL;
	return (ls);
}

int				main(int argc, char **argv)
{
	int		start_file;
	t_ls	*ls;

	ls = make_ls_struct();
	if (!ls)
		return (1);
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
