/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 05:50:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/04 07:17:58 by agrumbac         ###   ########.fr       */
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

void			ft_ls_args(int ac, char **av, int first, const char *flags)
{
	int			i;

	i = first - 1;
	while (++i < ac)
		if (is_error_file_dir(av[i]) == 1)
			ft_ls(av[i], flags);
	i = first - 1;
	while (++i < ac)
		if (is_error_file_dir(av[i]) == 2)
			ft_ls(av[i], flags);
	while (--i >= first)
	{
		if (is_error_file_dir(av[i]) == 3)
		{
			ft_ls_print_path(av[i], 0, 0, 0);
			ft_ls(av[i], flags);
		}
	}
}
