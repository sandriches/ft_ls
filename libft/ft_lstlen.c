/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 17:37:36 by rcorke        #+#    #+#                 */
/*   Updated: 2019/02/04 17:39:00 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list *lst)
{
	int x;

	x = 0;
	while (lst != NULL)
	{
		x++;
		lst = lst->next;
	}
	return (x);
}
