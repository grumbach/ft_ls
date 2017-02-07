/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:24 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/07 02:08:35 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			padding_tool(const t_list *lst, uint *pd)
{
	while (lst)
	{
		pd[MODE] = ft_strlen(((t_pls*)(lst->content))->mode) > pd[MODE] \
		? ft_strlen(((t_pls*)(lst->content))->mode) : pd[MODE];
		pd[LNKS] = (uint)ft_intlen(((t_pls*)(lst->content))->links) > pd[LNKS] \
		? (uint)ft_intlen(((t_pls*)(lst->content))->links) : pd[LNKS];
		pd[OWN] = ft_strlen(((t_pls*)(lst->content))->own) > pd[OWN] \
		? ft_strlen(((t_pls*)(lst->content))->own) : pd[OWN];
		pd[GROUP] = ft_strlen(((t_pls*)(lst->content))->group) > pd[GROUP] \
		? ft_strlen(((t_pls*)(lst->content))->group) : pd[GROUP];
		pd[SIZE] = (uint)ft_intlen(((t_pls*)(lst->content))->size) > pd[SIZE] \
		? (uint)ft_intlen(((t_pls*)(lst->content))->size) : pd[SIZE];
		lst = lst->next;
	}
	pd[DATE] = 12;
}

static long long	total_block(const t_list *lst)
{
	long long		total;

	total = 0;
	while (lst)
	{
		total += ((t_pls*)(lst->content))->blocks;
		lst = lst->next;
	}
	return (total);
}

static char			*date_time(long date_n)
{
	char			*date;
	time_t			now;

	time(&now);
	date = ft_strdup(ctime(&date_n) + 4);
	if (ft_abs(now - date_n) > 15552000)
	{
		date[7] = ' ';
		ft_memmove(date + 8, date + 16, 4);
	}
	date[12] = 0;
	return (date);
}

static void			print_path(const char *path, const t_list *lst, \
					uint *padd, const char *flags)
{
	static int		i = -1;

	i++;
	if (!flags && padd[ARGS] > 1 && ft_ls_error_file_dir(path) == 3)
	{
		if (i)
			ft_printf("\n%s:\n", path);
		else
			ft_printf("%s:\n", path);
	}
	else if (flags)
	{
		if (ft_strchr(flags, 'l'))
		{
			if (((t_pls*)(lst->content))->not_a_dir == 0)
				ft_printf("total %lld\n", total_block(lst));
			padding_tool(lst, padd);
		}
	}
}

void				ft_ls_front(const t_list *lst, const char *flags, \
					const char *path, int args)
{
	t_pls				*info;
	char				*date;
	unsigned int		padd[10];

	info = (t_pls*)(lst->content);
	ft_bzero(padd, sizeof(padd));
	padd[ARGS] = (uint)args;
	print_path(path, lst, padd, 0);
	print_path(0, lst, padd, flags);
	while (lst)
	{
		info = (t_pls*)(lst->content);
		if (ft_strchr(flags, 'l'))
		{
			date = date_time(info->date);
			ft_printf("%-*s %*d %-*s %-*s %*lld %-*s %s\n", padd[MODE] + 1, \
			info->mode, padd[LNKS], info->links, padd[OWN] + 1, info->own, \
			padd[GROUP], info->group, padd[SIZE] + 1, info->size, padd[DATE], \
			date, info->name);
			ft_memdel((void**)&date);
		}
		else
			ft_printf("%s\n", info->name);
		lst = lst->next;
	}
}
