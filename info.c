#include "list.h"

char	**get_dirs(char *argv[], int *nrdirs)
{
	char	**result;
	int		i;
	int		j;

	*nrdirs = nget_dirs(argv);
	if (*nrdirs == 0)
	{
		result = (char**)malloc(sizeof(char*) * 1);
		result[0] = (char*)malloc(sizeof(char) * 1);
		result[0][0] = '.';
		*nrdirs = 1;
		return (result);
	}
	result = (char**)malloc(sizeof(char*) * *nrdirs);
	i = 1;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			result[j] = (char*)malloc(sizeof(char) * ft_strlen(argv[i]));
			ft_strcpy(result[j], argv[i]);
			j++;
		}
		i++;
	}
	return (result);
}

int		nget_dirs(char *argv[])
{
	int		i;
	int		nr_dirs;
	
	nr_dirs = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			nr_dirs++;
		i++;
	}
	return (nr_dirs);
}

char	*get_flags(char *argv[], int *nrflags)
{
	int		i;
	int		j;
	int		contor;
	char	*result;

	contor = 0;
	*nrflags = nget_flags(argv);
	if (*nrflags == 0)
		return (NULL);
	result = (char*)malloc(sizeof(char) * *nrflags);
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				result[contor++] = argv[i][j];
				j++;
			}
		}
		i++;
	}
	return (result);
}

int		nget_flags(char *argv[])
{
	int		i;
	int		j;
	int		nr_flags;
	
	nr_flags = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				nr_flags++;
				j++;
			}
		}
		i++;
	}
	return (nr_flags);
}

t_info	*ft_no_args()
{
	t_info *result;
	
	result = (t_info*)malloc(sizeof(t_list));
	result->dirs = 1;
	result->flags = 0;
	result->nflags = NULL;
	result->ndirs = (char**)malloc(sizeof(char*));
	result->ndirs[0] = (char*)malloc(sizeof(char));
	result->ndirs[0][0] = '.';
	return (result);
}