/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 19:05:44 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 19:07:02 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list *lst, t_list *new)
{
	if (lst && new)
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
		new->next = NULL;
	}
}
