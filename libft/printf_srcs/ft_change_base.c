/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_change_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/23 17:59:20 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 16:46:16 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	make_base(char c)
{
	if (c >= 0 && c <= 9)
		return ('0' + c);
	else
		return (55 + c);
}

static char	*get_quot(int quot, int base, char *str)
{
	char	*rtnstr;
	int		rem;
	int		tmpquote;
	int		x;

	x = 1;
	tmpquote = quot;
	while (tmpquote >= base)
	{
		x++;
		tmpquote /= base;
	}
	rtnstr = ft_strnew(x);
	x--;
	while (quot >= base)
	{
		rem = quot % base;
		rtnstr[x] = str[rem];
		x--;
		quot /= base;
	}
	rtnstr[x] = make_base(quot);
	return (rtnstr);
}

static char	*get_quot_long(unsigned long quot, unsigned int base, char *str)
{
	char			*rtnstr;
	unsigned long	rem;
	unsigned long	tmpquote;
	int				x;

	x = 1;
	tmpquote = quot;
	while (tmpquote >= base)
	{
		x++;
		tmpquote /= base;
	}
	rtnstr = ft_strnew(x);
	x--;
	while (quot >= base)
	{
		rem = quot % base;
		rtnstr[x] = str[rem];
		x--;
		quot /= base;
	}
	rtnstr[x] = make_base(quot);
	return (rtnstr);
}

char		*ft_change_base(char *nbr, int oldbase, int newbase, int is_long)
{
	char			*str;
	char			*rtnstring;
	int				number;
	unsigned long	long_number;

	rtnstring = 0;
	if (oldbase < 2 || oldbase > 16 || newbase < 2 || newbase > 16 || !nbr)
		return (0);
	str = ft_strnew(17);
	ft_strcpy(str, "0123456789ABCDEF");
	if (is_long == 1)
	{
		long_number = ft_get_decimal_unsigned_long(nbr, oldbase);
		rtnstring = get_quot_long(long_number, newbase, str);
	}
	else if (is_long == -1)
	{
		number = ft_get_decimal(nbr, oldbase);
		rtnstring = get_quot(number, newbase, str);
	}
	ft_strdel(&str);
	ft_strdel(&nbr);
	return (rtnstring);
}
