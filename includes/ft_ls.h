#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include <sys/xattr.h>
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

# define TRUE						1
# define FALSE						0
# define FLAG_PRINT_DETAIL			0x01
# define FLAG_RECURSIVE				0x02
# define FLAG_PRINT_HIDDEN			0x04
# define FLAG_SORT_REVERSE			0x08
# define FLAG_SORT_BY_MODIFIED_AT	0x10

typedef struct stat			t_stat;

typedef struct				s_node
{
	char			*path;
	char			*name;
	t_stat			st;
	struct s_node	*next;
}							t_node;

typedef struct				s_flist
{
	int		len;
	t_node	*head;
	t_node	*tail;
}							t_flist;

typedef struct				s_root_list
{
	t_flist	file;
	t_flist	dir;
	t_flist	invalid;
}							t_root_list;

typedef int					(*t_print)(const char *format, ...);
typedef int					(*t_cmp)(t_node *n1, t_node *n2);

typedef struct				s_context
{
	int				flag;
	int				terminal_width;
	t_cmp			cmp;
	t_print			print;
}							t_context;

typedef struct				s_col_width
{
	int		link;
	int		owner;
	int		group;
	int		size;
}							t_col_width;

char						*get_pure_name(char *path);

void						init_flist(t_flist *list);
void						free_list(t_flist *list);
int							add_node(
		char *path, char *name, t_stat *st, t_flist *list);
t_node						*list_to_arr(t_flist *list);

void						sort_list(t_flist *list, t_cmp cmp);

void						print_detail(
		t_node *node, t_col_width *w, t_context *ctx);

int							lexical_asc(t_node *n1, t_node *n2);
int							lexical_desc(t_node *n1, t_node *n2);
int							modified_at_asc(t_node *n1, t_node *n2);
int							modified_at_desc(t_node *n1, t_node *n2);

int							parse_flags(char *arg, t_context *ctx);

int							get_entry_list(
		char *path, t_flist *list, int include_hidden, size_t *total_block_size);

void						get_aggregate_data(t_col_width *w, t_flist *list);
int							get_longest_name_length(t_flist *list);

int							get_rows(
		int col_width, int terminal_width, int num_files);
int							get_terminal_width(void);

int							print_list(t_flist *list, t_context *ctx);

int							visit(
		t_node *node, int show_dir_name, t_context *ctx);
int							visit_current_dir(t_context *ctx);

void						init_context(t_context *ctx);

void						err(char *name);
void						err_invalid_option(char invalid);

void						init_root_list(t_root_list *lists);
void						free_root_list(t_root_list *lists);
int							classify_file(
		char *str, t_root_list *lists, t_context *ctx);
int							handle_classified_lists(
		t_root_list *lists, t_context *ctx);

#endif
