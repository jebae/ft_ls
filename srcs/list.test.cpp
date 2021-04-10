#include <gtest/gtest.h>
#include <string.h>
#include "ft_ls.h"

TEST(add_node, add_to_empty_list)
{
	t_flist		list;
	t_stat		st;
	const char	*str = "./foo/bar";
	char		*path;

	init_flist(&list);
	path = (char *)malloc(strlen(str) + 1);
	strcpy(path, str);

	ASSERT_EQ(add_node(path, path + 6, &st, &list), 0);
	ASSERT_NE((long)list.head, NULL);
	ASSERT_NE((long)list.tail, NULL);
	ASSERT_EQ(list.head, list.tail);
	ASSERT_STREQ(list.head->path, str);
	ASSERT_EQ(list.len, 1);
	free_list(&list);
}

TEST(add_node, add_to_non_empty_list)
{
	t_flist		list;
	t_stat		st;
	const char	*s1 = "./foo/bar";
	const char	*s2 = "./go/lang";
	const char	*s3 = "./temp";
	char		*path1;
	char		*path2;
	char		*path3;

	init_flist(&list);

	path1 = (char *)malloc(strlen(s1) + 1);
	path2 = (char *)malloc(strlen(s2) + 1);
	path3 = (char *)malloc(strlen(s3) + 1);
	strcpy(path1, s1);
	strcpy(path2, s2);
	strcpy(path3, s3);

	ASSERT_EQ(add_node(path1, path1 + 6, &st, &list), 0);
	ASSERT_EQ(add_node(path2, path2 + 5, &st, &list), 0);
	ASSERT_EQ(add_node(path3, path3 + 2, &st, &list), 0);
	ASSERT_NE(list.head, list.tail);
	ASSERT_STREQ(list.head->path, s1);
	ASSERT_STREQ(list.head->next->path, s2);
	ASSERT_STREQ(list.tail->path, s3);
	ASSERT_EQ(list.len, 3);
	free_list(&list);
}

TEST(list_to_arr, should_have_same_data)
{
	t_flist	list;
	t_node	node[5];
	const char	*paths[5] = {
		"./toystory/buzz"
		"./toystory/woody",
		"./harry",
		"./potter",
		"./toystory/bullseye",
	};
	const char	*names[5] = {
		"buzz",
		"woody",
		"harry",
		"potter",
		"bullseye",
	};
	t_node	*arr;
	int		len;

	init_flist(&list);
	len = (int)(sizeof(node) / sizeof(t_node));
	for (int i=0; i < len - 1; i++)
	{
		node[i].path = (char *)paths[i];
		node[i].name = (char *)names[i];
		node[i].next = &node[i + 1];
	}
	node[len - 1].next = NULL;
	node[len - 1].path = (char *)paths[len - 1];
	node[len - 1].name = (char *)names[len - 1];
	list.head = node;
	list.len = len;

	arr = list_to_arr(&list);

	ASSERT_NE((long)arr, NULL);
	for (int i=0; i < len; i++)
	{
		ASSERT_STREQ(arr[i].path, node[i].path);
		ASSERT_STREQ(arr[i].name, node[i].name);
	}
	free(arr);
}
