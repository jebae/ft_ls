#include <gtest/gtest.h>
#include <stdio.h>
#include "ft_ls.h"

static char		buf[1024];

static void		init_buf(void)
{
	memset(buf, 0, 1024);
}

static int		print4test(const char *format, ...)
{
	va_list	ap;
	int		res;
	char	temp[256];

	va_start(ap, format);
	res = vsprintf(temp, format, ap);
	strcat(buf, temp);
	va_end(ap);
	return (res);
}

TEST(print_detail, filetype_regular)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFREG;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], '-');
}

TEST(print_detail, filetype_directory)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFDIR;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 'd');
}

TEST(print_detail, filetype_symlink)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFLNK;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 'l');
}

TEST(print_detail, filetype_fifo)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFIFO;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 'p');
}

TEST(print_detail, filetype_character_special)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFCHR;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 'c');
}

TEST(print_detail, filetype_block_special)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFBLK;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 'b');
}

TEST(print_detail, filetype_socket)
{

	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;
	st.st_mode = 0 | S_IFSOCK;

	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_EQ(buf[0], 's');
}

TEST(print_detail, permission_0755)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 0755;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rwxr-xr-x"), NULL);
}

TEST(print_detail, permission_0644)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 0644;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rw-r--r--"), NULL);
}

TEST(print_detail, permission_4644)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 04644;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rwSr--r--"), NULL);
}

TEST(print_detail, permission_4755)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 04755;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rwsr-xr-x"), NULL);
}

TEST(print_detail, permission_2755)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 02755;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rwxr-sr-x"), NULL);
}

TEST(print_detail, permission_2644)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 02644;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rw-r-Sr--"), NULL);
}

TEST(print_detail, permission_1644)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 01644;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rw-r--r-T"), NULL);
}

TEST(print_detail, permission_1755)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 01755;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "rwxr-xr-t"), NULL);
}

TEST(print_detail, few_link)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_nlink = 1;
	w.link = 4;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "   1"), NULL);
}

TEST(print_detail, many_link)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_nlink = 1347;
	w.link = 4;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "1347"), NULL);
}

TEST(print_detail, owner)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_uid = 0;
	w.owner = 7;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "root   "), NULL);
}

TEST(print_detail, invalid_owner)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_uid = 123123123;
	w.owner = 11;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "123123123  "), NULL);
}

TEST(print_detail, group)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_gid = 0;
	w.group = 10;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "wheel     "), NULL);
}

TEST(print_detail, invalid_group)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_gid = 456456456;
	w.group = 11;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "456456456  "), NULL);
}

TEST(print_detail, owner_and_group)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_uid = 0;
	st.st_gid = 0;
	w.owner = 7;
	w.group = 9;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "root     wheel    "), NULL);
}

TEST(print_detail, small_size)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_size = 73;
	w.size = 3;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, " 73"), NULL);
}

TEST(print_detail, big_size)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_size = 1174528;
	w.size = 9;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "  1174528"), NULL);
}

TEST(print_detail, last_modified)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mtime = 1611209356;
	print_detail((char *)"", &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "Jan 21 15:09"), NULL);
	ASSERT_EQ((long)strstr(buf, "Jan 21 15:09:"), NULL);
}

TEST(print_detail, filename)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;
	const char		*name = "./foo/bar";

	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	print_detail((char *)name, &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "bar"), NULL);
	ASSERT_EQ((long)strstr(buf, "/bar"), NULL);
}

TEST(print_detail, filename_with_link)
{
	t_context		ctx;
	t_col_width		w = {0,0,0,0};
	t_stat			st;
	const char		*name = "./foo";

	symlink("../../bar", name);
	init_buf();
	memset(&st, 0, sizeof(t_stat));
	ctx.print = print4test;

	st.st_mode = 0 | S_IFLNK;
	print_detail((char *)name, &st, &w, &ctx);
	ASSERT_NE((long)strstr(buf, "foo -> ../../bar"), NULL);
	ASSERT_EQ((long)strstr(buf, "/foo -> ../../bar"), NULL);
	remove(name);
}
