#include "ft_ls.h"

void		init_lists(
		t_list *file_list, t_list *dir_list, t_list *invalid_list)
{
	init_list(file_list);
	init_list(dir_list);
	init_list(invalid_list);
}

void		free_lists(
		t_list *file_list, t_list *dir_list, t_list *invalid_list)
{
	free_list(file_list);
	free_list(dir_list);
	free_list(invalid_list);
}

int			classify_file(char *str,
		t_list *file_list, t_list *dir_list, t_list *invalid_list)
{
	char	*path;
	t_stat	st;
	t_list	*list;

	path = (char *)ft_strdup(str);
	if (path == NULL)
		return (-1);
	if (lstat(path, &st) == -1)
		list = invalid_list;
	else if ((st.st_mode & S_IFMT) == S_IFDIR)
		list = dir_list;
	else
		list = file_list;
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

int			handle_classified_lists(t_list *file_list,
		t_list *dir_list, t_list *invalid_list, t_context *ctx)
{
	t_node	*node;
	int		show_dir_name;

	sort_list(file_list, ctx->cmp);
	sort_list(dir_list, ctx->cmp);
	sort_list(invalid_list, lexical_asc);
	handle_invalid_list(invalid_list);
	if (print_list(file_list, ctx) == -1)
		return (-1);
	if (file_list->len > 0 && dir_list->len > 0)
		ctx->print("\n");
	show_dir_name = dir_list->len + file_list->len + invalid_list->len > 1;
	node = dir_list->head;
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
