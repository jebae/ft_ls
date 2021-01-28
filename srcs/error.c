#include "ft_ls.h"

void		err_invalid_option(char invalid)
{
	ft_fprintf(2, "ls: illegal option -- %c\n", invalid);
	ft_fprintf(2, "usage: ft_ls [Ralrt] [file ...]\n");
}

static void	err_operation_not_permitted(char *name)
{
	ft_fprintf(2, "ls: %s: Operation not permitted\n", name);
}

static void	err_permission_denied(char *name)
{
	ft_fprintf(2, "ls: %s: Permission denied\n", name);
}

static void	err_file_not_exist(char *name)
{
	ft_fprintf(2, "ls: %s: No such file or directory\n", name);
}

void		err(char *name)
{
	if (errno == ENOENT)
		err_file_not_exist(name);
	else if (errno == EPERM)
		err_operation_not_permitted(name);
	else if (errno == EACCES)
		err_permission_denied(name);
}
