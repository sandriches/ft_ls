/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 11:38:58 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/06 14:49:16 by sandRICH      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static struct dirent	*get_ds(DIR *ptr)
{
	struct dirent *d_s;

	d_s = readdir(ptr);
	d_s = readdir(ptr);
	d_s = readdir(ptr);
	return (d_s);
}

static DIR	*get_next_ptr(t_dir_list *list)
{
	DIR		*ptr;

	if (!list)
		return (NULL);
	ptr = opendir(list->path);
	return (ptr);
}


static int		print_all_in_dirent(t_dir_list **list, DIR *ptr, char *path, t_ls *ls)
{
	static int j;
	int i = 0;
	int list_size = 0;
	struct dirent	*d_s;
	t_dir_list		*current;

	ft_printf(BOLD_CYAN);
	ft_printf("%s:\n\033[0m", path);
	d_s = get_ds(ptr);
	current = NULL;
	if (!d_s)
	{
		ft_printf("\n");
		return (0);
	}
	if (!list || !*list)
		return (1);
	while (d_s)
	{
		add_to_current(d_s, &current, path);
		if (d_s->d_type == 4)
		{
			add_to_front_of_list(d_s, list, path, ls);
			list_size++;
		}
		d_s = readdir(ptr);
	}
	print_current(ls, current);
	free_current(current);
	if (path)
		free(path);
	ft_printf("\n\n");
	j++;
	if (list_size == 0)
		return (0);
	while (list_size > 0)
	{
		closedir(ptr);
		ptr = get_next_ptr(*list);
		path = ft_strdup((*list)->path);
		pop_first_list(list);
		if (print_all_in_dirent(list, ptr, path, ls) == 1)
			return (1);
		list_size--;
	}
	return (1);
}


static int	print_all_in_dirent_no_path(t_dir_list **list, DIR *ptr, t_ls *ls)
{
	struct dirent	*d_s;
	t_dir_list		*current;
	int				size;

	size = 0;
	d_s = get_ds(ptr);
	current = NULL;
	if (!d_s)
		return (0);
	if (ls->head_folder == 1)
	{
		ft_printf(BOLD_MAGENTA);
		HERE;
		ft_printf(COLOR_RESET);
	}
	while (d_s)
	{
		add_to_current(d_s, &current, ls->folder);
		if (d_s->d_type == 4)
		{
			add_to_list(d_s, list, ls->folder, ls);
			size++;
		}
		d_s = readdir(ptr);
	}
	print_current(ls, current);
	free_current(current);
	ft_printf("\n");
	return (size);
}

static void	ft_ls(t_ls *ls, char *folder)
{
	struct passwd	*pw_struct;
	struct group	*group_struct;
	struct stat		*stat_struct;
	struct dirent	*dirent_struct;
	DIR				*ptr;
	gid_t			group_id;

	t_dir_list		*list;
	char			*path;
	int				first_size;

	list = NULL;
	path = NULL;
	ptr = opendir(folder);
	if (!ptr)
		return (no_folder_error(ls, folder));
	ls->folder = folder;
	first_size = print_all_in_dirent_no_path(&list, ptr, ls);
	closedir(ptr);
	ptr = get_next_ptr(list);
	while (!ptr && list)
	{
		NL;
		no_folder_error(ls, list->path);
		pop_first_list(&list);
		ptr = get_next_ptr(list);
	}
	if (!list)
		return ;
	while (ls->R == 1 && first_size > 0)
	{
		print_all_in_dirent(&list, ptr, list->path, ls);
		if (first_size == 1)
			break ;
		if (dir_list_size(list) > 0)
			pop_first_list(&list);
		else
			break ;
		ptr = get_next_ptr(list);
		path = ft_strdup(list->path);
		first_size--;
	}
}

int		main(int argc, char **argv)
{
	int				start_files;
	t_ls			*ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->head_folder = 0;
	ls->folder = NULL;
	if (argc > 1)
	{
		start_files = set_flags(argc, argv, ls);
		// ft_printf("START FILES: %d\tARGC: %d\n", start_files, argc);
		if (start_files + 1 < argc)
			ls->head_folder = 1;
		else if (start_files == argc)
			ft_ls(ls, ft_strdup("."));
		while (start_files < argc)
		{
			ft_ls(ls, ft_strdup(argv[start_files]));
			start_files++;
		}
	}
	else
		ft_ls(ls, ft_strdup("."));
	return (0);
}
