#include "ft_ls.h"

void	init_list(t_list *list)
{
	ft_memset(list, 0, sizeof(t_list));
}

void	free_list(t_list *list)
{
	t_node	*node;
	t_node	*next;

	node = list->head;
	while (node)
	{
		next = node->next;
		ft_memdel((void **)&node->name);
		ft_memdel((void **)&node);
		node = next;
	}
}

int		add_node(char *name, t_stat *st, t_list *list)
{
	t_node	*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	if (node == NULL)
		return (FALSE);
	node->next = NULL;
	node->name = name;
	node->st = *st;
	if (list->len == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->len++;
	return (TRUE);
}
