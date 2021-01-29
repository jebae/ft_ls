#include "ft_ls.h"

void		err_invalid_option(char invalid)
{
	ft_fprintf(2, "ls: illegal option -- %c\n", invalid);
	ft_fprintf(2, "usage: ft_ls [Ralrt] [file ...]\n");
}

void		err(char *name)
{
	ft_fprintf(2, "ls: ");
	perror(name);
}
