#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "ft_ls.h"

TEST(classify_file, invalid)
{
	const char	*path = "./not_exist";
	t_root_list	lists;
	t_context	ctx;

	init_root_list(&lists);
	init_context(&ctx);

	ASSERT_NE(classify_file((char *)path, &lists, &ctx), -1);
	ASSERT_EQ(lists.file.len, 0);
	ASSERT_EQ(lists.dir.len, 0);
	ASSERT_EQ(lists.invalid.len, 1);

	free_root_list(&lists);
}

TEST(classify_file, file)
{
	const char	*path = "./foo";
	t_root_list	lists;
	t_context	ctx;
	int			fd;

	init_root_list(&lists);
	init_context(&ctx);
	fd = open(path, O_CREAT, 0);
	close(fd);

	ASSERT_NE(classify_file((char *)path, &lists, &ctx), -1);
	ASSERT_EQ(lists.file.len, 1);
	ASSERT_EQ(lists.dir.len, 0);
	ASSERT_EQ(lists.invalid.len, 0);

	free_root_list(&lists);
	remove(path);
}

TEST(classify_file, dir)
{
	const char	*path = "./foo";
	t_root_list	lists;
	t_context	ctx;

	init_root_list(&lists);
	init_context(&ctx);
	mkdir(path, 0755);

	ASSERT_NE(classify_file((char *)path, &lists, &ctx), -1);
	ASSERT_EQ(lists.file.len, 0);
	ASSERT_EQ(lists.dir.len, 1);
	ASSERT_EQ(lists.invalid.len, 0);

	free_root_list(&lists);
	rmdir(path);
}

TEST(classify_file, sym_link_with_detail_print)
{
	const char	*path = "./foo";
	t_root_list	lists;
	t_context	ctx;

	init_root_list(&lists);
	init_context(&ctx);
	ctx.flag |= FLAG_PRINT_DETAIL;
	symlink("../../bar", path);

	ASSERT_NE(classify_file((char *)path, &lists, &ctx), -1);
	ASSERT_EQ(lists.file.len, 1);
	ASSERT_EQ(lists.dir.len, 0);
	ASSERT_EQ(lists.invalid.len, 0);

	free_root_list(&lists);
	remove(path);
}

TEST(classify_file, sym_link_with_simple_print)
{
	const char	*path = "./foo";
	t_root_list	lists;
	t_context	ctx;

	init_root_list(&lists);
	init_context(&ctx);
	symlink("../../bar", path);

	ASSERT_NE(classify_file((char *)path, &lists, &ctx), -1);
	ASSERT_EQ(lists.file.len, 0);
	ASSERT_EQ(lists.dir.len, 1);
	ASSERT_EQ(lists.invalid.len, 0);

	free_root_list(&lists);
	remove(path);
}
