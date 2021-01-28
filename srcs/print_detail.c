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

static void		print_permission_and_xattr(
		mode_t mode, char *path, t_context *ctx)
{
	char	s[1024];

	s[0] = (mode & S_IRUSR) ? 'r' : '-';
	s[1] = (mode & S_IWUSR) ? 'w' : '-';
	s[2] = (mode & S_IXUSR) ? 'x' : '-';
	if (mode & S_ISUID)
		s[2] = (mode & S_IXUSR) ? 's' : 'S';
	s[3] = (mode & S_IRGRP) ? 'r' : '-';
	s[4] = (mode & S_IWGRP) ? 'w' : '-';
	s[5] = (mode & S_IXGRP) ? 'x' : '-';
	if (mode & S_ISGID)
		s[5] = (mode & S_IXGRP) ? 's' : 'S';
	s[6] = (mode & S_IROTH) ? 'r' : '-';
	s[7] = (mode & S_IWOTH) ? 'w' : '-';
	s[8] = (mode & S_IXOTH) ? 'x' : '-';
	if (mode & S_ISVTX)
		s[8] = (mode & S_IXOTH) ? 't' : 'T';
	s[9] = '\0';
	ctx->print("%s", s);
	if (listxattr(path, s, 1024, XATTR_SHOWCOMPRESSION) > 0)
		ctx->print("@");
	else
		ctx->print(" ");
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
	char		*date;
	time_t		today;
	t_timedelta	td;

	if (time(&today) != -1 && timedelta(modified_at, today, &td) != -1)
	{
		date = ctime(&modified_at);
		if (date != NULL)
		{
			if (td.year >= 1 || td.month >= 6)
			{
				date[10] = '\0';
				date[24] = '\0';
				ctx->print(" %s  %s", date + 4, date + 20);
			}
			else
			{
				date[16] = '\0';
				ctx->print(" %s", date + 4);
			}
			return ;
		}
	}
	ctx->print("             ");
}

void			print_detail(t_node *node, t_col_width *w, t_context *ctx)
{
	char	link[4097];
	int		r;
	t_stat	*st;

	st = &node->st;
	print_file_type(st->st_mode, ctx);
	print_permission_and_xattr(st->st_mode, node->path, ctx);
	ctx->print(" %*hu", w->link, st->st_nlink);
	print_owner_and_group(st, w, ctx);
	ctx->print("  %*lld", w->size, st->st_size);
	print_last_modified(st->st_mtime, ctx);
	ctx->print(" %s", node->name);
	if ((st->st_mode & S_IFMT) == S_IFLNK)
	{
		if ((r = readlink(node->path, link, 4096)) != -1)
		{
			link[r] = '\0';
			ctx->print(" -> %s", link);
		}
	}
	ctx->print("\n");
}
