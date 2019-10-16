/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_search_until_specifier.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/26 17:23:26 by rcorke         #+#    #+#                */
/*   Updated: 2019/05/03 20:45:53 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_search_until_specifier(char *str, t_flags *data)
{
	char	terminating_char;
	int		i;

	if (!data->specifier)
		return (0);
	terminating_char = data->specifier;
	i = 0;
	if (str[0] == '%')
		i++;
	while (str[i] && str[i] != terminating_char)
		i++;
	return (i);
}
