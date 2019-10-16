/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 14:33:02 by rcorke        #+#    #+#                 */
/*   Updated: 2019/02/11 12:34:24 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_struct(int fd, t_list **lst)
{
	t_list *rtn_node;
	t_list *iterate;

	iterate = *lst;
	while (iterate != NULL)
	{
		if (iterate->content_size == (size_t)fd)
			return (iterate);
		iterate = iterate->next;
	}
	rtn_node = ft_lstnew(0, 0);
	rtn_node->content_size = fd;
	rtn_node->content = ft_strnew(0);
	ft_lstadd(lst, rtn_node);
	return (*lst);
}

static char		*fill_line(char **leftover, char **line)
{
	int		len;
	char	*tmp;

	if (ft_memchr(*leftover, '\n', ft_strlen(*leftover)) != NULL)
	{
		len = ft_strcharloc(*leftover);
		tmp = *leftover;
		*line = ft_strndup(*leftover, len);
		*leftover = ft_strdup(tmp + len + 1);
		free(tmp);
	}
	else
	{
		*line = ft_strdup(*leftover);
		ft_memdel((void **)leftover);
		free(*leftover);
	}
	return (*line);
}

static int		last_fill_line(char **leftover, char **line)
{
	fill_line(leftover, line);
	return (1);
}

static int		read_line(int fd, char **leftover, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		tmp = *leftover;
		*leftover = ft_strjoin(*leftover, buf);
		free(tmp);
		if (ft_memchr(buf, '\n', ret) != NULL || ret < BUFF_SIZE)
		{
			*line = fill_line(leftover, line);
			return (1);
		}
	}
	if (*leftover && ft_strlen(*leftover))
		return (last_fill_line(leftover, line));
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*leftover;
	t_list			*tmp;
	int				check;

	if (!line)
		return (-1);
	if (!leftover)
		leftover = get_struct(fd, &leftover);
	tmp = get_struct(fd, &leftover);
	check = read_line(fd, (char **)&tmp->content, line);
	if (check == 0)
		return (0);
	else if (check == 1)
		return (1);
	return (-1);
}
