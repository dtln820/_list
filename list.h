#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>

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

typedef struct		s_opt
{
	int				lon;
	int				rec;
	int				rev;
	int				hid;
	int				tim;
}					t_opt;

t_info		*ft_info(char *argv[]);

char		*get_flags(char *argv[], int *nflags);

int			nget_flags(char *argv[]);

t_info		*ft_no_args();

char		**get_dirs(char *argv[], int *nrdirs);

int			nget_dirs(char *argv[]);

size_t      ft_strlen(const char *str);

char        *ft_strcpy(char *dest, const char *src);

void		ft_list(t_info *info);

void		ft_show(DIR *dr, t_info *info);

void		ft_rec(char *path, t_opt *options);

char		*ft_createpath(char *path, char *new_path);

t_opt		*ft_options(t_info *info);

void		ft_simple(char *path, t_opt *options);

void		ft_pwrite(char *name, t_opt *options, char *path);

char		**ft_sort(DIR *dr, t_opt* options);

char    	**ft_matsort(char **result, int x);

int         ft_strcmp(const char *str1, const char *str2);

void		ft_privs(struct stat *fileStat);

#endif