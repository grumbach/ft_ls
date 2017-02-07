/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_rec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 01:17:51 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/07 16:44:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_rec(const t_list *lst, const char *path, \
				const char *flags)
{
	DIR					*dirp;
	char				*newpath;
	char				*tmp;
	char				buf[1];

	buf[0] = 0;
	dirp = NULL;
	while (lst)
	{
		if (!(tmp = ft_strjoin("/", ((t_pls*)(lst->content))->name)) || \
			!(newpath = ft_strjoin(path, tmp)))
			errors(0, 0);
		ft_memdel((void**)&tmp);
		if ((dirp = opendir(newpath)))
		{
			if (ft_strcmp(((t_pls*)(lst->content))->name, "..") && \
				ft_strcmp(((t_pls*)(lst->content))->name, ".") && \
				readlink(newpath, buf, 1) < 0)
				ft_ls(newpath, flags, 42);
			(void)closedir(dirp);
		}
		ft_memdel((void**)&newpath);
		lst = lst->next;
	}
}
