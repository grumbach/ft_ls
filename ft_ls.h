/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:27:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 17:11:09 by agrumbac         ###   ########.fr       */
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
	long long		size;
	long long		blocks;
	long			date;
	char			*name;
}					t_pls;

void				ft_ls(const char *path, const char *flags);
void				errors(const int error, const char *letter);
t_list				*ft_ls_back(const char *path, const char *flags);
void				ft_ls_front(const t_list *lst, const char *flags);
void				ft_ls_rec(const t_list *lst, const char *path, \
					const char *flags);
t_list				*ft_ls_sort(t_list *lst, const char *flags);

#endif
