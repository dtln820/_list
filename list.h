#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

typedef struct		s_list
{
	char 			*name;
	struct s_list	*next;
}					t_list;

typedef struct		s_info
{
	int				dirs;
	int				flags;
	char			**ndirs;
	char			*nflags;
}					t_info;

t_info		*ft_info(int argc, char *argv[]);

char		*get_flags(int argc, char *argv[], int *nflags);

int			nget_flags(int argc, char *argv[]);

t_info		*ft_no_args();

char		**get_dirs(int argc, char *argv[], int *nrdirs);

int			nget_dirs(int argc, char *argv[]);

size_t      ft_strlen(const char *str);

char        *ft_strcpy(char *dest, const char *src);

void		ft_list(t_info *info);

void		ft_show(DIR *dr, t_info *info);

void		ft_rec(char *path);

char		*ft_createpath(char *path, char *new_path);

#endif