/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:24 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 15:46:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_front(const t_list *lst, const char *flags)
{
	t_pls				*info;
	const t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		info = (t_pls*)(tmp->content);
		if (ft_strchr(flags, 'l'))
		{
			ft_printf("%10s %*d %-*s %-*s %5lld %.20s %-10s\n", \
			info->mode, 2, info->links, 7, info->own, 7, info->group, \
			info->size, ctime(&(info->date)) + 4, info->name);
		}
		else
			ft_printf("%-10s\n", info->name);
		tmp = tmp->next;
	}
}
