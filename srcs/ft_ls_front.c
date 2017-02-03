/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:24 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/04 00:14:36 by agrumbac         ###   ########.fr       */
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
	pd[DATE_P] = 12;
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

void				ft_ls_front(const t_list *lst, const char *flags)
{
	t_pls				*info;
	unsigned int		padd[10];

	ft_bzero(padd, sizeof(padd));
	if (ft_strchr(flags, 'l'))
	{
		if (((t_pls*)(lst->content))->not_a_dir == 0)
			ft_printf("total %lld\n", total_block(lst));
		padding_tool(lst, padd);
	}
	while (lst)
	{
		info = (t_pls*)(lst->content);
		if (ft_strchr(flags, 'l'))
		{
			ft_printf("%-*s %*d %-*s %-*s %*lld %-*.*s %s\n", \
			padd[MODE] + 1, info->mode, padd[LNKS], info->links, \
			padd[OWN] + 1, info->own, padd[GROUP], info->group, \
			padd[SIZE] + 1, info->size, padd[DATE], padd[DATE_P], \
			ctime(&(info->date)) + 4, info->name);
		}
		else
			ft_printf("%s\n", info->name);
		lst = lst->next;
	}
}

void				ft_ls_print_path(const char *path)
{
	ft_printf("\n%s:\n", path);
}
