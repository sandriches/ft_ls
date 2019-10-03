/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_listdelone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:42:12 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/21 18:52:36 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
