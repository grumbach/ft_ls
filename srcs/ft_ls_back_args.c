/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 05:50:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/04 16:09:58 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		is_error_file_dir(const char *path)
{
	DIR					*dirp;
	struct dirent		*file;

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

static int		sort_dir_ascii(void *a, void *b)
{
	if (ft_strcmp((char*)a, (char*)b) > 0)
		return (0);
	return (1);
}

static void		free_char(void *str, size_t size)
{
	(void)size;
	ft_memdel(&str);
}

void			ft_ls_args(int ac, char **av, int first, const char *flags)
{
	//DO THIS!!!!!
	// NORM
	// UNDERSTAND ERROR memmove???
	// \n missing sometimes (is stuff above but first dir)
	int			i;
	int			ret;
	t_list		*lst;
	t_list		*tmp;

	lst = NULL;
	tmp = NULL;
	ret = 1;
	i = first - 1;
	while (++i < ac)
		if (is_error_file_dir(av[i]) == 1)
			ft_ls(av[i], flags);
	while (++ret < 4)
	{
		i = first - 1;
		while (++i < ac)
			if (is_error_file_dir(av[i]) == ret)
			{
				if (!(tmp = ft_lstnew(av[i], ft_strlen(av[i]))))
					errors(0, 0);
				if (!lst)
					lst = tmp;
				else
					ft_lstaddend(&lst, tmp);
			}
		lst = ft_lstsort(lst, &sort_dir_ascii);
		tmp = lst;
		while (tmp)
		{
			if (ret == 3)
				ft_ls_print_path(tmp->content, (tmp == lst ? (t_list*)1 : 0), 0, 0);
			ft_ls(tmp->content, flags);
			tmp = tmp->next;
		}
		if (lst)
			ft_lstdel(&lst, &free_char);
	}
}
