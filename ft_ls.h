/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 10:31:53 by rcorke         #+#    #+#                */
/*   Updated: 2019/09/24 14:19:26 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include "ft_printf.h"
#define HERE write(1, "here\n", 5)
#define NL write(1, "\n", 1)

typedef struct	s_dir_list {
	struct dirent			*d_s;
	struct s_dir_list		*next;
	int						use;
}				t_dir_list;

void	print_dir_list(t_dir_list *list);
void	print_info(DIR *ptr, struct dirent *d_s);

#endif
