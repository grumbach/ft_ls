/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 21:45:01 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/15 21:56:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			sort_ascii(void *a, void *b)
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

static int			sort_rev_ascii(void *a, void *b)
{
	int			type_a;
	int			type_b;

	type_a = ft_ls_error_file_dir((char*)a);
	type_b = ft_ls_error_file_dir((char*)b);
	if (type_a > type_b)
		return (0);
	else if (type_a < type_b)
		return (1);
	else if (ft_strcmp((char*)a, (char*)b) < 0)
		return (0);
	return (1);
}

t_list				*ft_ls_back_args_sort(t_list *lst, const char *flags)
{
	if (ft_strchr(flags, 'f'))
		return (lst);
	else if (ft_strchr(flags, 'r'))
		return (ft_ls_listsort(lst, &sort_rev_ascii));
	else
		return (ft_ls_listsort(lst, &sort_ascii));
}
