/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:27:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/09 19:37:56 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>

# define LS_FLAGS "GMRaflrt1"

typedef struct		s_pls
{
	char			mode[15];
	int				links;
	char			*own;
	char			*group;
	int				major;
	long long		size;
	long long		blocks;
	long			date;
	char			*name;
	char			*linkpath;
	int				not_a_dir;
}					t_pls;

void				ft_ls(const char *path, const char *flags, int args);
t_list				*ft_ls_back(const char *path, const char *flags);
void				ft_ls_front(const t_list *lst, const char *flags, \
					const char *path, int args);
void				ft_ls_rec(const t_list *lst, const char *path, \
					const char *flags);
t_list				*ft_ls_sort(t_list *lst, const char *flags);
void				ft_ls_args(int ac, char **av, int first, const char *flags);
int					ft_ls_error_file_dir(const char *path);
t_list				*ft_ls_listsort(t_list *lst, int (*cmp)(void*, void*));
long				errors(const int error, const char *letter);

# define MODE 0
# define LNKS 1
# define OWN 2
# define GROUP 3
# define MAJ 4
# define SIZE 5
# define DATE 6
# define ARGS 9
# define FILENAMEMAXLEN 255

#endif
