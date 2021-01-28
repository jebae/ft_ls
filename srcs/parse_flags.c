#include "ft_ls.h"

static t_cmp	get_compare_func(int is_reverse, int sort_by_modified_at)
{
	if (is_reverse)
		return ((sort_by_modified_at) ? modified_at_asc : lexical_desc);
	else
		return ((sort_by_modified_at) ? modified_at_desc : lexical_asc);
}

int				parse_flags(char *arg, t_context *ctx)
{
	while (*arg != '\0')
	{
		if (*arg == 'l')
			ctx->flag |= FLAG_PRINT_DETAIL;
		else if (*arg == 'R')
			ctx->flag |= FLAG_RECURSIVE;
		else if (*arg == 'a')
			ctx->flag |= FLAG_PRINT_HIDDEN;
		else if (*arg == 'r')
			ctx->flag |= FLAG_SORT_REVERSE;
		else if (*arg == 't')
			ctx->flag |= FLAG_SORT_BY_MODIFIED_AT;
		else
		{
			err_invalid_option(*arg);
			return (-1);
		}
		arg++;
	}
	ctx->cmp = get_compare_func(ctx->flag & FLAG_SORT_REVERSE,
			ctx->flag & FLAG_SORT_BY_MODIFIED_AT);
	return (0);
}
