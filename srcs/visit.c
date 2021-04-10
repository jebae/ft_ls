#include "ft_ls.h"

static int		err_with_free(t_flist *list)
{
	free_list(list);
	return (-1);
}

static int		recurse(t_flist *list, t_context *ctx)
{
	t_node	*node;

	node = list->head;
	while (node)
	{
		if ((node->st.st_mode & S_IFMT) == S_IFDIR &&
			ft_strcmp(node->name, ".") != 0 &&
			ft_strcmp(node->name, "..") != 0)
		{
			ctx->print("\n");
			if (visit(node, TRUE, ctx) == -1)
				return (-1);
		}
		node = node->next;
	}
	return (0);
}

int				visit(t_node *node, int show_dir_name, t_context *ctx)
{
	t_flist	list;
	size_t	total_block_size;

	if (show_dir_name)
		ctx->print("%s:\n", node->path);
	init_flist(&list);
	total_block_size = 0;
	if (get_entry_list(node->path, &list, ctx->flag & FLAG_PRINT_HIDDEN,
			&total_block_size) == -1)
		return (err_with_free(&list));
	if (list.len == 0)
		return (0);
	sort_list(&list, ctx->cmp);
	if (ctx->flag & FLAG_PRINT_DETAIL)
		ctx->print("total %llu\n", total_block_size);
	if (print_list(&list, ctx) == -1)
		return (err_with_free(&list));
	if (ctx->flag & FLAG_RECURSIVE)
	{
		if (recurse(&list, ctx) == -1)
			return (err_with_free(&list));
	}
	free_list(&list);
	return (0);
}

int				visit_current_dir(t_context *ctx)
{
	t_node	node;
	t_stat	st;

	node.path = (char *)".";
	if (lstat(node.path, &st) == -1)
	{
		err(node.path);
		return (0);
	}
	return (visit(&node, FALSE, ctx));
}
