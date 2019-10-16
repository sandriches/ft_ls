/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 10:31:53 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/14 17:47:39 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <time.h>
# include <limits.h>
# include <errno.h>
# include "libft/libft_lib.h"
# define NL write(1, "\n", 1)
# define TAB write(1, "\t", 1)
# define FULL_COLOR_RESET "\033[0;0m"
# define LINK_BUF 1024

typedef struct	s_dir_list {
	char					*path;
	char					type;
	char					*permissions;
	int						uid;
	int						gid;
	char					*u_name;
	char					*g_name;
	int						n_links;
	time_t					a_time;
	time_t					m_time;
	char					*m_time_str;
	char					*a_time_str;
	unsigned long			size;
	unsigned long			blocks;
	char					*name;
	char					len_name;
	struct s_dir_list		*next;
}				t_dir_list;

typedef struct	s_ls {
	unsigned char	l;
	unsigned char	rc;
	unsigned char	a;
	unsigned char	r;
	unsigned char	t;
	unsigned char	sort;
	unsigned char	n;
	unsigned char	p;
	unsigned char	g;
	unsigned char	head_folder;
	char			*folder;
}				t_ls;

/*
**print dirent.c
*/
int				print_dirent(t_dir_list **list, DIR *dptr, t_ls *ls);
struct dirent	*get_ds_init_values(DIR *ptr, t_dir_list **list, t_ls *ls, \
char *path);

/*
**print first dirent.c
*/
int				print_first_dirent(t_dir_list **list, DIR *dptr, t_ls *ls);
void			print_single_file(struct stat st, t_ls *ls, char *path);
void			print_total_blocks(t_dir_list *list);

/*
**print functions.c
*/
void			print_info(t_ls *ls, t_dir_list *current);
void			print_dir_list(t_ls *ls, t_dir_list **list);

/*
**get rel time.c
*/
char			*get_rel_time(time_t st_time);

/*
**Utility functions
*/
void			print_head_folder(t_ls *ls);
int				update_flags_final(t_ls *ls, int x);

/*
**List functions
*/
char			*join_paths_with_slash(char *old_path, char *new_path);
void			pop_first_list(t_dir_list **list);
void			sort_print_free(t_ls *ls, t_dir_list **current, DIR **dptr);
void			join_lists(t_dir_list **to_add, t_dir_list **main_list);

/*
**add_to_dir_list.c
*/
int				add_to_dir_list(struct dirent *d_s, t_dir_list **current, \
char *path);
void			copy_stat_to_new(struct stat *st, t_dir_list **n_new);
void			copy_permissions_to_new(struct stat *st, char **str);

/*
**free_functions.c
*/
void			free_current(t_dir_list **list);
void			free_everything(t_ls *ls, t_dir_list **list);
void			free_singular_node(t_dir_list **list);
int				free_str(char **str);

/*
**flags & error
*/
int				set_flags(int argc, char **argv, t_ls *ls);
void			no_folder_error(t_dir_list *list);

/*
**merge sort
*/
void			merge_sort_list(t_ls *ls, t_dir_list **list);
int				compare_values(t_dir_list *iter, t_dir_list *next, t_ls *ls);

#endif
