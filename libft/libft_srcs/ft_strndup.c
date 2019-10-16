/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 14:57:42 by rcorke        #+#    #+#                 */
/*   Updated: 2019/02/02 15:00:33 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	while (i < size && s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	if (i == size)
	{
		dst[i] = '\0';
		return (dst);
	}
	else
		return (0);
}
