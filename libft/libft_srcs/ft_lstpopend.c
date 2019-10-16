/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstpopend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 19:27:35 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 19:28:37 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpopend(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		free(lst->content);
		free(lst);
		lst = NULL;
	}
}
