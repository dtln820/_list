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
		dr = opendir(info->ndirs[i]);
		if (dr == NULL)
		{
			printf("ls: cannot access '%s': No such file or directory\n", info->ndirs[i]);
			return ;
		}
		ft_show(dr, info);
		i++;
		printf("\n");
		closedir(dr);
	}
}

void	ft_show(DIR *dr, t_info *info)
{
	struct dirent *de;

	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.')
			printf("%s\t", de->d_name);
	}
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