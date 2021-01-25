#include "ft_ls.h"

static void		print_file_type(mode_t mode, t_context *ctx)
{
	mode &= S_IFMT;
	if (mode == S_IFREG)
		ctx->print("-");
	else if (mode == S_IFDIR)
		ctx->print("d");
	else if (mode == S_IFLNK)
		ctx->print("l");
	else if (mode == S_IFIFO)
		ctx->print("p");
	else if (mode == S_IFCHR)
		ctx->print("c");
	else if (mode == S_IFBLK)
		ctx->print("b");
	else if (mode == S_IFSOCK)
		ctx->print("s");
	else
		ctx->print("?");
}

static void		print_permission(mode_t mode, t_context *ctx)
{
	char	s[10];

	s[0] = (mode & S_IRUSR) ? 'r' : '-';
	s[1] = (mode & S_IWUSR) ? 'w' : '-';
	s[2] = (mode & S_IXUSR) ? 'x' : '-';
	if (mode & S_ISUID)
		s[2] = (mode & S_IXUSR) ? 's' : 'S'; 
	s[3] = (mode & S_IRGRP) ? 'r' : '-';
	s[4] = (mode & S_IWGRP) ? 'w' : '-';
	s[5] = (mode & S_IXGRP) ? 'x' : '-';
	if (mode & S_ISGID)
		s[5] =  (mode & S_IXGRP) ? 's' : 'S'; 
	s[6] = (mode & S_IROTH) ? 'r' : '-';
	s[7] = (mode & S_IWOTH) ? 'w' : '-';
	s[8] = (mode & S_IXOTH) ? 'x' : '-';
	if (mode & S_ISVTX)
		s[8] = (mode & S_IXOTH) ? 't' : 'T'; 
	s[9] = '\0';
	ctx->print("%s", s);
}

static void		print_owner_and_group(
		t_stat *st, t_col_width *w, t_context *ctx)
{
	struct passwd	*pw;
	struct group	*grp;

	pw = getpwuid(st->st_uid);
	if (pw)
		ctx->print(" %-*s", w->owner, pw->pw_name);
	else
		ctx->print(" %-*d", w->owner, st->st_uid);
	grp = getgrgid(st->st_gid);
	if (grp)
		ctx->print("  %-*s", w->group, grp->gr_name);
	else
		ctx->print("  %-*d", w->group, st->st_gid);
}

static void		print_last_modified(time_t modified_at, t_context *ctx)
{
	char	*date;

	date = ctime(&modified_at);
	if (date)
	{
		date[16] = '\0';
		ctx->print(" %s", date + 4);
	}
	else
		ctx->print("             ");
}

int				print_detail(
		char *name, t_stat *st, t_col_width *w, t_context *ctx)
{
	char	*ptr;
	char	link[4097];

	print_file_type(st->st_mode, ctx);
	print_permission(st->st_mode, ctx);
	ctx->print("  %*d", w->link, st->st_nlink);
	print_owner_and_group(st, w, ctx);
	ctx->print("  %*lld", w->size, st->st_size);
	print_last_modified(st->st_mtime, ctx);
	ptr = name;
	while (*ptr != '\0')
		ptr++;
	while (ptr > name && *ptr != '/')
		ptr--;
	ctx->print(" %s", (*ptr == '/') ? ptr + 1 : name);
	if ((st->st_mode & S_IFMT) == S_IFLNK)
	{
		readlink(name, link, 4096);
		ctx->print(" -> %s", link);
	}
	ft_putchar('\n');
	return (TRUE);
}
