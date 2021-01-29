#include "ft_ls.h"

static int	err_with_free(
		t_list *file_list, t_list *dir_list, t_list *invalid_list)
{
	free_lists(file_list, dir_list, invalid_list);
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
	t_list		file_list;
	t_list		dir_list;
	t_list		invalid_list;

	i = set_context(argc, argv, &ctx);
	if (i == -1)
		return (1);
	if (i == argc)
		return (visit_current_dir(&ctx) == -1);
	init_lists(&file_list, &dir_list, &invalid_list);
	while (i < argc)
	{
		if (classify_file(argv[i], &file_list, &dir_list, &invalid_list) == -1)
			return (err_with_free(&file_list, &dir_list, &invalid_list));
		i++;
	}
	if (handle_classified_lists(
			&file_list, &dir_list, &invalid_list, &ctx) == -1)
		return (err_with_free(&file_list, &dir_list, &invalid_list));
	free_lists(&file_list, &dir_list, &invalid_list);
	return (errno != 0);
}
