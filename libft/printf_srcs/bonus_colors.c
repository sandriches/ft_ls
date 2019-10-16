/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/25 17:35:15 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/28 16:43:36 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*search_for_colors_2(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{')
		{
			if (!ft_strncmp(&str[i], OUR_BOLD_YELLOW, 8))
				str = ft_strrpl(str, i, 8, BOLD_YELLOW);
			else if (!ft_strncmp(&str[i], OUR_MAGENTA, 9))
				str = ft_strrpl(str, i, 9, MAGENTA);
			else if (!ft_strncmp(&str[i], OUR_BOLD_MAGENTA, 9))
				str = ft_strrpl(str, i, 9, BOLD_MAGENTA);
			else if (!ft_strncmp(&str[i], OUR_CYAN, 6))
				str = ft_strrpl(str, i, 6, CYAN);
			else if (!ft_strncmp(&str[i], OUR_BOLD_CYAN, 6))
				str = ft_strrpl(str, i, 6, BOLD_CYAN);
			else if (!ft_strncmp(&str[i], OUR_RESET, 3))
				str = ft_strrpl(str, i, 3, COLOR_RESET);
		}
		i++;
	}
	return (str);
}

char		*search_for_colors(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '{')
		{
			if (!ft_strncmp(&str[i], OUR_RED, 5))
				str = ft_strrpl(str, i, 5, RED);
			else if (!ft_strncmp(&str[i], OUR_BOLD_RED, 5))
				str = ft_strrpl(str, i, 5, BOLD_RED);
			else if (!ft_strncmp(&str[i], OUR_GREEN, 7))
				str = ft_strrpl(str, i, 7, GREEN);
			else if (!ft_strncmp(&str[i], OUR_BOLD_GREEN, 7))
				str = ft_strrpl(str, i, 7, BOLD_GREEN);
			else if (!ft_strncmp(&str[i], OUR_BLUE, 6))
				str = ft_strrpl(str, i, 6, BLUE);
			else if (!ft_strncmp(&str[i], OUR_BOLD_BLUE, 6))
				str = ft_strrpl(str, i, 6, BOLD_BLUE);
			else if (!ft_strncmp(&str[i], OUR_YELLOW, 8))
				str = ft_strrpl(str, i, 8, YELLOW);
		}
		i++;
	}
	return (str);
}
