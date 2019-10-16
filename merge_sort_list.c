/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge_sort_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 13:00:28 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/13 15:02:11 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			split(t_dir_list *source, t_dir_list **front, \
t_dir_list **back)
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

static t_dir_list	*merge_sorted(t_dir_list *a, t_dir_list *b, t_ls *ls)
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

void				merge_sort_list(t_ls *ls, t_dir_list **head)
{
	t_dir_list *a;
	t_dir_list *b;

	if (!*head || !(*head)->next)
		return ;
	split(*head, &a, &b);
	merge_sort_list(ls, &a);
	merge_sort_list(ls, &b);
	*head = merge_sorted(a, b, ls);
}
