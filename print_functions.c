/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 13:17:16 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/04 17:06:01 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		temp_print_dir_list(t_dir_list *list)
{
	t_dir_list *iter;

	iter = list;
	while (iter)
	{
		ft_printf("%s\tPATH: %s\n", iter->name, iter->path);
		iter = iter->next;
	}
}

void		print_flags(t_ls *ls)
{
	ft_printf("l->%d\nR->%d\na->%d\nr->%d\nsort->%c\tn->%d\tp->%d\tG->%d\n", \
	ls->l, ls->R, ls->a, ls->r, ls->sort, ls->n, ls->p, ls->G);
}

static char	get_d_type(t_dir_list *dir)
{
	char d_type;

	if (dir->type == DT_DIR)
		d_type = 'd';
	else if (dir->type == DT_LNK)
		d_type = 'l';
	else if (dir->type == DT_CHR)
		d_type = 'c';
	else if (dir->type == DT_BLK)
		d_type = 'b';
	else if (dir->type == DT_FIFO)
		d_type = 'p';
	else if (dir->type == DT_SOCK)
		d_type = 's';
	else
		d_type = '-';
	return (d_type);
}

static void	print_owner_info(t_ls *ls, t_dir_list *current)
{
	if (ls->n == 1)
		ft_printf("%d\t%d\t", current->uid, current->gid);
	else
		ft_printf("%s\t%s\t", current->u_name, current->g_name);
}

static void	print_color_code(t_ls *ls, t_dir_list *current)
{
	if (ls->G == 1)
	{
		if (current->type == DT_DIR)
			ft_printf(BOLD_CYAN);
		else if (current->type == DT_LNK)
			ft_printf(MAGENTA);
		else if (current->type == DT_CHR)
			ft_printf("\033[43m\033[34m");
		else if (current->type == DT_BLK)
			ft_printf("\033[1;36m\033[44m");
		else if (current->type == DT_FIFO)
			ft_printf(YELLOW);
		else if (current->type == DT_SOCK)
			ft_printf(GREEN);
		else if (current->permissions && current->permissions[2] == 'x')
			ft_printf(RED);
		else if (current->permissions && current->permissions[2] == 's')
			ft_printf("\033[41m\033[30m");
	}
}

static void	print_info(t_ls *ls, t_dir_list *current)
{
	struct stat st;
	char		buf[current->len_name];

	stat(current->path, &st);
	if (current->type == 10)
		lstat(current->path, &st);
	if (ls->l == 1)
	{
		ft_printf("%c%s\t%d\t", get_d_type(current), current->permissions, current->n_links);
		print_owner_info(ls, current);
		ft_printf("%8d\tTIME: %d\t", current->size, current->m_time, current->name);
	}
	print_color_code(ls, current);
	ft_printf("%s%s", current->name, FULL_COLOR_RESET);
	if (current->type == 10)
	{
		readlink(current->path, buf, current->len_name);
		ft_printf(" -> %s", buf);
	}

	if (ls->p == 1 && current->type == 4)
		ft_printf("/");
}

void		print_dir_list(t_ls *ls, t_dir_list *list)
{
	t_dir_list *iter;

	if (list)
		sort_list(ls, &list);
	iter = list;
	if (ls->head_folder == 1)
		ft_printf("%s\n", iter->name);
	while (iter)
	{
		print_info(ls, iter);
		NL;
		iter = iter->next;
	}
	NL;
}
