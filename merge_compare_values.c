/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge_compare_values.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 14:35:26 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/13 14:37:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		big_str(t_dir_list *iter, t_dir_list *next, t_ls *ls)
{
	if (ls->r == 1)
	{
		if (ft_biggest_ascii_str(iter->name, next->name) == 1)
			return (1);
	}
	else
	{
		if (ft_biggest_ascii_str(iter->name, next->name) == 2)
			return (1);
	}
	return (0);
}

static int		compare_rev_values(t_dir_list *iter, t_dir_list *next, t_ls *ls)
{
	if (ls->t == 1 && ls->r == 1)
	{
		if (iter->m_time < next->m_time)
			return (1);
		else if (iter->m_time == next->m_time && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->sort == 'U' && ls->r == 1)
	{
		if (iter->a_time < next->a_time)
			return (1);
		else if (iter->a_time == next->a_time && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->sort == 'S' && ls->r == 1)
	{
		if (iter->size < next->size)
			return (1);
		else if (iter->size == next->size && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->r == 1 && ft_biggest_ascii_str(iter->name, next->name) == 1)
		return (1);
	return (0);
}

int				compare_values(t_dir_list *iter, t_dir_list *next, t_ls *ls)
{
	if (ls->t == 1 && ls->r == 0)
	{
		if (iter->m_time > next->m_time)
			return (1);
		else if (iter->m_time == next->m_time && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->sort == 'U' && ls->r == 0)
	{
		if (iter->a_time > next->a_time)
			return (1);
		else if (iter->a_time == next->a_time && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->sort == 'S' && ls->r == 0)
	{
		if (iter->size > next->size)
			return (1);
		else if (iter->size == next->size && big_str(iter, next, ls) == 1)
			return (1);
	}
	else if (ls->r == 0)
		if (ft_biggest_ascii_str(iter->name, next->name) == 2)
			return (1);
	return (compare_rev_values(iter, next, ls));
}
