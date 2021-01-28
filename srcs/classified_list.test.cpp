#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "ft_ls.h"

TEST(classify_file, invalid)
{
	const char	*path = "./not_exist";
	t_list		file_list;
	t_list		dir_list;
	t_list		invalid_list;

	init_lists(&file_list, &dir_list, &invalid_list);

	ASSERT_NE(classify_file((char *)path, &file_list, &dir_list, &invalid_list), -1);
	ASSERT_EQ(file_list.len, 0);
	ASSERT_EQ(dir_list.len, 0);
	ASSERT_EQ(invalid_list.len, 1);

	free_lists(&file_list, &dir_list, &invalid_list);
}

TEST(classify_file, file)
{
	const char	*path = "./foo";
	t_list		file_list;
	t_list		dir_list;
	t_list		invalid_list;
	int			fd;

	init_lists(&file_list, &dir_list, &invalid_list);
	fd = open(path, O_CREAT, 0);
	close(fd);

	ASSERT_NE(classify_file((char *)path, &file_list, &dir_list, &invalid_list), -1);
	ASSERT_EQ(file_list.len, 1);
	ASSERT_EQ(dir_list.len, 0);
	ASSERT_EQ(invalid_list.len, 0);

	free_lists(&file_list, &dir_list, &invalid_list);
	remove(path);
}

TEST(classify_file, dir)
{
	const char	*path = "./foo";
	t_list		file_list;
	t_list		dir_list;
	t_list		invalid_list;

	init_lists(&file_list, &dir_list, &invalid_list);
	mkdir(path, 0755);

	ASSERT_NE(classify_file((char *)path, &file_list, &dir_list, &invalid_list), -1);
	ASSERT_EQ(file_list.len, 0);
	ASSERT_EQ(dir_list.len, 1);
	ASSERT_EQ(invalid_list.len, 0);

	free_lists(&file_list, &dir_list, &invalid_list);
	rmdir(path);
}
