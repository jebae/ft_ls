#include "ft_ls.h"

char	*get_pure_name(char *path)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			j = i + 1;
		i++;
	}
	return (path + j);
}
