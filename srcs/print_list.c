#include "ft_ls.h"

static int	print_detail_list(t_flist *list, t_context *ctx)
{
	t_col_width	w;
	t_node		*node;

	get_aggregate_data(&w, list);
	node = list->head;
	while (node)
	{
		print_detail(node, &w, ctx);
		node = node->next;
	}
	return (0);
}

static int	print_simple_list(t_flist *list, t_context *ctx)
{
	int		col_width;
	int		rows;
	int		i;
	int		j;
	t_node	*arr;

	col_width = get_longest_name_length(list) + 1;
	if ((rows = get_rows(col_width, ctx->terminal_width, list->len)) == 0)
		return (0);
	if ((arr = list_to_arr(list)) == NULL)
		return (-1);
	i = 0;
	while (i < rows)
	{
		j = i;
		while (j < list->len)
		{
			ctx->print("%-*s", col_width, arr[j].name);
			j += rows;
		}
		ctx->print("\n");
		i++;
	}
	ft_memdel((void **)&arr);
	return (0);
}

int			print_list(t_flist *list, t_context *ctx)
{
	if (ctx->flag & FLAG_PRINT_DETAIL)
		return (print_detail_list(list, ctx));
	else
		return (print_simple_list(list, ctx));
}
