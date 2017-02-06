/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 05:50:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/07 00:54:32 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_ls_error_file_dir(const char *path)
{
	DIR					*dirp;
	struct dirent		*file;

	if (!path)
		return (1);
	if ((dirp = opendir(path)))
	{
		(void)closedir(dirp);
		return (3);
	}
	else if (!(dirp = opendir(".")))
		return (1);
	while ((file = readdir(dirp)))
	{
		if (file->d_namlen == ft_strlen(path) && !ft_strcmp(file->d_name, path))
		{
			(void)closedir(dirp);
			return (2);
		}
	}
	(void)closedir(dirp);
	return (1);
}

static int		sort_args(void *a, void *b)
{
	int			type_a;
	int			type_b;

	type_a = ft_ls_error_file_dir((char*)a);
	type_b = ft_ls_error_file_dir((char*)b);
	if (type_a > type_b)
		return (0);
	else if (type_a < type_b)
		return (1);
	else if (ft_strcmp((char*)a, (char*)b) > 0)
		return (0);
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
		(files ? ft_ls_front(files, flags, 0, args) :
		ft_ls((char*)(lst->content), flags, args));
		lst = (files ? lst : lst->next);
	}
}

void			ft_ls_args(int ac, char **av, int i, const char *flags)
{
	t_list		*lst;
	t_list		*tmp;
	int			args;

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
	lst = ft_lstsort(lst, &sort_args);
	args = ft_lstsize(lst);
	ls_caller(lst, flags, args);
	ft_lstdel(&lst, &free_char);
}
