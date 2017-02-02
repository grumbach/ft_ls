/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:27:06 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 05:50:11 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_date
{
	int				month;
	int				day;
	int				hour;
	int				minute;
}					t_date;

typedef struct		s_pls
{
	char			*mode;
	int				links;
	char			*own;
	char			*group;
	long			size;
	t_date			date;
	char			*name;
}					t_pls;

# define LS_FLAGS "GMRaflrt1"

# define MONTH1 "Jan"
# define MONTH2 "Feb"
# define MONTH3 "Mar"
# define MONTH4 "Apr"
# define MONTH5 "May"
# define MONTH6 "Jun"
# define MONTH7 "Jul"
# define MONTH8 "Aug"
# define MONTH9 "Sep"
# define MONTH10 "Oct"
# define MONTH11 "Nov"
# define MONTH12 "Dec"

#endif
