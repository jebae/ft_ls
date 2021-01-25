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
	int		is_reverse;
	int		sort_by_modified_at;

	is_reverse = FALSE;
	sort_by_modified_at = FALSE;
	while (*arg != '\0')
	{
		if (*arg == 'l')
			ctx->flag |= FLAG_PRINT_DETAIL;
		else if (*arg == 'R')
			ctx->flag |= FLAG_RECURSIVE;
		else if (*arg == 'a')
			ctx->flag |= FLAG_PRINT_HIDDEN;
		else if (*arg == 'r')
			is_reverse = TRUE;
		else if (*arg == 't')
			sort_by_modified_at = TRUE;
		else
			return (FALSE);
		arg++;
	}
	ctx->cmp = get_compare_func(is_reverse, sort_by_modified_at);
	return (TRUE);
}
