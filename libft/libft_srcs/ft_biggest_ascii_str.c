/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biggest_ascii_str.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 16:33:17 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/03 16:33:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int				ft_biggest_ascii_str(char *str1, char *str2)
{
	int x;

	x = 0;
	while (str1[x] && str2[x] && str1[x] == str2[x])
		x++;
	if (str1[x] == '\0' || (str1[x] && str2[x] && str1[x] < str2[x]))
		return (2);
	else
		return (1);
}
