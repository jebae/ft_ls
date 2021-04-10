#include "ft_ls.h"

static t_node	*partition(t_node *head)
{
	t_node	*slow;
	t_node	*fast;

	slow = head;
	fast = head;
	while (fast)
	{
		fast = fast->next;
		if (fast)
			fast = fast->next;
		if (!fast)
			break ;
		slow = slow->next;
	}
	fast = slow->next;
	slow->next = NULL;
	return (fast);
}

static t_node	*merge_sort(t_node *node, t_cmp cmp)
{
	t_node	*l1;
	t_node	*l2;
	t_node	sentinel;

	if (!node || !node->next)
		return (node);
	l2 = merge_sort(partition(node), cmp);
	l1 = merge_sort(node, cmp);
	node = &sentinel;
	while (l1 && l2)
	{
		if (cmp(l1, l2) == 1)
		{
			node->next = l2;
			l2 = l2->next;
		}
		else
		{
			node->next = l1;
			l1 = l1->next;
		}
		node = node->next;
	}
	node->next = (l1) ? l1 : l2;
	return (sentinel.next);
}

void			sort_list(t_flist *list, t_cmp cmp)
{
	t_node	*node;

	if (!list || !list->head)
		return ;
	list->head = merge_sort(list->head, cmp);
	node = list->head;
	while (node->next)
		node = node->next;
	list->tail = node;
}
