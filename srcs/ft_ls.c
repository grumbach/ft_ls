/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:26:08 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 12:16:57 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			errors(int error, const char *letter)
{
	if (error == 1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putstr_fd(letter, 2);
		ft_putstr_fd("\nusage: ft_ls [-"LS_FLAGS"] [file ...]\n", 2);
	}
	else if (letter)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(letter, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd(strerror(errno), 2);
	exit(-1);
}

static void		free_lst(void *inf, size_t size)
{
	t_pls		*info;

	(void)size;
	info = (t_pls*)inf;
	if (info)
	{
		if (info->mode)
			free(info->mode);
		if (info->own)
			free(info->own);
		if (info->group)
			free(info->group);
		if (info->name)
			free(info->name);
		free(info);
	}
}

static void		setflags(char *flags, const char *format)
{
	int			flags_count;

	flags_count = ft_strlen(flags);
	while (*format)
	{
		if (ft_strchr(LS_FLAGS, *format) && !ft_strchr(flags, *format))
			flags[flags_count++] = *format;
		else
			errors(1, (char[2]){(*format), '\0'});
		format++;
	}
}

void			ft_ls(const char *path, const char *flags)
{
	t_list		*lst;

	ft_printf("====================ft_ls(%s, %s)\n\n", path, flags);
	lst = ft_ls_back(path, flags);
	ft_ls_front(lst, path, flags);
	if (ft_strchr(flags, 'R'))
		ft_ls_rec(lst, path, flags);
	ft_lstdel(&lst, &free_lst);
}

int				main(int ac, char **av)
{
	char		flags[ft_strlen(LS_FLAGS)];
	int			i;

	i = 1;
	ft_bzero(&flags, ft_strlen(LS_FLAGS));
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1])
			setflags(flags, av[i] + 1);
		else
			break ;
		i++;
	}
	if (i < ac)
		while (i < ac)
		{
			ft_ls(av[i], flags);
			i++;
		}
	else
		ft_ls(".", flags);
	return (0);
}
