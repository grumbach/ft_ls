/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 11:32:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			fill_info(t_pls *info, struct dirent *file)
{
	info->name = ft_strdup(file->d_name);
	return (0);
}

t_list				*ft_ls_back(const char *path, const char *flags)
{
	t_list				*lst;
	t_list				*tmp;
	t_pls				*info;
	DIR					*dirp;
	struct dirent		*file;

	lst = NULL;
	dirp = NULL;
	if (!(dirp = opendir(path)))
		errors(0, path);
	while ((file = readdir(dirp)))
	{
		if (!(info = ft_memalloc(sizeof(t_pls))) || fill_info(info, file) || \
			!(tmp = ft_lstnew(info, sizeof(t_pls))))
			errors(0, 0);
		ft_memdel((void**)&info);
		if (!lst)
			lst = tmp;
		else
			ft_lstaddend(&lst, tmp);
	}
	(void)closedir(dirp);
	return (lst);
}
