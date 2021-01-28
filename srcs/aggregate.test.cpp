#include <gtest/gtest.h>
#include "ft_ls.h"

TEST(get_aggregate_data, link)
{
	t_list		list;
	t_node		node[5];
	int			len;
	t_col_width	w;

	len = (int)(sizeof(node) / sizeof(t_node));
	for (int i=0; i < len - 1; i++)
	{
		node[i].next = &node[i + 1];
	}
	node[len - 1].next = NULL;

	node[0].st.st_nlink = 10;
	node[1].st.st_nlink = 1;
	node[2].st.st_nlink = 100;
	node[3].st.st_nlink = 1000;
	node[4].st.st_nlink = 10;
	list.head = &node[0];

	get_aggregate_data(&w, &list);
	ASSERT_EQ(w.link, 4);
}

TEST(get_aggregate_data, size)
{
	t_list		list;
	t_node		node[5];
	int			len;
	t_col_width	w;

	len = (int)(sizeof(node) / sizeof(t_node));
	for (int i=0; i < len - 1; i++)
	{
		node[i].next = &node[i + 1];
	}
	node[len - 1].next = NULL;

	node[0].st.st_size = 10;
	node[1].st.st_size = 1;
	node[2].st.st_size = 100;
	node[3].st.st_size = 1000;
	node[4].st.st_size = 10;
	list.head = &node[0];

	get_aggregate_data(&w, &list);
	ASSERT_EQ(w.size, 4);
}

TEST(get_longest_name_length, normal_case)
{
	t_list		list;
	t_node		node[5];
	const char	*names[5] = {
		"a",
		"ab",
		"abcdefg",
		"ab",
		"abcde",
	};
	int			len;

	len = (int)(sizeof(node) / sizeof(t_node));

	for (int i=0; i < len - 1; i++)
	{
		node[i].next = &node[i + 1];
	}
	node[len - 1].next = NULL;

	for (int i=0; i < len; i++)
	{
		node[i].name = (char *)names[i];
	}
	list.head = &node[0];

	ASSERT_EQ(get_longest_name_length(&list), (int)strlen("abcdefg"));
}
