#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif
# include "libft.h"
# include "ft_printf.h"
#ifdef __cplusplus
}
#endif

# define TRUE			1
# define FALSE			0

typedef struct	stat	t_stat;

typedef struct			s_node
{
	char			*name;
	t_stat			st;
	struct s_node	*next;
}						t_node;

typedef struct			s_list
{
	int		len;
	t_node	*head;
	t_node	*tail;
}						t_list;

typedef int				(*t_print)(const char *format, ...);

typedef struct			s_context
{
	t_print	print;
}						t_context;

typedef struct			s_col_width
{
	int	link;
	int	owner;
	int	group;
	int	size;
}						t_col_width;

typedef int				(*t_cmp)(t_node *n1, t_node *n2);

void					init_list(t_list *list);
void					free_list(t_list *list);
int						add_node(char *name, t_stat *st, t_list *list);

void					sort_list(t_list *list, t_cmp cmp);

int						print_detail(
		char *name, t_stat *st, t_col_width *w, t_context *ctx);

#endif