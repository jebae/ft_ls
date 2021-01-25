#include <gtest/gtest.h>
#include <string.h>
#include "ft_ls.h"

TEST(parse_flags, flag_l)
{
	t_context	ctx;
	const char	*arg = "l";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ(ctx.flag, FLAG_PRINT_DETAIL);
	ASSERT_EQ((long)ctx.cmp, (long)lexical_asc);
}

TEST(parse_flags, flag_a)
{
	t_context	ctx;
	const char	*arg = "a";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ(ctx.flag, FLAG_PRINT_HIDDEN);
	ASSERT_EQ((long)ctx.cmp, (long)lexical_asc);
}

TEST(parse_flags, flag_R)
{
	t_context	ctx;
	const char	*arg = "R";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ(ctx.flag, FLAG_RECURSIVE);
	ASSERT_EQ((long)ctx.cmp, (long)lexical_asc);
}

TEST(parse_flags, flag_r)
{
	t_context	ctx;
	const char	*arg = "r";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ((long)ctx.cmp, (long)lexical_desc);
	ASSERT_EQ(ctx.flag, 0);
}

TEST(parse_flags, flag_t)
{
	t_context	ctx;
	const char	*arg = "t";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ((long)ctx.cmp, (long)modified_at_desc);
	ASSERT_EQ(ctx.flag, 0);
}

TEST(parse_flags, flag_rt)
{
	t_context	ctx;
	const char	*arg = "rt";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ((long)ctx.cmp, (long)modified_at_asc);
	ASSERT_EQ(ctx.flag, 0);
}

TEST(parse_flags, flag_lRa)
{
	t_context	ctx;
	const char	*arg = "lRa";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ((long)ctx.cmp, (long)lexical_asc);
	ASSERT_EQ(ctx.flag, FLAG_PRINT_DETAIL | FLAG_PRINT_HIDDEN | FLAG_RECURSIVE);
}

TEST(parse_flags, flag_lRart)
{
	t_context	ctx;
	const char	*arg = "lRart";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_TRUE(parse_flags((char *)arg, &ctx));
	ASSERT_EQ((long)ctx.cmp, (long)modified_at_asc);
	ASSERT_EQ(ctx.flag, FLAG_PRINT_DETAIL | FLAG_PRINT_HIDDEN | FLAG_RECURSIVE);
}

TEST(parse_flags, invalid_flag_case1)
{
	t_context	ctx;
	const char	*arg = "x";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_FALSE(parse_flags((char *)arg, &ctx));
}

TEST(parse_flags, invalid_flag_case2)
{
	t_context	ctx;
	const char	*arg = "lRx";

	memset(&ctx, 0, sizeof(t_context));
	ASSERT_FALSE(parse_flags((char *)arg, &ctx));
}
