/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/24 14:58:13 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/11 18:35:15 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_head_folder(t_ls *ls)
{
	if (ls && ls->head_folder == 1)
	{
		if (ls->G == 1)
			ft_printf(BOLD_BLUE);
		ft_printf("%s:\n", ls->folder);
		ft_printf(COLOR_RESET);
	}
}

struct dirent	*copy_ds(struct dirent *d_s)
{
	struct dirent *new;

	if (!d_s)
		return (NULL);
	new = (struct dirent *)malloc(sizeof(struct dirent));
	new->d_ino = d_s->d_ino;
	ft_strcpy(new->d_name, d_s->d_name);
	new->d_namlen = d_s->d_namlen;
	new->d_reclen = d_s->d_reclen;
	new->d_seekoff = d_s->d_seekoff;
	new->d_type = d_s->d_type;
	return (new);
}
