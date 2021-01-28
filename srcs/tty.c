#include "ft_ls.h"

int		get_terminal_width(void)
{
	struct winsize	w;

	if (ioctl(1, TIOCGWINSZ, &w) == -1)
		return (0);
	return (w.ws_col);
}

int		get_rows(int col_width, int terminal_width, int num_files)
{
	int		cols;
	int		rows;

	cols = terminal_width / col_width;
	if (cols == 0)
		return (0);
	rows = num_files / cols;
	if (num_files % cols != 0)
		rows++;
	return (rows);
}
