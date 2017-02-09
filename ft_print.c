#include "list.h"

void	ft_privs(struct stat *fileStat)
{
	if (S_ISDIR(fileStat->st_mode))
		printf("d");
	else if (S_ISLNK(fileStat->st_mode))
		printf("l");
	else if (S_ISCHR(fileStat->st_mode))
		printf("c");
	else if (S_ISBLK(fileStat->st_mode))
		printf("b");
	else if (S_ISFIFO(fileStat->st_mode))
		printf("p");
	else
		printf("-");
	printf((fileStat->st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat->st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat->st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat->st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat->st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat->st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat->st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat->st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat->st_mode & S_IXOTH) ? "x" : "-");
}

int		ft_gettotal(char **folders, t_opt *options, char *path)
{
	int			result;
	int			i;
	struct stat	*fileStat;

	fileStat = malloc(sizeof(struct stat));
	i = 0;
	result = 0;
	while (folders[i])
	{
		if (options->hid == 1)
		{
			lstat(ft_createpath(path, folders[i]), fileStat);
			result += fileStat->st_blocks;
		}
		else if (folders[i][0] != '.' && options->hid != 1)
		{
			lstat(ft_createpath(path, folders[i]), fileStat);
			result += fileStat->st_blocks;
		}
		i++;
	}
	free(fileStat);
	return (result);
}

int		ft_veropt(t_opt *o, t_info *n)
{
	int		ver;
	int		i;

	i = 0;
	ver = 0;
	while (i < n->flags)
	{
		if (n->nflags[i] == 'l')
			ver++;
		else if (n->nflags[i] == 'R')
			ver++;
		else if (n->nflags[i] == 'r')
			ver++;
		else if (n->nflags[i] == 'a')
			ver++;
		else if (n->nflags[i] == 't')
			ver++;
		else if (n->nflags[i] == '1')
			ver++;
		i++;
	}
	if (ver != n->flags)
	{
		printf("ft_ls: illegal option\nusage: ft_ls [-Rlatr] [file ...]\n");
		return (-1);
	}
	return (1);
}
