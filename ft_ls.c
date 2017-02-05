#include "list.h"

t_info	*ft_info(char *argv[])
{
	t_info	*result;
	int		i;
	char	*temp;

	i = 0;
	result = (t_info*)malloc(sizeof(t_list));
	temp = get_flags(argv, &result->flags);
	result->nflags = get_flags(argv, &result->flags);
	result->ndirs = get_dirs(argv, &result->dirs);
	return (result);
}

void	ft_list(t_info *info)
{
	DIR		*dr;
	int		i;
	t_opt	*options;

	options = ft_options(info);
	i = 0;
	while (i < info->dirs)
	{
		if (options->rec == 1)
		{
			if (!(dr = opendir(info->ndirs[i])))
				printf("ls: cannot access %s: No such file or directory\n", info->ndirs[i]);
			else
				ft_rec(info->ndirs[i], options);
		}
		else
		{
			if (!(dr = opendir(info->ndirs[i])))
				printf("ls: cannot access %s: No such file or directory\n", info->ndirs[i]);
			else if (info->dirs > 1)
			{
				printf("%s:\n", info->ndirs[i]);
				ft_simple(info->ndirs[i], options);
			}
			else
				ft_simple(info->ndirs[i], options);
		}
		i++;
		if (i < info->dirs && options->rec != 1)
			printf("\n");
	}
	free(options);
}

void	ft_simple(char *path, t_opt *options)
{
	DIR		*dr;
	char	**folders;
	int		i;
	char	*temp;

	i = 0;
	dr = opendir(path);
	folders = ft_sort(dr, options);
	while (folders[i])
	{
		temp = ft_createpath(path, folders[i]);
		if (folders[i][0] != '.' && options->hid != 1)
			ft_pwrite(folders[i], options, temp);
		else if (options->hid == 1) 
			ft_pwrite(folders[i], options, temp);
		i++;
		free(temp);
	}
	printf("\n");
	closedir(dr);
	free(folders);
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
	char	*temp;

	i = 0;
	dr = opendir(path);
	if (dr == NULL)
		return ;
	printf("%s:\n", path);
	folders = ft_sort(dr, options);
	while (folders[i])
	{
		temp = ft_createpath(path, folders[i]);
		if (folders[i][0] != '.' && options->hid != 1)
			ft_pwrite(folders[i], options, temp);
		else if (options->hid == 1)
			ft_pwrite(folders[i], options, temp);
		i++;
		free(temp);
	}
	closedir(dr);
	dr = opendir(path);
	if (dr != NULL)
		printf("\n");
	i = 0;
	while (folders[i])
	{
		temp = ft_createpath(path, folders[i]);
		if (folders[i][0] != '.' && options->hid != 1)
			ft_rec(temp, options);
		else if (strcmp(folders[i], ".") != 0 && strcmp(folders[i], "..") != 0 && options->hid == 1)
			ft_rec(temp, options);
		i++;
		free(temp);
	}
	closedir(dr);
	free(folders);
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
	struct stat		*fileStat;
	struct passwd	*psswd;
	struct group	*grp;
	char			*temp;
	
	fileStat = malloc(sizeof(struct stat));
	if (lstat(path, fileStat) == -1)
		printf("Path : %s | %s\n", path, strerror(errno));
	psswd = getpwuid(fileStat->st_uid);
	grp = getgrgid(psswd->pw_gid);
	if (options->lon == 1)
	{
		ft_privs(fileStat);
		temp = (char*)malloc(sizeof(char) * strlen(ctime(&fileStat->st_mtime)));
		ft_strcpy(temp, ctime(&fileStat->st_mtime));
		temp[16] = '\0';
		printf("\t%hu\t%s\t%s\t%lld\t%s\t%s\n", fileStat->st_nlink, psswd->pw_name, grp->gr_name, fileStat->st_size, temp+4, name);
		free(temp);
	}
	else
		printf("%s\t", name);
	free(fileStat);
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
