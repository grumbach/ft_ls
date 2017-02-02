/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:26:08 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 05:55:08 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				errors(int error, const char *letter)
{
	if (error == 0)
	{
		ft_putstr_fd("ls: illegal option -- ", 2);
		ft_putstr_fd(letter, 2);
		ft_putstr_fd("\nusage: ls [-"LS_FLAGS"] [file ...]\n", 2);
	}
	else
		ft_putstr_fd("error\n", 2);
	exit(-1);
}

static void		free_info(t_pls info)
{
	if (info.mode)
		free(info.mode);
	if (info.own)
		free(info.mode);
	if (info.group)
		free(info.mode);
	if (info.name)
		free(info.mode);
}

static void		setflags(char *flags, const char *format)
{
	int			flags_count;

	flags_count = 0;
	ft_printf("flags : {%s}\n", format);
	while (*format)
	{
		if (ft_strchr(LS_FLAGS, *format) && !ft_strchr(flags, *format))
			flags[flags_count++] = *format;
		else
			errors(0, (char[2]){(*format), '\0'});
		format++;
	}
}

static void		ft_ls(const char *path, const char *flags)
{
	t_pls		info;

	ft_bzero(&info, sizeof(t_pls));
	ft_printf("path = {%s}, flags = {%s}\n", path, flags);
	// ft_ls_back(&info);
	// ft_ls_front(info);
	free_info(info);
}

int				main(int ac, char **av)
{
	char		flags[ft_strlen(LS_FLAGS)];
	int			i;

	i = 1;
	ft_bzero(&flags, ft_strlen(LS_FLAGS));
	while (i < ac)
	{
		if (i == 1 && av[1][0] == '-' && av[1][1])
			setflags(flags, av[1] + 1);
		else
			ft_ls(av[i], flags);
		i++;
	}
	if (i == 2 && flags[0])
		i--;
	if (i == 1)
		ft_ls(".", flags);
	return (0);
}
