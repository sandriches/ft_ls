/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 11:38:58 by rcorke         #+#    #+#                */
/*   Updated: 2019/09/24 12:44:57 by rcorke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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


static void	print_info(DIR *ptr, struct dirent *d_s)
{
	ft_printf("%s", d_s->d_name);
	return ;
}

static struct dirent	*copy_ds(struct dirent *d_s)
{
	struct dirent *new;

	if (!d_s)
		return (NULL);
	new = (struct dirent *)malloc(sizeof(struct dirent));
	new->d_ino = d_s->d_ino;
	ft_strcpy(new->d_name, d_s->d_name);
	new->d_namlen = d_s->d_namlen;
	new->d_reclen = d_s->d_reclen;
	new->d_seekoff = d_s->d_seekoff;
	new->d_type = d_s->d_type;
	return (new);
}

static void	add_to_list(struct dirent *d_s, t_dir_list **list)
{
	t_dir_list	*iter;

	if (!list || !*list)
	{
		*list = (t_dir_list *)malloc(sizeof(t_dir_list));
		(*list)->d_s = copy_ds(d_s);
		if (!*list)
		{
			free(list);
			return ;
		}
		(*list)->use = 0;
		(*list)->next = NULL;
	}
	iter = *list;
	while (iter && iter->next)
		iter = iter->next;
	iter->next = (t_dir_list *)malloc(sizeof(t_dir_list));
	iter->next->d_s = copy_ds(d_s);
	if (!iter->next->d_s)
	{
		free(iter->next);
		iter->next = NULL;
		return ;
	}
	iter->next->use = 0;
	iter->next->next = NULL;
}

// int print_all_in_dirent(DIR *ptr, char *path, t_dir_list *list)
// {
// 	int i = 0;
// 	int list_size = 0;
// 	struct dirent *d_s;

// 	ft_printf("./%s:\n", path);
// 	while (i < 3)
// 	{
// 		d_s = readdir(ptr);
// 		i++;
// 	}
// 	while (d_s)
// 	{
// 		print_info(ptr, d_s);
// 		if (d_s->d_type == 4)
// 		{
// 			add_to_list(d_s, list);
// 			list_size++;
// 		}
// 		d_s = readdir(ptr);
// 	}
// 	if (list_size == 0)
// 		return (1);
// 	while (list_size > 0)
// 	{
// 		add_to_path(path, list);
// 		add_to_ptr(path, ptr);
// 		if (print_all_in_dirent(ptr, path, list) == 0)
// 			return (1);
// 		pop_from_ptr(path, ptr);
// 		pop_from_path(path, list);
// 		list_size--;
// 	}
// 	return (0);
// }

static void print_list(t_dir_list *list)
{
	t_dir_list *iter;

	iter = list;
	while (iter)
	{
		ft_printf("%s\n", iter->d_s->d_name);
		iter = iter->next;
	}
}

static void	print_all_in_dirent_no_path(DIR *ptr, char *path, t_dir_list **list)
{
	struct dirent	*d_s;

	d_s = readdir(ptr);
	while (d_s)
	{
		if (ft_strequ(d_s->d_name, "."))
		{
			d_s = readdir(ptr);
			d_s = readdir(ptr);
			if (!d_s)
				return ;
		}
		print_info(ptr, d_s);
		if (d_s->d_type == 4)
			add_to_list(d_s, list);
		d_s = readdir(ptr);
		if (d_s)
			ft_printf("\t");
	}
	ft_printf("\n");
}

int		main(void)
{
	struct passwd	*pw_struct;
	struct group	*group_struct;
	struct stat		*stat_struct;
	struct dirent	*dirent_struct;
	DIR				*ptr_to_directory;
	gid_t			group_id;

	t_dir_list		*list;
	char			*path;

	path = NULL;
	list = NULL;
	ptr_to_directory = opendir(".");
	print_all_in_dirent_no_path(ptr_to_directory, path, &list);
	closedir(ptr_to_directory);
	exit(1);


	// dir_copy = find_folders(list_of_dirs);
	// if (get_dir_path_length(dir_path) > 0)
	// {
	// 	new_path = ft_strdup(dir_path->name);
	// 	current_path = &new_path;
	// 	*current_path = new_path;
	// }
	// while (dir_copy)
	// {
	// 	ptr_to_directory = opendir(dir_copy->name);
	// 	dirent_struct = readdir(ptr_to_directory);
	// 	dirent_struct = readdir(ptr_to_directory);
	// 	dir_copy = copy_dirent_struct(readdir(ptr_to_directory));
	// 	print_all_in_dirent(dir_copy, ptr_to_directory, head_of_dirs, &dir_path, current_path);
	// 	dir_copy = find_folders(list_of_dirs);
	// 	closedir(ptr_to_directory);
	// 	NL;
	// }
	return (0);
}
