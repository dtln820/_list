#include "list.h"

t_info	*ft_info(char *argv[])
{
	t_info *result;

	result = (t_info*)malloc(sizeof(t_list));
	result->nflags = get_flags(argv, &result->flags);
	result->ndirs = get_dirs(argv, &result->dirs);
	return (result);
}

void	ft_list(t_info *info)
{
	int		i;
	t_opt	*options;

	options = ft_options(info);
	i = 0;
	while (i < info->dirs)
	{
		if (options->rec == 1)
			ft_rec(info->ndirs[i], options);
		else
		{
			if (info->dirs > 1)
				printf("%s:\n", info->ndirs[i]);
			ft_simple(info->ndirs[i], options);
		}
		i++;
		if (i < info->dirs && options->rec != 1)
			printf("\n");
	}
}

void	ft_simple(char *path, t_opt *options)
{
	DIR *dr;
	char	**folders;
	int		i;

	i = 0;
	dr = opendir(path);
	folders = ft_sort(dr, options);
	while (folders[i])
	{
		if (folders[i][0] != '.' && options->hid != 1)
			ft_pwrite(folders[i], options, ft_createpath(path, folders[i]));
		else if (options->hid == 1) // strcmp(folders[i], ".") != 0 && strcmp(folders[i], "..") != 0 && 
			ft_pwrite(folders[i], options, ft_createpath(path, folders[i]));
		i++;
	}
	printf("\n");
	closedir(dr);
}

t_opt	*ft_options(t_info *info)
{
	int		i;
	t_opt	*result;
	
	result = (t_opt*)malloc(sizeof(t_opt));
	i = 0;
	while (i < info->flags)
	{
		if (info->nflags[i] == 'l')
			result->lon = 1;
		else if (info->nflags[i] == 'R')
			result->rec = 1;
		else if (info->nflags[i] == 'r')
			result->rev = 1;
		else if (info->nflags[i] == 'a')
			result->hid = 1;
		else if (info->nflags[i] == 't')
			result->tim = 1;
		i++;
	}
	return (result);
}

void	ft_rec(char *path, t_opt *options)
{
	DIR		*dr;
	char	**folders;
	int		i;

	i = 0;
	dr = opendir(path);
	if (dr == NULL)
		return ;
	printf("%s:\n", path);
	folders = ft_sort(dr, options);
	while (folders[i])
	{
		if (folders[i][0] != '.' && options->hid != 1)
			ft_pwrite(folders[i], options, ft_createpath(path, folders[i]));
		else if (options->hid == 1) // strcmp(folders[i], ".") != 0 && strcmp(folders[i], "..") != 0 && 
			ft_pwrite(folders[i], options, ft_createpath(path, folders[i]));
		i++;
	}
	closedir(dr);
	dr = opendir(path);
	if (dr != NULL)
		printf("\n");
	i = 0;
	while (folders[i])
	{
		if (folders[i][0] != '.' && options->hid != 1)
			ft_rec(ft_createpath(path, folders[i]), options);
		else if (strcmp(folders[i], ".") != 0 && strcmp(folders[i], "..") != 0 && options->hid == 1)
			ft_rec(ft_createpath(path, folders[i]), options);
		i++;
	}
	closedir(dr);
}

char	*ft_createpath(char *path, char *new_path)
{
	char	*result;

	result = (char*)malloc(sizeof(char) * (strlen(path) + strlen(new_path) + 2));
	strcpy(result, path);
	strcat(result, "/");
	strcat(result, new_path);
	return (result);
}

void	ft_pwrite(char *name, t_opt *options, char *path)
{
	struct stat *fileStat;
	struct passwd *psswd;
	struct group *grp;

	fileStat = malloc(sizeof(struct stat));
	stat(path, fileStat);
	psswd = getpwuid(fileStat->st_uid);
	grp = getgrgid(psswd->pw_gid);
	if (options->lon == 1)
	{
		ft_privs(fileStat);
		printf("\t%lu\t%s\t%s\t%lu\t%ld\t%s\n", fileStat->st_nlink, psswd->pw_name, grp->gr_name, fileStat->st_size, fileStat->st_mtime, name);
	}
	else
		printf("%s\t", name);
}

int		main(int argc, char *argv[])
{
	t_info *info;
	if (argc < 2)
		info = ft_no_args();
	else
		info = ft_info(argv);
	ft_list(info);
	return (0);
}