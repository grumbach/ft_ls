/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:24 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 12:19:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_front(const t_list *lst, const char *path, \
				const char *flags)
{
	t_pls				*info;
	const t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		info = (t_pls*)(tmp->content);
		//ft_printf("%-7s %-3d %-7s %-7s %-5lld %.20s %-10s\n", \
		info->mode, info->links, info->own, info->group, info->size, \
		ctime(&(info->date)) + 4, info->name);
		ft_printf("%-10s\n", info->name);
		tmp = tmp->next;
	}
}
