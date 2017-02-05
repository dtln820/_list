#include "list.h"

char    **ft_sort(DIR *dr, t_opt* options)
{
	struct dirent   *de;
	char            **result;
	int             i;

	i = 0;
	while ((de = readdir(dr)) != NULL)
		i++;
	rewinddir(dr);
	result = (char**)malloc(sizeof(char*) * i + 1);
	result[i] = NULL;
	i = 0;
	while ((de = readdir(dr)) != NULL)
	{
			result[i] = (char*)malloc(sizeof(char) * (ft_strlen(de->d_name) + 1));
			ft_strcpy(result[i], de->d_name);
			result[i][ft_strlen(de->d_name)] = '\0';
			i++;
	}
	if (options->rev == 1 && options->tim != 1)
		ft_revsort(result, i);
	else if (options->rev != 1 && options->tim != 1)
		ft_matsort(result, i);
	else if (options->rev != 1 && options->tim == 1)
		ft_timesort(result, i);
	else if (options->rev == 1 && options->tim == 1)
		ft_timerev(result, i);
	return (result);
}

char	**ft_timerev(char **result, int x)
{
	int			i;
	int			j;
	char		*temp;

	i = 1;
	while (i < x)
	{
		j = 1;
		while (j < x)
		{
			if (ft_cmptime(result[j - 1], result[j]) > 0)
			{
				temp = (char*)malloc(sizeof(char) * ft_strlen(result[j]));
				ft_strcpy(temp, result[j]);
				free(result[j]);
				result[j] = (char*)malloc(sizeof(char) * ft_strlen(result[j - 1]));
				ft_strcpy(result[j], result[j - 1]);
				free(result[j - 1]);
				result[j - 1] = (char*)malloc(sizeof(char) * ft_strlen(temp));
				ft_strcpy(result[j - 1], temp);
			}
			j++;
		}
		i++;
	}
	return (result);
}

char	**ft_timesort(char **result, int x)
{
	int			i;
	int			j;
	char		*temp;

	i = 1;
	while (i < x)
	{
		j = 1;
		while (j < x)
		{
			if (ft_cmptime(result[j - 1], result[j]) < 0)
			{
				temp = (char*)malloc(sizeof(char) * ft_strlen(result[j]));
				ft_strcpy(temp, result[j]);
				free(result[j]);
				result[j] = (char*)malloc(sizeof(char) * ft_strlen(result[j - 1]));
				ft_strcpy(result[j], result[j - 1]);
				free(result[j - 1]);
				result[j - 1] = (char*)malloc(sizeof(char) * ft_strlen(temp));
				ft_strcpy(result[j - 1], temp);
			}
			j++;
		}
		i++;
	}
	return (result);
}

int		ft_cmptime(char *first, char *second)
{
	struct stat	*file1;
	struct stat	*file2;
	double		seconds;
	
	file1 = malloc(sizeof(struct stat));
	file2 = malloc(sizeof(struct stat));
	stat(first, file1);
	stat(second, file2);
	seconds = difftime(file1->st_mtime, file2->st_mtime);
	if (seconds < 0)
		return (-1);
	else if (seconds > 0)
		return (1);
	return (0);
}

char    **ft_revsort(char **result, int x)
{
	int     i;
	int     j;
	char    *temp;
	
	i = 1;
	while (i < x)
	{
		j = 1;
		while (j < x)
		{
			if (ft_strcmp(result[j - 1], result[j]) < 0)
			{
				temp = (char*)malloc(sizeof(char) * ft_strlen(result[j]));
				ft_strcpy(temp, result[j]);
				free(result[j]);
				result[j] = (char*)malloc(sizeof(char) * ft_strlen(result[j - 1]));
				ft_strcpy(result[j], result[j - 1]);
				free(result[j - 1]);
				result[j - 1] = (char*)malloc(sizeof(char) * ft_strlen(temp));
				ft_strcpy(result[j - 1], temp);
			}
			j++;
		}
		i++;
	}
	return (result);
}

char    **ft_matsort(char **result, int x)
{
	int     i;
	int     j;
	char    *temp;

	i = 1;
	while(i < x)
	{
		j = 1;
		while (j < x)
		{
			if (ft_strcmp(result[j - 1], result[j]) > 0)
			{
				temp = (char*)malloc(sizeof(char) * (ft_strlen(result[j]) + 1));
				ft_strcpy(temp, result[j]);
				temp[ft_strlen(result[j])] = '\0';
				free(result[j]);
				result[j] = (char*)malloc(sizeof(char) * (ft_strlen(result[j - 1]) + 1));
				ft_strcpy(result[j], result[j - 1]);
				result[j][ft_strlen(result[j - 1])] = '\0';
				free(result[j - 1]);
				result[j - 1] = (char*)malloc(sizeof(char) * (ft_strlen(temp) + 1));
				result[j - 1][ft_strlen(temp)] = '\0';
				ft_strcpy(result[j - 1], temp);
			}
			j++;
		}
		i++;
	}
	return (result);
}
