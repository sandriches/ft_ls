/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge_sort_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 13:00:28 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/11 18:44:26 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	biggest_str(t_dir_list *iter, t_dir_list *next, t_ls *ls, int num)
{
	if (ft_biggest_ascii_str(iter->name, next->name) == num)
		return (1);
	return (0);
}

static int	bs_norm_function(t_dir_list *iter, t_dir_list *next, \
t_ls *ls, int which)
{
	if (which == 1)
	{
		if (iter->size > next->size)
			return (1);
		else if (iter->size == next->size)
			if (ft_biggest_ascii_str(iter->name, next->name) == 2)
				return (1);
	}
	else if (which == 2)
	{
		if (iter->size < next->size)
			return (1);
		else if (iter->size == next->size)
			if (ft_biggest_ascii_str(iter->name, next->name) == 1)
				return (1);
	}
	return (0);
}

static int	compare_rev_values(t_dir_list *iter, t_dir_list *next, t_ls *ls)
{
	if (ls->t == 1)
	{
		if (iter->m_time < next->m_time)
			return (1);
		else if (iter->m_time == next->m_time)
			if (ft_biggest_ascii_str(iter->name, next->name) == 1)
				return (1);
	}
	else if (ls->sort == 'U')
	{
		if (iter->a_time < next->a_time)
			return (1);
		else if (iter->a_time == next->a_time)
			if (ft_biggest_ascii_str(iter->name, next->name) == 1)
				return (1);
	}
	else if (ls->sort == 'S')
	{
		if (bs_norm_function(iter, next, ls, 2) == 1)
			return (1);
	}
	return (biggest_str(iter, next, ls, 1));
}

int			compare_values(t_dir_list *iter, t_dir_list *next, t_ls *ls)
{
	if (ls->t == 1 && ls->r == 0)
	{
		if (iter->m_time > next->m_time)
			return (1);
		else if (iter->m_time == next->m_time)
			if (ft_biggest_ascii_str(iter->name, next->name) == 2)
				return (1);
	}
	else if (ls->sort == 'U' && ls->r == 0)
	{
		if (iter->a_time > next->a_time)
			return (1);
		else if (iter->a_time == next->a_time)
			if (ft_biggest_ascii_str(iter->name, next->name) == 2)
				return (1);
	}
	else if (ls->sort == 'S' && ls->r == 0)
	{
		if (bs_norm_function(iter, next, ls, 1) == 1)
			return (1);
	}
	else if (ls->r == 0)// && ft_biggest_ascii_str(iter->name, next->name) == 2)
		return (biggest_str(iter, next, ls, 2));
	return (compare_rev_values(iter, next, ls));
}

void		split(t_dir_list *source, t_dir_list **front, t_dir_list **back, \
t_ls *ls)
{
	t_dir_list *slow;
	t_dir_list *fast;

	if (!source || !source->next)
	{
		*front = source;
		*back = NULL;
		return ;
	}
	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

t_dir_list	*merge_sorted(t_dir_list *a, t_dir_list *b, t_ls *ls)
{
	t_dir_list *rtn_node;

	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (compare_values(a, b, ls) == 1)
	{
		rtn_node = a;
		rtn_node->next = merge_sorted(a->next, b, ls);
	}
	else
	{
		rtn_node = b;
		rtn_node->next = merge_sorted(b->next, a, ls);
	}
	return (rtn_node);
}

void		merge_sort_list(t_ls *ls, t_dir_list **head)
{
	t_dir_list *a;
	t_dir_list *b;

	if (!*head || !(*head)->next)
		return ;
	split(*head, &a, &b, ls);
	merge_sort_list(ls, &a);
	merge_sort_list(ls, &b);
	*head = merge_sorted(a, b, ls);
}
