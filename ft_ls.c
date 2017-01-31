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
	DIR *dr;
	int i;

	i = 0;
	while (i < info->dirs)
	{
		ft_rec(info->ndirs[i]);
		i++;
	}
}

void	ft_rec(char *path)
{
	DIR *dr;
	struct dirent *de;

	dr = opendir(path);
	if (dr == NULL)
		return ;
	printf("------[%s]------\n", path);
	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.')
			printf("%s\t", de->d_name);
	}
	printf("\n\n");
	closedir(dr);
	dr = opendir(path);
	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.')
			ft_rec(ft_createpath(path, de->d_name));
	}
	closedir(dr);
}

char	*ft_createpath(char *path, char *new_path)
{
	char	*result;

	result = (char*)malloc(sizeof(char) * (strlen(path) + strlen(new_path) + 2));
	strcpy(result, path);
	strcat(result, new_path);
	return (result);
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