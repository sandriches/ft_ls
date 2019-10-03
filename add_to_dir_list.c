/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_dir_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 15:52:12 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 17:15:04 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	copy_stat_to_new(struct stat *st, t_dir_list **new)
{
	struct passwd	*pw;
	struct group	*gp;

	pw = getpwuid(st->st_uid);
	gp = getgrgid(st->st_gid);
	(*new)->uid = st->st_uid;
	(*new)->gid = st->st_gid;
	(*new)->u_name = ft_strdup(pw->pw_name);
	(*new)->g_name = ft_strdup(gp->gr_name);
	(*new)->n_links = st->st_nlink;
	(*new)->a_time = st->st_atimespec.tv_sec;
	(*new)->m_time = st->st_mtimespec.tv_sec;
	(*new)->size = st->st_size;
}

static void	check_sticky_bits(char **str, struct stat *st)
{
	// if (st->st_mode & S_ISGID)			//set group id on execution (2... - ---------x) - group ID on execute bit 2000
		// add_to_end_of_str(&rtn, 'x');
	if (st->st_mode & S_ISVTX)			//save swapped text even after use (1... ---------t) - sticky bit is set 1000 -> takes priority when both S_ISVTZX and S_ISGID are being used
	{
		if ((*str)[8] == 'x')
			(*str)[8] = 't';
		else
			(*str)[8] = 'T';
	}
	if (st->st_mode & S_ISUID)			//set user id on execution (4... ---s------) - user ID on execute bit 4000
	{
		if ((*str)[2] == 'x')
			(*str)[2] = 's';
		else
			(*str)[2] = 'S';
	}
}

static void	copy_permissions_to_new(struct stat *st, char **str)
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

static void	add_to_end(t_dir_list **list, t_dir_list **new)
{
	t_dir_list *iter;

	iter = *list;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = *new;
	(*new)->next = NULL;
}

int			add_to_dir_list(struct dirent *d_s, t_dir_list **current, \
char *path, char start_or_end)
{
	t_dir_list	*new;
	struct stat	st;

	if (!d_s)
		return (0);
	new = (t_dir_list *)malloc(sizeof(t_dir_list));
	new->path = join_paths_with_slash(path, d_s->d_name);
	new->name = ft_strdup(d_s->d_name);
	new->type = d_s->d_type;
	new->next = NULL;
	stat(new->path, &st);
	copy_stat_to_new(&st, &new);
	new->permissions = ft_strdup("---------");
	copy_permissions_to_new(&st, &new->permissions);
	new->len_name = ft_strlen(d_s->d_name);
	if (!*current)
		*current = new;
	else if (start_or_end == 's')
		new->next = *current;
	else if (start_or_end == 'e')
		add_to_end(current, &new);
	return (1);
}
