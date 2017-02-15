/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 05:50:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/15 21:57:04 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_ls_error_file_dir(const char *path)
{
	DIR					*dirp;
	struct stat			stats;

	if (!path)
		return (1);
	if ((dirp = opendir(path)))
		return (3 + 0 * (int)closedir(dirp));
	if (stat(path, &stats) != -1 && !(S_ISDIR(stats.st_mode)))
		return (2);
	return (1);
}

static void		free_char(void *str, size_t size)
{
	(void)size;
	ft_memdel(&str);
}

static void		ls_caller(const t_list *lst, const char *flags, int args)
{
	t_list		*tmp;
	t_list		*files;

	while (lst)
	{
		files = NULL;
		if (ft_ls_error_file_dir((char*)(lst->content)) == 2)
			while (lst)
			{
				if (ft_ls_error_file_dir((char*)(lst->content)) == 2)
				{
					tmp = ft_ls_back((char*)(lst->content), flags);
					if (!files)
						files = tmp;
					else
						ft_lstaddend(&files, tmp);
					lst = lst->next;
				}
				else
					break ;
			}
		(files ? ft_ls_front(ft_ls_sort(files, flags), flags, 0, args) :
		ft_ls((char*)(lst->content), flags, args));
		lst = (files ? lst : lst->next);
	}
}

void			ft_ls_args(int ac, char **av, int i, const char *flags)
{
	t_list		*lst;
	t_list		*tmp;

	lst = NULL;
	tmp = NULL;
	while (i < ac)
	{
		if (!(tmp = ft_lstnew(av[i], ft_strlen(av[i]) + 1)))
			errors(0, 0);
		if (!lst)
			lst = tmp;
		else
			ft_lstaddend(&lst, tmp);
		i++;
	}
	lst = ft_ls_back_args_sort(lst, flags);
	ls_caller(lst, flags, ft_lstsize(lst));
	ft_lstdel(&lst, &free_char);
}
