#include "ft_ls.h"

int		lexical_asc(t_node *n1, t_node *n2)
{
	return ((ft_strcmp(n1->name, n2->name) > 0 ? 1 : 0));
}

int		lexical_desc(t_node *n1, t_node *n2)
{
	return ((ft_strcmp(n1->name, n2->name) >= 0 ? 0 : 1));
}

int		modified_at_asc(t_node *n1, t_node *n2)
{
	if (n1->st.st_mtimespec.tv_sec == n2->st.st_mtimespec.tv_sec)
	{
		if (n1->st.st_mtimespec.tv_nsec == n2->st.st_mtimespec.tv_nsec)
			return (lexical_desc(n1, n2));
		return (n1->st.st_mtimespec.tv_nsec > n2->st.st_mtimespec.tv_nsec);
	}
	return (n1->st.st_mtimespec.tv_sec > n2->st.st_mtimespec.tv_sec);
}

int		modified_at_desc(t_node *n1, t_node *n2)
{
	if (n1->st.st_mtimespec.tv_sec == n2->st.st_mtimespec.tv_sec)
	{
		if (n1->st.st_mtimespec.tv_nsec == n2->st.st_mtimespec.tv_nsec)
			return (lexical_asc(n1, n2));
		return (n1->st.st_mtimespec.tv_nsec < n2->st.st_mtimespec.tv_nsec);
	}
	return (n1->st.st_mtimespec.tv_sec < n2->st.st_mtimespec.tv_sec);
}
