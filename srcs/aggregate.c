#include "ft_ls.h"

static int		get_digit_len(unsigned long long num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static int		get_owner_len(uid_t id)
{
	struct passwd	*pw;

	pw = getpwuid(id);
	if (pw)
		return (ft_strlen(pw->pw_name));
	return (get_digit_len(id));
}

static int		get_group_len(uid_t id)
{
	struct group	*grp;

	grp = getgrgid(id);
	if (grp)
		return (ft_strlen(grp->gr_name));
	return (get_digit_len(id));
}

void			get_aggregate_data(t_col_width *w, t_flist *list)
{
	t_node		*node;
	int			len;

	ft_memset(w, 0, sizeof(t_col_width));
	node = list->head;
	while (node)
	{
		if ((len = get_digit_len(node->st.st_nlink)) > w->link)
			w->link = len;
		if ((len = get_digit_len(node->st.st_size)) > w->size)
			w->size = len;
		if ((len = get_owner_len(node->st.st_uid)) > w->owner)
			w->owner = len;
		if ((len = get_group_len(node->st.st_gid)) > w->group)
			w->group = len;
		node = node->next;
	}
}

int				get_longest_name_length(t_flist *list)
{
	t_node	*node;
	int		longest;
	int		len;

	longest = 0;
	node = list->head;
	while (node)
	{
		len = ft_strlen(node->name);
		if (len > longest)
			longest = len;
		node = node->next;
	}
	return (longest);
}
