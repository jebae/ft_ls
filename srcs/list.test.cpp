#include <gtest/gtest.h>
#include <string.h>
#include "ft_ls.h"

TEST(add_node, add_to_empty_list)
{
	t_list		list;
	t_stat		st;
	const char	*str = "./foo/bar";
	char		*name;

	init_list(&list);
	name = (char *)malloc(strlen(str) + 1);
	strcpy(name, str);

	ASSERT_TRUE(add_node(name, &st, &list));
	ASSERT_NE((long)list.head, NULL);
	ASSERT_NE((long)list.tail, NULL);
	ASSERT_EQ(list.head, list.tail);
	ASSERT_STREQ(list.head->name, str);
	ASSERT_EQ(list.len, 1);
	free_list(&list);
}

TEST(add_node, add_to_non_empty_list)
{
	t_list		list;
	t_stat		st;
	const char	*s1 = "./foo/bar";
	const char	*s2 = "./go/lang";
	const char	*s3 = "./temp";
	char		*name1;
	char		*name2;
	char		*name3;

	init_list(&list);

	name1 = (char *)malloc(strlen(s1) + 1);
	name2 = (char *)malloc(strlen(s2) + 1);
	name3 = (char *)malloc(strlen(s3) + 1);
	strcpy(name1, s1);
	strcpy(name2, s2);
	strcpy(name3, s3);

	ASSERT_TRUE(add_node(name1, &st, &list));
	ASSERT_TRUE(add_node(name2, &st, &list));
	ASSERT_TRUE(add_node(name3, &st, &list));
	ASSERT_NE(list.head, list.tail);
	ASSERT_STREQ(list.head->name, s1);
	ASSERT_STREQ(list.head->next->name, s2);
	ASSERT_STREQ(list.tail->name, s3);
	ASSERT_EQ(list.len, 3);
	free_list(&list);
}
