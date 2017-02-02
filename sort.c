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
            result[i] = (char*)malloc(sizeof(char) * ft_strlen(de->d_name));
            ft_strcpy(result[i], de->d_name);
            i++;
    }
    ft_matsort(result, i);
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
                temp = (char*)malloc(sizeof(char) * ft_strlen(result[j]));
                ft_strcpy(temp, result[j]);
                ft_strcpy(result[j], result[j - 1]);
                ft_strcpy(result[j - 1], temp);
            }
            j++;
        }
        i++;
    }
    return (result);
}