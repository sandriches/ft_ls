/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_first_dirent.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 14:45:52 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/14 17:48:41 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_total_blocks(t_dir_list *list)
{
	t_dir_list		*iter;
	unsigned long	blocks;

	blocks = 0;
	iter = list;
	while (iter)
	{
		blocks += iter->blocks;
		iter = iter->next;
	}
	ft_printf("total: %lu\n", blocks);
}

void			print_single_file(struct stat st, t_ls *ls, char *path)
{
	t_dir_list	*new;

	if (errno == EACCES)
	{
		perror(path);
		return ;
	}
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
		add_to_dir_list(d_s, current, path);
	d_s = readdir(ptr);
	if (ls->a == 1)
		add_to_dir_list(d_s, current, path);
	d_s = readdir(ptr);
	return (d_s);
}

int				print_first_dirent(t_dir_list **list, DIR *dptr, t_ls *ls)
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
			add_to_dir_list(ds, &current, ls->folder);
		if (ds->d_type == 4 && ((ls->a == 0 && ds->d_name[0] != \
		'.') || ls->a == 1) && ls->rc == 1)
			size += add_to_dir_list(ds, list, ls->folder);
		ds = readdir(dptr);
	}
	sort_print_free(ls, &current, &dptr);
	merge_sort_list(ls, list);
	ft_printf("\n");
	return (size);
}
