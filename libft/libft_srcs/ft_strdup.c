/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 17:30:14 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/21 11:23:27 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	x;
	size_t	i;

	x = ft_strlen(s1);
	copy = (char *)malloc(x * sizeof(char) + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < x)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
