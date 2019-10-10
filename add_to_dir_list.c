/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_dir_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 15:52:12 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/10 18:03:05 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	move_i_forward(char *str, int i, int e_or_not)
{
	if (e_or_not % 2 == 1)
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	else
	{
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (i);
}

static char	*remove_excess(char *str)
{
	char	*rtn;
	int		i;
	int		start;
	int		e_or_not;

	if (!str)
		return (NULL);
	i = 0;
	e_or_not = 1;
	while (e_or_not <= 8)
	{
		i = move_i_forward(str, i, e_or_not);
		if (e_or_not == 3)
			start = i;
		e_or_not++;
	}
	if (i > 3)
		i -= 3;
	rtn = ft_strnew(i - start + 1);
	return (ft_strncpy(rtn, &str[start], i - start));
}

static int	is_more_than_year_old(char *str)
{
	int 	x;
	int 	len;
	char	*year;

	x = ft_strlen(str) - 2;
	len = x + 1;
	while (ft_isdigit(str[x]))
		x--;
	year = ft_strsub(str, x, len - x);
	len = ft_atoi(year);
	free(year);
	if (len > 1970)
		return (1);
	return (0);
}

static char	*get_year_str(char *str)
{
	int		x;
	int		len;
	char	*year;
	char	*tmpstr;
	char	*rtn_str;

	len = ft_strlen(str) - 1;
	x = len - 2;
	while (ft_isdigit(str[x]))
		x--;
	year = ft_strsub(str, x, len - x);
	x--;
	while (ft_isdigit(str[x]) || str[x] == ':')
		x--;
	x--;
	len = x;
	tmpstr = ft_strsub(str, 4, len - 2);
	rtn_str = ft_strjoin(tmpstr, year);
	free(tmpstr);
	free(year);
	return (rtn_str);
}

static char	*get_rel_time(struct stat *st)
{
	time_t		time_val;
	time_t		difference;
	char		*rtn_str;
	char		*time_str;

	time_val = time(&time_val);
	difference = (time_t)(difftime(time_val, st->st_mtimespec.tv_sec));
	time_str = ctime(&difference);
	if (is_more_than_year_old(time_str) == 0)
		rtn_str = remove_excess(ctime(&(st->st_mtimespec.tv_sec)));
	else
		rtn_str = get_year_str(ctime(&st->st_mtimespec.tv_sec));
	return (rtn_str);
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
	(*new)->m_time_str = get_rel_time(st);
	(*new)->uid = st->st_uid;
	(*new)->gid = st->st_gid;
	(*new)->blocks = st->st_blocks;
	(*new)->n_links = st->st_nlink;
	(*new)->m_time = st->st_mtimespec.tv_sec;
	(*new)->a_time = st->st_atimespec.tv_sec;
	(*new)->size = st->st_size;
}

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

static void	add_to_end(t_dir_list **list, t_dir_list **new)
{
	t_dir_list *iter;

	iter = *list;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = *new;
	(*new)->next = NULL;
}

static void	add_to_new_node(t_dir_list **new, char *path, struct dirent *ds)
{
	(*new)->path = join_paths_with_slash(path, ds->d_name);
	(*new)->name = ft_strdup(ds->d_name);
	(*new)->len_name = ft_strlen(ds->d_name);
	(*new)->type = ds->d_type;
	(*new)->next = NULL;
}

static int	compare_types_rev(char sort, t_dir_list *new, t_dir_list *iter)
{
	if (sort == 0)
	{
		if (ft_biggest_ascii_str(new->name, iter->name) == 1)
			return (1);
	}
	else if (sort == 't')
	{
		if (new->m_time < iter->m_time)
			return (1);
	}
	else if (sort == 'u')
	{
		if (new->a_time < iter->a_time)
			return (1);
	}
	else if (sort == 'S')
		if (new->size < iter->size)
			return (1);
	return (0);
}

static int	compare_types(char sort, t_dir_list *new, t_dir_list *iter, \
t_ls *ls)
{
	if (ls->r == 0)
	{
		if (sort == 0)
		{
			if (ft_biggest_ascii_str(new->name, iter->name) == 2)
				return (1);
		}
		else if (sort == 't')
		{
			if (new->m_time > iter->m_time)
				return (1);
		}
		else if (sort == 'u')
		{
			if (new->a_time > iter->a_time)
				return (1);
		}
		else if (sort == 'S')
			if (new->size > iter->size)
				return (1);
	}
	else if (ls->r == 1)
		return (compare_types_rev(sort, new, iter));
	return (0);
}

static void	sort_with_three(t_dir_list **new, t_ls *ls, t_dir_list **list)
{
	t_dir_list	*iter;
	t_dir_list	*next;

	iter = *list;
	if (compare_types(ls->sort, *new, iter, ls) == 1)
	{
		(*new)->next = *list;
		*list = *new;
	}
	else if (!iter->next)
		(*list)->next = *new;
	else
	{
		next = iter->next;
		if (compare_types(ls->sort, *new, iter->next, ls) == 1)
		{
			iter->next = *new;
			(*new)->next = next;
		}
		else
			next->next = *new;
	}
}

static void	edit_if_one(t_dir_list **prev, t_dir_list **current, \
t_dir_list **next)
{
	*prev = *current;
	*current = *next;
	*next = (*next)->next;
}

static void	add_to_correct_position(t_dir_list **new, t_ls *ls, \
t_dir_list **list)
{
	t_dir_list	*prev;
	t_dir_list	*current;
	t_dir_list	*next;

	if (!(*list)->next || !(*list)->next->next)
		return (sort_with_three(new, ls, list));
	if (compare_types(ls->sort, *new, *list, ls) == 1)
	{
		(*new)->next = *list;
		*list = *new;
		return ;
	}
	prev = *list;
	current = prev->next;
	next = current->next;
	while (prev && current && next && compare_types(ls->sort, *new, \
	current, ls) == 0)
		edit_if_one(&prev, &current, &next);
	if (!next && compare_types(ls->sort, *new, current, ls) == 0)
		current->next = *new;
	else
	{
		prev->next = *new;
		(*new)->next = current;
	}
}

int			add_to_dir_list(struct dirent *d_s, t_dir_list **current, \
t_ls *ls, char *path)
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
	if (!*current)
		*current = new;
	else
		add_to_correct_position(&new, ls, current);
	return (1);
}
