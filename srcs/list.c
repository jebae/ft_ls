#include "ft_ls.h"

void	init_flist(t_flist *list)
{
	ft_memset(list, 0, sizeof(t_flist));
}

void	free_list(t_flist *list)
{
	t_node	*node;
	t_node	*next;

	node = list->head;
	while (node)
	{
		next = node->next;
		ft_memdel((void **)&node->path);
		ft_memdel((void **)&node);
		node = next;
	}
}

int		add_node(char *path, char *name, t_stat *st, t_flist *list)
{
	t_node	*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	if (node == NULL)
		return (-1);
	node->next = NULL;
	node->path = path;
	node->name = name;
	node->st = *st;
	if (list->len == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->len++;
	return (0);
}

t_node	*list_to_arr(t_flist *list)
{
	int		i;
	t_node	*arr;
	t_node	*node;

	arr = (t_node *)ft_memalloc(sizeof(t_node) * list->len);
	if (arr == NULL)
		return (NULL);
	i = 0;
	node = list->head;
	while (node)
	{
		arr[i] = *node;
		node = node->next;
		i++;
	}
	return (arr);
}
