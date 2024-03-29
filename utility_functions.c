/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 14:58:13 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/13 15:35:19 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_head_folder(t_ls *ls)
{
	if (ls && ls->head_folder == 1)
	{
		if (ls->g == 1)
			ft_printf(BOLD_BLUE);
		ft_printf("%s:\n", ls->folder);
		ft_printf(COLOR_RESET);
	}
}

int				update_flags_final(t_ls *ls, int x)
{
	if (ls->t == 1 && ls->sort == 'u')
	{
		ls->sort = 'U';
		ls->t = 0;
	}
	else if (ls->sort == 'S')
		ls->t = 0;
	return (x);
}
