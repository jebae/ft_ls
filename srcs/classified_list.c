#include "ft_ls.h"

void		init_root_list(t_root_list *lists)
{
	init_list(&lists->file);
	init_list(&lists->dir);
	init_list(&lists->invalid);
}

void		free_root_list(t_root_list *lists)
{
	free_list(&lists->file);
	free_list(&lists->dir);
	free_list(&lists->invalid);
}

int			classify_file(char *str, t_root_list *lists, t_context *ctx)
{
	char	*path;
	t_stat	st;
	t_list	*list;

	path = (char *)ft_strdup(str);
	if (path == NULL)
		return (-1);
	if (lstat(path, &st) == -1)
		list = &lists->invalid;
	else if ((st.st_mode & S_IFMT) == S_IFDIR ||
		((st.st_mode & S_IFMT) == S_IFLNK && !(ctx->flag & FLAG_PRINT_DETAIL)))
		list = &lists->dir;
	else
		list = &lists->file;
	if (add_node(path, path, &st, list) == -1)
	{
		ft_memdel((void **)&path);
		return (-1);
	}
	return (0);
}

static void	handle_invalid_list(t_list *list)
{
	t_node	*node;
	t_stat	st;

	node = list->head;
	while (node)
	{
		lstat(node->path, &st);
		err(node->path);
		node = node->next;
	}
}

int			handle_classified_lists(t_root_list *lists, t_context *ctx)
{
	t_node	*node;
	int		show_dir_name;

	sort_list(&lists->file, ctx->cmp);
	sort_list(&lists->dir, ctx->cmp);
	sort_list(&lists->invalid, lexical_asc);
	handle_invalid_list(&lists->invalid);
	if (print_list(&lists->file, ctx) == -1)
		return (-1);
	if (lists->file.len > 0 && lists->dir.len > 0)
		ctx->print("\n");
	show_dir_name = lists->dir.len +
		lists->file.len + lists->invalid.len > 1;
	node = lists->dir.head;
	while (node)
	{
		if (visit(node, show_dir_name, ctx) == -1)
			return (-1);
		node = node->next;
		if (node)
			ctx->print("\n");
	}
	return (0);
}
