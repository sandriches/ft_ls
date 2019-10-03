/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_listdelone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:42:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/17 18:40:03 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *iterate;
	t_list *delete;

	iterate = *alst;
	while (iterate->next != NULL)
	{
		delete = iterate;
		iterate = iterate->next;
		del(delete->content, delete->content_size);
		delete->next = NULL;
		free(delete);
	}
	del(iterate->content, iterate->content_size);
	free(iterate);
	*alst = NULL;
}
