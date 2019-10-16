/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 18:03:32 by rcorke        #+#    #+#                 */
/*   Updated: 2019/01/27 13:02:38 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*buf;
	int		slen;
	size_t	x;

	slen = (int)ft_strlen(s);
	buf = (char *)malloc(sizeof(char) * slen + 1);
	ft_memcpy(buf, s, slen);
	buf[slen] = '\0';
	x = 0;
	s[slen] = '\0';
	slen--;
	while (slen >= 0)
	{
		s[slen] = buf[x];
		x++;
		slen--;
	}
	free(buf);
	return (s);
}
