/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:48:29 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/05 14:50:54 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			sort_ascii(void *a, void *b)
{
	if (ft_strcmp(((t_pls*)a)->name, ((t_pls*)b)->name) > 0)
		return (0);
	return (1);
}

static int			sort_rev_ascii(void *a, void *b)
{
	if (ft_strcmp(((t_pls*)a)->name, ((t_pls*)b)->name) < 0)
		return (0);
	return (1);
}

static int			sort_time(void *a, void *b)
{
	if (((t_pls*)a)->date < ((t_pls*)b)->date)
		return (0);
	if (((t_pls*)a)->date == ((t_pls*)b)->date)
		return (sort_ascii(a, b));
	return (1);
}

static int			sort_rev_time(void *a, void *b)
{
	if (((t_pls*)a)->date > ((t_pls*)b)->date)
		return (0);
	if (((t_pls*)a)->date == ((t_pls*)b)->date)
		return (sort_rev_ascii(a, b));
	return (1);
}

t_list				*ft_ls_sort(t_list *lst, const char *flags)
{
	if (ft_strchr(flags, 'f'))
		return (lst);
	else if (ft_strchr(flags, 'r') && ft_strchr(flags, 't'))
		return (ft_lstsort(lst, &sort_rev_time));
	else if (ft_strchr(flags, 't'))
		return (ft_lstsort(lst, &sort_time));
	else if (ft_strchr(flags, 'r'))
		return (ft_lstsort(lst, &sort_rev_ascii));
	else
		return (ft_lstsort(lst, &sort_ascii));
}
