/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_dir_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 15:52:12 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/13 15:19:05 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_sticky_bits(char **str, struct stat *st)
{
	if (st->st_mode & S_ISVTX)
	{
		if ((*str)[8] == 'x')
			(*str)[8] = 't';
		else
			(*str)[8] = 'T';
	}
	if (st->st_mode & S_ISUID)
	{
		if ((*str)[2] == 'x')
			(*str)[2] = 's';
		else
			(*str)[2] = 'S';
	}
}

void		copy_permissions_to_new(struct stat *st, char **str)
{
	if (st->st_mode & S_IRUSR)
		(*str)[0] = 'r';
	if (st->st_mode & S_IRGRP)
		(*str)[3] = 'r';
	if (st->st_mode & S_IROTH)
		(*str)[6] = 'r';
	if (st->st_mode & S_IWUSR)
		(*str)[1] = 'w';
	if (st->st_mode & S_IWGRP)
		(*str)[4] = 'w';
	if (st->st_mode & S_IWOTH)
		(*str)[7] = 'w';
	if (st->st_mode & S_IXUSR)
		(*str)[2] = 'x';
	if (st->st_mode & S_IXGRP)
		(*str)[5] = 'x';
	if (st->st_mode & S_IXOTH)
		(*str)[8] = 'x';
	check_sticky_bits(str, st);
}

static void	add_to_new_node(t_dir_list **new, char *path, struct dirent *ds)
{
	(*new)->path = join_paths_with_slash(path, ds->d_name);
	(*new)->name = ft_strdup(ds->d_name);
	(*new)->len_name = ft_strlen(ds->d_name);
	(*new)->type = ds->d_type;
	(*new)->next = NULL;
}

void		copy_stat_to_new(struct stat *st, t_dir_list **new)
{
	struct passwd	*pw;
	struct group	*gp;

	if (!st)
		return ;
	pw = getpwuid(st->st_uid);
	gp = getgrgid(st->st_gid);
	if (pw)
		(*new)->u_name = ft_strdup(pw->pw_name);
	else
		(*new)->u_name = ft_strdup(ft_itoa(st->st_uid));
	if (!gp)
		(*new)->g_name = ft_strdup(ft_itoa(st->st_gid));
	else
		(*new)->g_name = ft_strdup(gp->gr_name);
	(*new)->m_time_str = get_rel_time(st->st_mtimespec.tv_sec);
	(*new)->a_time_str = get_rel_time(st->st_atimespec.tv_sec);
	(*new)->uid = st->st_uid;
	(*new)->gid = st->st_gid;
	(*new)->blocks = st->st_blocks;
	(*new)->n_links = st->st_nlink;
	(*new)->m_time = st->st_mtimespec.tv_sec;
	(*new)->a_time = st->st_atimespec.tv_sec;
	(*new)->size = st->st_size;
}

int			add_to_dir_list(struct dirent *d_s, t_dir_list **current, \
char *path)
{
	t_dir_list	*new;
	struct stat	st;

	if (!d_s)
		return (0);
	new = (t_dir_list *)ft_memalloc(sizeof(t_dir_list));
	if (!new)
		return (0);
	new->next = NULL;
	add_to_new_node(&new, path, d_s);
	if (d_s->d_type == 10)
		lstat(new->path, &st);
	else
		stat(new->path, &st);
	copy_stat_to_new(&st, &new);
	new->permissions = ft_strdup("---------");
	copy_permissions_to_new(&st, &new->permissions);
	if (*current)
		new->next = *current;
	*current = new;
	return (1);
}
