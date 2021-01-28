#include <gtest/gtest.h>
#include <string.h>
#include "ft_ls.h"

static int		cmp(t_node *n1, t_node *n2)
{
	int		res;

	res = strcmp(n1->name, n2->name);
	if (res > 0)
		return (1);
	else
		return (0);
}

TEST(sort_list, even_length)
{
	t_list		list;
	t_node		*prev;
	t_node		*node;
	t_stat		st;
	const char	*names[] = {
		"c", "f", "a", "d", "b", "e",
	};
	int			count = 1;
	
	init_list(&list);
	for (int i=0; i < (int)(sizeof(names) / sizeof(char *)); i++)
	{
		char *name = (char *)malloc(strlen(names[i]) + 1);

		strcpy(name, names[i]);
		add_node(name, name, &st, &list);
	}

	sort_list(&list, cmp);
	prev = list.head;
	node = prev->next;
	while (node)
	{
		count++;
		ASSERT_EQ(cmp(prev, node), 0);
		prev = node;
		node = node->next;
	}
	ASSERT_EQ(count, (int)(sizeof(names) / sizeof(char *)));
	ASSERT_EQ(prev, list.tail);
	free_list(&list);
}

TEST(sort_list, odd_length)
{
	t_list		list;
	t_node		*prev;
	t_node		*node;
	t_stat		st;
	const char	*names[] = {
		"c", "f", "a", "d", "b",
	};
	int			count = 1;
	
	init_list(&list);
	for (int i=0; i < (int)(sizeof(names) / sizeof(char *)); i++)
	{
		char *name = (char *)malloc(strlen(names[i]) + 1);

		strcpy(name, names[i]);
		add_node(name, name, &st, &list);
	}

	sort_list(&list, cmp);
	prev = list.head;
	node = prev->next;
	while (node)
	{
		count++;
		ASSERT_EQ(cmp(prev, node), 0);
		prev = node;
		node = node->next;
	}
	ASSERT_EQ(count, (int)(sizeof(names) / sizeof(char *)));
	ASSERT_EQ(prev, list.tail);
	free_list(&list);
}

// expected no seg fault
TEST(sort_list, _1_length)
{
	t_list		list;
	t_stat		st;
	const char	*names[] = {
		"a",
	};
	
	init_list(&list);
	for (int i=0; i < (int)(sizeof(names) / sizeof(char *)); i++)
	{
		char *name = (char *)malloc(strlen(names[i]) + 1);

		strcpy(name, names[i]);
		add_node(name, name, &st, &list);
	}

	sort_list(&list, cmp);
	free_list(&list);
}

// expected no seg fault
TEST(sort_list, _0_length)
{
	t_list		list;
	
	init_list(&list);
	sort_list(&list, cmp);
	free_list(&list);
}
