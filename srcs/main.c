#include "ft_ls.h"

static int	err_with_free(t_root_list *lists)
{
	free_root_list(lists);
	return (1);
}

/*
** return value:
** -1 : error
** else: index after flag args
*/

static int	set_context(int argc, char **argv, t_context *ctx)
{
	int	i;

	init_context(ctx);
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			break ;
		if (parse_flags(argv[i] + 1, ctx) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int			main(int argc, char **argv)
{
	int			i;
	t_context	ctx;
	t_root_list	lists;

	i = set_context(argc, argv, &ctx);
	if (i == -1)
		return (1);
	if (i == argc)
		return (visit_current_dir(&ctx) == -1);
	init_root_list(&lists);
	while (i < argc)
	{
		if (classify_file(argv[i], &lists, &ctx) == -1)
			return (err_with_free(&lists));
		i++;
	}
	if (handle_classified_lists(&lists, &ctx) == -1)
		return (err_with_free(&lists));
	free_root_list(&lists);
	return (errno != 0);
}
