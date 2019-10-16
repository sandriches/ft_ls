/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_rel_time.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 14:51:44 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/15 14:19:14 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	move_i_forward(char *str, int i, int e_or_not)
{
	if (e_or_not % 2 == 1)
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	else
	{
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (i);
}

static char	*remove_excess(char *str)
{
	char	*rtn;
	int		i;
	int		start;
	int		e_or_not;

	if (!str)
		return (NULL);
	i = 0;
	e_or_not = 1;
	while (e_or_not <= 8)
	{
		i = move_i_forward(str, i, e_or_not);
		if (e_or_not == 3)
			start = i;
		e_or_not++;
	}
	if (i > 3)
		i -= 3;
	rtn = ft_strnew(i - start + 1);
	return (ft_strncpy(rtn, &str[start], i - start));
}

static int	is_more_than_year_old(char *str)
{
	int		x;
	int		len;
	char	*year;

	x = ft_strlen(str) - 2;
	len = x + 1;
	while (ft_isdigit(str[x]))
		x--;
	year = ft_strsub(str, x, len - x);
	len = ft_atoi(year);
	free(year);
	if (len > 1970)
		return (1);
	return (0);
}

static char	*get_year_str(char *str)
{
	int		x;
	int		len;
	char	*year;
	char	*tmpstr;
	char	*rtn_str;

	len = ft_strlen(str) - 1;
	x = len - 2;
	while (ft_isdigit(str[x]))
		x--;
	year = ft_strsub(str, x, len - x);
	x--;
	while (ft_isdigit(str[x]) || str[x] == ':')
		x--;
	x--;
	len = x;
	tmpstr = ft_strsub(str, 4, len - 2);
	rtn_str = ft_strjoin(tmpstr, year);
	free(tmpstr);
	free(year);
	return (rtn_str);
}

char		*get_rel_time(time_t st_time)
{
	time_t		time_val;
	time_t		difference;
	char		*rtn_str;
	char		*time_str;

	time_val = time(&time_val);
	difference = (time_t)(time_val - st_time);
	time_str = ctime(&difference);
	if (is_more_than_year_old(time_str) == 0)
		rtn_str = remove_excess(ctime(&st_time));
	else
		rtn_str = get_year_str(ctime(&st_time));
	return (rtn_str);
}
