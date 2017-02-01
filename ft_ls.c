#include "list.h"

t_info	*ft_info(int argc, char *argv[])
{
	t_info *result;
	
	result = (t_info*)malloc(sizeof(t_list));
	result->nflags = get_flags(argc, argv, &result->flags);
	result->ndirs = get_dirs(argc, argv, &result->dirs);
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
	struct dirent *de;
	
	dr = opendir(path);
	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.' && options->hid != 1)
			//printf("%s\t", de->d_name);
			ft_pwrite(de, options);
		else if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0 && options->hid == 1)
			printf("%s\t", de->d_name);
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
	DIR				*dr;
	struct dirent	*de;

	dr = opendir(path);
	if (dr == NULL)
		return ;
	printf("%s:\n", path);
	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.' && options->hid != 1)
			printf("%s\t", de->d_name);
		else if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0 && options->hid == 1)
			printf("%s\t", de->d_name);
	}
	printf("\n");
	closedir(dr);
	dr = opendir(path);
	if (dr != NULL)
		printf("\n");
	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.' && options->hid != 1)
			ft_rec(ft_createpath(path, de->d_name), options);
		else if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0 && options->hid == 1)
			ft_rec(ft_createpath(path, de->d_name), options);
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

void	ft_pwrite(struct dirent *de, t_opt *options)
{
	struct stat fileStat;
	struct passwd *psswd;
	struct group *grp;

	psswd = malloc(sizeof(struct passwd));
	stat(de->d_name, &fileStat);
	grp = getgrgid(fileStat.st_gid);
	psswd = getpwuid(fileStat.st_uid);
	if (options->lon == 1)
	{
		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		printf("\t%lu\t%s\t%s\t%lu\t%lu\t%s\n", fileStat.st_nlink, psswd->pw_name, grp->gr_name, fileStat.st_size, fileStat.st_mtime, de->d_name);
	}
	else
		printf("%s\t", de->d_name);
}

int		main(int argc, char *argv[])
{
	t_info *info;
	if (argc < 2)
		info = ft_no_args();
	else
		info = ft_info(argc, argv);
	ft_list(info);
	return (0);
}