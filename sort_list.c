/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/28 13:43:18 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/07 17:47:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					dir_list_size(t_dir_list *list)
{
	t_dir_list	*iter;
	int			i;

	if (!list)
		return (0);
	iter = list;
	i = 0;
	while (iter->next)
	{
		iter = iter->next;
		i++;
	}
	return (i + 1);
}

static void			swap_first(t_dir_list **list)
{
	t_dir_list	*iter;
	t_dir_list	*next;
	t_dir_list	*nextnext;

	iter = *list;
	next = iter->next;
	nextnext = iter->next->next;
	iter->next = nextnext;
	next->next = iter;
	*list = next;
}

static void			swap(t_dir_list **prev, t_dir_list **list)
{
	t_dir_list	*iter;
	t_dir_list	*next;
	t_dir_list	*nextnext;

	iter = *list;
	next = iter->next;
	nextnext = iter->next->next;
	iter->next = nextnext;
	next->next = iter;
	*list = next;
	(*prev)->next = *list;
}

static int			compare_iter(t_dir_list *iter, t_dir_list *next, char type)
{
	if (type == 't')
	{
		if (iter->m_time < next->m_time)
			return (1);
	}
	else if (type == 'u')
	{
		if (iter->a_time < next->a_time)
			return (1);
	}
	else
	{
		if (iter->size > next->size)
			return (1);
	}
	return (0);
}

static void			sort_by(t_dir_list **list, char type)
{
	t_dir_list	*iter;
	t_dir_list	*next;
	int			len;

	iter = *list;
	len = dir_list_size(*list);
	if (compare_iter(iter, iter->next, type) == 1)
		swap_first(list);
	while (len > 0)
	{
		iter = *list;
		while (iter)
		{
			if (iter->next && iter->next->next && \
			compare_iter(iter->next, iter->next->next, type) == 1)
			{
				next = iter->next;
				iter->next = iter->next->next;
				iter->next->next = next;
			}
			iter = iter->next;
		}
		len--;
	}
}

static t_dir_list	*remove_first_hidden(t_dir_list **list)
{
	t_dir_list	*iter;
	t_dir_list	*to_free;
	t_dir_list	*head;

	iter = *list;
	while (iter && iter->name[0] == '.')
	{
		to_free = iter;
		iter = iter->next;
		free_singular_node(&to_free);
	}
	if (!iter)
		return (NULL);
	return (iter);
}

static void			remove_hidden(t_dir_list **list)
{
	t_dir_list	*iter;
	t_dir_list	*to_free;
	t_dir_list	*head;

	*list = remove_first_hidden(list);
	if (!*list)
		return ;
	iter = *list;
	head = iter;
	to_free = iter->next;
	if (!to_free)
		return ;
	while (iter && to_free)
	{
		if (to_free->name[0] == '.')
		{
			iter->next = to_free->next;
			free_singular_node(&to_free);
		}
		iter = iter->next;
		to_free = iter->next;
	}
	*list = head;
}

void				reverse_list(t_dir_list **list)
{
	t_dir_list	*prev;
	t_dir_list	*current;
	t_dir_list	*next;
	int			len;

	len = dir_list_size(*list);
	current = *list;
	prev = NULL;
	while (len > 0 && current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		len--;
	}
	*list = prev;
}

static void			sort_by_ascii(t_dir_list **list)
{
	t_dir_list	*prev;
	t_dir_list	*iter;
	t_dir_list	*next;
	int			len;

	iter = *list;
	len = dir_list_size(*list);
	if (ft_biggest_ascii_str(iter->name, iter->next->name) == 1)
		swap_first(list);
	while (len > 0)
	{
		iter = *list;
		prev = iter;
		iter = iter->next;
		while (iter && iter->next)
		{
			if (ft_biggest_ascii_str(iter->name, \
			iter->next->name) == 1)
				swap(&prev, &iter);
			prev = iter;
			iter = iter->next;
		}
		len--;
	}
}

void				sort_list(t_ls *ls, t_dir_list **list)
{
	if (!list || !*list || !(*list)->next)
		return ;
	sort_by_ascii(list);
	if (ls->a == 0)
	{
		remove_hidden(list);
		if (dir_list_size(*list) == 0)
		{
			*list = NULL;
			return ;
		}
	}
	if (ls->sort == 't')
		sort_by(list, 't');
	else if (ls->sort == 'u')
		sort_by(list, 'u');
	else if (ls->sort == 'S')
		sort_by(list, 'S');
	if (ls->r == 1)
		reverse_list(list);
}
