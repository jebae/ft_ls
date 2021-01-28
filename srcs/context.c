#include "ft_ls.h"

void	init_context(t_context *ctx)
{
	ft_memset(ctx, 0, sizeof(t_context));
	ctx->cmp = lexical_asc;
	ctx->terminal_width = get_terminal_width();
	ctx->print = ft_printf;
}
