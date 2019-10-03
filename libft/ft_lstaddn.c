/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddn.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 13:23:18 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 12:54:39 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddn(t_list *lst, t_list *new, size_t n)
{
	t_list	*iterate;
	size_t	x;

	x = 0;
	if (lst && new && n > 0)
	{
		iterate = lst;
		while (x < (n - 1) && iterate->next != NULL)
		{
			lst = lst->next;
			iterate = iterate->next;
			x++;
		}
		if (x == (n - 1))
		{
			iterate = lst->next;
			lst->next = new;
			new->next = iterate;
		}
	}
}
