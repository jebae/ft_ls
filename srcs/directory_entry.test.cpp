#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "ft_ls.h"

TEST(get_entry_list, visible_files)
{
	const char	*dirname = "./toystory";
	const char	*files[] = {
		"./toystory/woody.txt",
		"./toystory/buzz.txt",
		"./toystory/bullseye.txt",
		"./toystory/jessie.txt",
	};
	const char	*subdirs[] = {
		"./toystory/1",
		"./toystory/2",
		"./toystory/3",
	};
	int			fd;
	size_t		total;
	t_flist		list;
	t_node		*node;

	init_flist(&list);

	// make directory for test
	mkdir(dirname, 0755);

	for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
	{
		fd = open(files[i], O_CREAT, 0);
		close(fd);
	}
	for (int i=0; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
	{
		mkdir(subdirs[i], 0755);
	}

	// test
	ASSERT_NE(get_entry_list((char *)dirname, &list, FALSE, &total), -1);
	ASSERT_EQ(list.len,
		(int)(sizeof(files) / sizeof(char *)) + (int)(sizeof(subdirs) / sizeof(char *)));
	node = list.head;
	while (node)
	{
		if ((node->st.st_mode & S_IFMT) == S_IFDIR)
		{
			int found = FALSE;

			for (int i=0; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
			{
				if (strcmp(subdirs[i], node->path) == 0)
				{
					found = TRUE;
					ASSERT_STREQ(get_pure_name((char *)subdirs[i]), node->name);
				}
			}
			ASSERT_TRUE(found);
		}
		else
		{
			int found = FALSE;

			for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
			{
				if (strcmp(files[i], node->path) == 0)
				{
					found = TRUE;
					ASSERT_STREQ(get_pure_name((char *)files[i]), node->name);
				}
			}
			ASSERT_TRUE(found);
		}
		node = node->next;
	}

	// clean directory for test
	for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
	{
		remove(files[i]);
	}
	for (int i=0; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
	{
		rmdir(subdirs[i]);
	}
	rmdir(dirname);
	free_list(&list);
}

TEST(get_entry_list, with_hidden_files)
{
	const char	*dirname = "./toystory";
	const char	*files[] = {
		"./toystory/woody.txt",
		"./toystory/buzz.txt",
		"./toystory/bullseye.txt",
		"./toystory/jessie.txt",
	};
	const char	*subdirs[] = {
		"./toystory/.",
		"./toystory/..",
		"./toystory/1",
		"./toystory/2",
		"./toystory/3",
	};
	int			fd;
	size_t		total;
	t_flist		list;
	t_node		*node;

	init_flist(&list);

	// make directory for test
	mkdir(dirname, 0755);

	for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
	{
		fd = open(files[i], O_CREAT, 0);
		close(fd);
	}
	for (int i=2; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
	{
		mkdir(subdirs[i], 0755);
	}

	// test
	ASSERT_NE(get_entry_list((char *)dirname, &list, TRUE, &total), -1);
	ASSERT_EQ(list.len,
		(int)(sizeof(files) / sizeof(char *)) + (int)(sizeof(subdirs) / sizeof(char *)));
	node = list.head;
	while (node)
	{
		if ((node->st.st_mode & S_IFMT) == S_IFDIR)
		{
			int found = FALSE;

			for (int i=0; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
			{
				if (strcmp(subdirs[i], node->path) == 0)
				{
					found = TRUE;
					ASSERT_STREQ(get_pure_name((char *)subdirs[i]), node->name);
				}
			}
			ASSERT_TRUE(found);
		}
		else
		{
			int found = FALSE;

			for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
			{
				if (strcmp(files[i], node->path) == 0)
				{
					found = TRUE;
					ASSERT_STREQ(get_pure_name((char *)files[i]), node->name);
				}
			}
			ASSERT_TRUE(found);
		}
		node = node->next;
	}

	// clean directory for test
	for (int i=0; i < (int)(sizeof(files) / sizeof(char *)); i++)
	{
		remove(files[i]);
	}
	for (int i=2; i < (int)(sizeof(subdirs) / sizeof(char *)); i++)
	{
		rmdir(subdirs[i]);
	}
	rmdir(dirname);
	free_list(&list);
}

TEST(get_entry_list, directory_not_exist)
{
	const char	*dirname = "./not_exist";
	size_t		total;
	t_flist		list;

	init_flist(&list);
	ASSERT_NE(get_entry_list((char *)dirname, &list, TRUE, &total), -1);
	ASSERT_EQ(list.len, 0);
}
