/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_front_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Anselme <Anselme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 10:14:40 by Anselme           #+#    #+#             */
/*   Updated: 2017/02/15 19:58:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_ls_colors(const t_pls *info, const char *flags)
{
	if (!ft_strchr(flags, 'G'))
		return (0);
	if (info->mode[0] == 'd')
		return (4);
	if (info->mode[0] == 'l')
		return (3);
	if (info->mode[0] == 'b')
		return (5);
	if (info->mode[0] == 'c')
		return (2);
	if (info->major >= 0)
		return (6);
	if (info->mode[3] == 'x')
		return (1);
	if (info->mode[1] == '-')
		return (7);
	return (0);
}
