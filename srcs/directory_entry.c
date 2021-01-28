#include "ft_ls.h"

static char	*concat_path(int len_dir, char *dir, char *entry_name)
{
	char	*path;

	path = (char *)ft_memalloc(len_dir + ft_strlen(entry_name) + 2);
	if (path == NULL)
		return (NULL);
	ft_strcpy(path, dir);
	path[len_dir] = '/';
	ft_strcat(path, entry_name);
	return (path);
}

static int	is_hidden(char *name)
{
	return (name[0] == '.');
}

/*
** return value:
**  0 : no error, not added
**  1 : no error, added
** -1 : error, not added
*/

static int	add_entry(char *name, char *path, t_list *list,
		size_t *total_block_size)
{
	int		len_dir;
	char	*entry_name;
	t_stat	st;

	len_dir = ft_strlen(path);
	entry_name = concat_path(len_dir, path, name);
	if (entry_name == NULL)
		return (-1);
	if (lstat(entry_name, &st) == -1)
	{
		err(name);
		ft_memdel((void **)&entry_name);
		return (0);
	}
	if (add_node(entry_name, entry_name + len_dir + 1, &st, list) == -1)
	{
		ft_memdel((void **)&entry_name);
		return (-1);
	}
	*total_block_size += st.st_blocks;
	return (1);
}

int			get_entry_list(
		char *path, t_list *list, int include_hidden, size_t *total_block_size)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
	{
		err(get_pure_name(path));
		return (0);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_hidden(entry->d_name) && !include_hidden)
			continue ;
		if (add_entry(entry->d_name, path, list, total_block_size) == -1)
		{
			closedir(dir);
			return (-1);
		}
	}
	if (closedir(dir) == -1)
		return (-1);
	return (0);
}
