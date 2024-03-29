/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags_and_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/26 16:45:56 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/16 15:57:59 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		no_folder_error(t_dir_list *list)
{
	ft_putstr_fd(list->path, 2);
	ft_putstr_fd(":\nft_ls: ", 2);
	perror(list->name);
	ft_putstr_fd("\n", 2);
}

static void	flags_error(t_ls *ls, char c, char help)
{
	if (help == 0)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		write(2, &c, 1);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("usage: ./ft_ls [-lRartuSnpG] [file ...]\n", 2);
	}
	else
		ft_putstr("usage: ./ft_ls [-lRartuSnpG] [file ...]\n");
	free_everything(ls, NULL);
	exit(0);
}

static void	check_for_flags_cont(t_ls *ls, char chr)
{
	if (chr == 't')
		ls->t = 1;
	if (chr == 'u' && ls->sort != 'S')
		ls->sort = 'u';
	else if (chr == 'S')
		ls->sort = 'S';
	else if (chr == 'n')
	{
		ls->n = 1;
		ls->l = 1;
	}
	else if (chr == 'h')
		flags_error(ls, 'h', 1);
}

static void	check_for_flags(t_ls *ls, char *str)
{
	int x;

	x = 1;
	while (str[x] != '\0')
	{
		if (str[x] == 'l')
			ls->l = 1;
		else if (str[x] == 'R')
			ls->rc = 1;
		else if (str[x] == 'a')
			ls->a = 1;
		else if (str[x] == 'r')
			ls->r = 1;
		else if (str[x] == 't' || str[x] == 'u' || str[x] == 'S' || \
		str[x] == 'n' || str[x] == 'h')
			check_for_flags_cont(ls, str[x]);
		else if (str[x] == 'p')
			ls->p = 1;
		else if (str[x] == 'G')
			ls->g = 1;
		else
			flags_error(ls, str[x], 0);
		x++;
	}
}

int			set_flags(int argc, char **argv, t_ls *ls)
{
	int x;

	x = 1;
	ls->l = 0;
	ls->rc = 0;
	ls->a = 0;
	ls->r = 0;
	ls->sort = 0;
	ls->n = 0;
	ls->p = 0;
	ls->g = 0;
	ls->t = 0;
	while (x <= argc)
	{
		if (argv[x] && argv[x][0] == '-')
			check_for_flags(ls, argv[x]);
		else
			return (update_flags_final(ls, x));
		x++;
	}
	return (update_flags_final(ls, x));
}
