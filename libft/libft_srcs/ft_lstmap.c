/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:45:46 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/25 13:19:47 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list *iterate;
	t_list *map;

	if (lst)
	{
		map = f(lst);
		if (!map)
			return (NULL);
		iterate = lst->next;
		if (iterate != NULL)
			map->next = ft_lstmap(lst->next, f);
		return (map);
	}
	return (0);
}
