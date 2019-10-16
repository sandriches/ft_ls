/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrpl.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 18:22:49 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:51:16 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrpl(char *haystack, int index, int replaced_length, char *needle)
{
	char	*return_string;
	int		x[2];

	x[1] = ft_strlen(needle);
	return_string = ft_strnew(((size_t)ft_strlen(haystack) - replaced_length) \
	+ ft_strlen(needle) + 1);
	x[0] = 0;
	while (x[0] < index)
	{
		return_string[x[0]] = haystack[x[0]];
		x[0]++;
	}
	while (x[0] < index + x[1])
	{
		return_string[x[0]] = *needle;
		x[0]++;
		needle++;
	}
	while (haystack[x[0] - (x[1] - replaced_length)] != '\0')
	{
		return_string[x[0]] = haystack[x[0] - (x[1] - replaced_length)];
		x[0]++;
	}
	return (return_string);
}
