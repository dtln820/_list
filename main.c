#include <stdio.h>

int     main(int argc, char *argv[])
{
    int i;
    int j;
    
    j = 1;
    while (argv[j])
    {
        i = 0;
        while (argv[j][i])
        {
            printf("%c", argv[j][i]);
            i++;
        }
        j++;
        printf("\n");
    }
    return (0);
}