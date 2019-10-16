/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_percent.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 19:21:01 by rcorke         #+#    #+#                */
/*   Updated: 2019/04/30 15:25:47 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		percent_path(t_flags *data)
{
	data->result = (char *)malloc(sizeof(char) * 2);
	data->result[0] = '%';
	data->result[1] = '\0';
	data->result = make_width(data);
}
