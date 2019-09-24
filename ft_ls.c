/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcorke <rcorke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 11:38:58 by rcorke         #+#    #+#                */
/*   Updated: 2019/09/24 16:35:10 by rcorke        ########   odam.nl         */
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

static void	pop_path(char **path)
{
	int		len;
	char	*new_path;
	char	*to_free;

	len = ft_strlen(*path);
	while (len > 0 && (*path)[len] != '/')
		len--;
	if (len == 0)
	{
		free(*path);
		*path = ft_strnew(0);
		return ;
	}
	(*path)[len] = '\0';
	to_free = &(*path)[len + 1];
}

static char	*join_paths_with_slash(char *old_path, char *new_path)
{
	char	*rtn_path;
	int		len;
	int		len_old_path;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len_old_path = ft_strlen(old_path);
	len = len_old_path + ft_strlen(new_path) + 1;
	rtn_path = ft_strnew(len);
	while (i < len_old_path)
	{
		rtn_path[i] = old_path[i];
		i++;
	}
	rtn_path[i] = '/';
	i++;
	len_old_path = ft_strlen(new_path);
	j = 0;
	while (j < len_old_path)
	{
		rtn_path[i] = new_path[j];
		i++;
		j++;
	}
	rtn_path[i] = '\0';
	free(old_path);
	free(new_path);
	return (rtn_path);
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

static void	new_list(struct dirent *d_s, t_dir_list **list)
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
	return ;
}

static void	add_to_front_of_list(struct dirent *d_s, t_dir_list **list)
{
	t_dir_list	*new;

	if (!list || !*list)
		return (new_list(d_s, list));
	new = (t_dir_list *)malloc(sizeof(t_dir_list));
	new->d_s = copy_ds(d_s);
	new->next = *list;
	new->use = 0;
	*list = new;
}

static void	add_to_list(struct dirent *d_s, t_dir_list **list)
{
	t_dir_list	*iter;

	if (!list || !*list)
		new_list(d_s, list);
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

static void		pop_first_list(t_dir_list **list)
{
	t_dir_list *to_free;

	if (!list || !(*list))
		return ;
	to_free = *list;
	*list = (*list)->next;
	free(to_free);
	to_free = NULL;
}

static void		add_to_path(char **path, t_dir_list **list)
{
	char 	*new;
	char	*old;

	if (!list)
		return ;
	if (!path || !*path)
	{
		*path = ft_strdup((*list)->d_s->d_name);
		pop_first_list(list);
		return ;
	}
	new = ft_strdup((*list)->d_s->d_name);
	old = *path;
	*path = join_paths_with_slash(old, new);
	pop_first_list(list);
}

int		print_all_in_dirent(DIR *ptr, char **path, t_dir_list **list)
{
	static int j;
	int i = 0;
	int list_size = 0;
	struct dirent *d_s;

	if (j == 100)
		exit(1);
	ft_printf("%s:\n", *path);
	d_s = readdir(ptr);
	while (i < 2)
	{
		d_s = readdir(ptr);
		i++;
	}
	if (!d_s)
	{
		ft_printf("\n");
		return (1);
	}
	while (d_s)
	{
		print_info(ptr, d_s);
		if (d_s->d_type == 4)
		{
			add_to_front_of_list(d_s, list);
			list_size++;
		}
		d_s = readdir(ptr);
		if (d_s)
			ft_printf("\t");
	}
	ft_printf("\n\n");
	j++;
	if (list_size == 0)
		return (0);
	while (list_size > 0)
	{
		add_to_path(path, list);
		closedir(ptr);
		ptr = opendir(*path);
		// ft_printf("PTR: %p\n", ptr);
		if (print_all_in_dirent(ptr, path, list) == 1)
			return (0);
		pop_path(path);
		list_size--;
	}
	return (1);
}


static int	print_all_in_dirent_no_path(DIR *ptr, char **path, t_dir_list **list)
{
	struct dirent	*d_s;
	int size;

	size = 0;
	d_s = readdir(ptr);
	while (d_s)
	{
		if (ft_strequ(d_s->d_name, "."))
		{
			d_s = readdir(ptr);
			d_s = readdir(ptr);
			if (!d_s)
				return (0);
		}
		print_info(ptr, d_s);
		if (d_s->d_type == 4)
		{
			add_to_list(d_s, list);
			size++;
		}
		d_s = readdir(ptr);
		if (d_s)
			ft_printf("\t");
	}
	ft_printf("\n");
	return (size);
}

int		main(void)
{
	struct passwd	*pw_struct;
	struct group	*group_struct;
	struct stat		*stat_struct;
	struct dirent	*dirent_struct;
	DIR				*ptr;
	gid_t			group_id;

	t_dir_list		*list;
	char			*path;
	int				first_size;

	path = ft_strdup(".");
	list = NULL;
	ptr = opendir(path);
	first_size = print_all_in_dirent_no_path(ptr, &path, &list);
	closedir(ptr);
	add_to_path(&path, &list);
	ptr = opendir(path);
	while (first_size >= 0)
	{
		print_all_in_dirent(ptr, &path, &list);
		pop_path(&path);
		if (first_size == 0)
			break ;
		add_to_path(&path, &list);
		ptr = opendir(path);
		ft_printf("FIRST SIZE: %d\n", first_size);
		first_size--;
	}
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
