#include <string.h>

size_t      ft_strlen(const char *str)
{
    size_t  i;
    
    i = 0;
    while (*str++)
        i++;
    return (i);
}

char        *ft_strcpy(char *dest, const char *src)
{
    char    *temp;
    
    temp = dest;
    while (*src != 0)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return (temp);
}