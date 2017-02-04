/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 05:50:09 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/04 05:56:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_args(int ac, char **av, int i, const char *flags)
{
	while (i < ac)
	{
		ft_ls(av[i], flags);
		i++;
	}
}
