/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 10:31:53 by rcorke         #+#    #+#                */
/*   Updated: 2019/10/06 16:14:00 by sandRICH      ########   odam.nl         */
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
# define HERE write(1, "here\n", 5)
# define NL write(1, "\n", 1)
# define TAB write(1, "\t", 1)
# define FULL_COLOR_RESET "\033[0;0m"

// Red text and blue background
//     puts("\x1b[31m\x1b[44mHello, World");

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
	int						size;
	char					*name;
	char					len_name;
	struct s_dir_list		*next;
}				t_dir_list;

typedef struct	s_ls {
	unsigned char	l;		//list
	unsigned char	R;		//recursive
	unsigned char	a;		//hidden
	unsigned char	r;		//rev sort
	unsigned char	sort;	//sort -t[mod time]		-u[access time]		-S[size]
	unsigned char	n;
	unsigned char	p;
	unsigned char	G;
	unsigned char	head_folder;
	char			*folder;
}				t_ls;

void	temp_print_dir_list(t_dir_list *list);
struct dirent	*get_ds_init_values(DIR *ptr, int *num, t_dir_list **list);
int		print_dirent(t_dir_list **list, DIR *dptr, t_ls *ls);

// void	print_info(t_ls *ls, struct dirent *d_s);
void	print_dir_list(t_ls *ls, t_dir_list *list);
void	print_flags(t_ls *ls);

/*Utility functions */
struct dirent	*copy_ds(struct dirent *ds);
struct stat		*get_stat(char *path);
void			print_head_folder(t_ls *ls);

/*List functions */
void			pop_first_list(t_dir_list **list);
char			*join_paths_with_slash(char *old_path, char *new_path);
void			sort_print_free(t_ls *ls, t_dir_list **current, DIR **dptr);
void			join_lists(t_dir_list **to_add, t_dir_list **main_list);

/*list functions 2 */
void	sort_list(t_ls *ls, t_dir_list **list);
int		dir_list_size(t_dir_list *list);

/*add_to_dir_list.c */
int			add_to_dir_list(struct dirent *d_s, t_dir_list **current, \
char *path, char start_or_end);

void	free_current(t_dir_list **list);
void	free_everything(t_ls *ls, t_dir_list **list);
void	free_singular_node(t_dir_list **list);
void	free_str(char **str);

int		set_flags(int argc, char **argv, t_ls *ls);
void	no_folder_error(t_ls *ls, char *folder);

#endif

/*
-l LONG FORMAT
-R Recursive
-a show . files
-r reverse output
-t sort by mod time
BONUS
-u sort by access time
-S sort by size
-n display uid and gid instead of user name and group name (turns on -l)
-p display '/' after name if it is a directory
-G colour output
 */

/* -l 
file mode - number of links - owner name - group name - file size (bytes) - last modfied (Mon date hour:min) - path(name)
*/


/* STAT
Returns information about file (PATH_TO_FILE), writes into the STAT *buff.
int stat(const char *path, struct stat *buf);

Function lstat is identical but returns information about a SYMBOLIC LINK

struct stat {
    dev_t     st_dev;     / ID of device containing file
    ino_t     st_ino;     / inode number
    mode_t    st_mode;    / protection
    nlink_t   st_nlink;   / number of hard links
    uid_t     st_uid;     / user ID of owner
    gid_t     st_gid;     / group ID of owner
    dev_t     st_rdev;    / device ID (if special file)
    off_t     st_size;    / total size, in bytes
    blksize_t st_blksize; / blocksize for file system I/O
    blkcnt_t  st_blocks;  / number of 512B blocks allocated
    time_t    st_atime;   / time of last access
    time_t    st_mtime;   / time of last modification
    time_t    st_ctime;   / time of last status change
} */


/* GETPWUID
Returns a pointer to a passwd struct with info about the USER (from LDAP/ etc/passwd) - needs user ID (UID).
struct passwd *getpwuid(uid_t uid)

struct passwd {
	char   *pw_name;	   / username
    char   *pw_passwd;     / user password
    uid_t   pw_uid;        / user ID
    gid_t   pw_gid;        / group ID
    char   *pw_gecos;      / user information
    char   *pw_dir;        / home directory
    char   *pw_shell;      / shell program
}*/


/* GETGRGID
Returns a pointer to a group struct with info about the GROUP (from LDAP/ etc/passwd) - needs group ID (GID)
struct group *getgrgid(gid_t gid);

struct group {
	char   *gr_name;	  / group name
    char   *gr_passwd;    / group password
    gid_t   gr_gid;       / group ID
    char  **gr_mem;       / group members
}*/


/* GETXATTR
Get extended attribute NAME of a file (PATH_TO_FILE). Writes into BUF.
ssize_t getxattr(const char *path_to_file, const char *name, void *buf, size_t buf_size)
*/


/* LISTXATTR
Lists all extended attributes of a file (PATH_TO_FILE). Writes into list,)
ssize_t listxattr(const char *path, char *list, size_t list_size);
*/


/* READLINK
Reads symbolic links contents. Writes BUF_SIZE bytes into BUF.
ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize);
*/

/*OPEN/READ/CLOSE DIR
DIR *opendir(const char *dirname);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

struct dirent {
    ino_t          d_ino;       / inode number
    off_t          d_seekoff;       / offset to the next dirent
    unsigned short d_reclen;    / length of this record
    unsigned char  d_type;      / type of file; not supported by all file system types
	unsigned int   d_namlen		/length of name
    char           d_name[1024]; / filename
}; */