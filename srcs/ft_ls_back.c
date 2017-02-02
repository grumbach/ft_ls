/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/02 17:09:35 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_rec(const t_list *lst, const char *path, \
				const char *flags)
{
	DIR					*dirp;
	char				*newpath;
	char				*tmp;

	newpath = NULL;
	dirp = NULL;
	tmp = NULL;
	while (lst)
	{
		if (!(tmp = ft_strjoin(((path[ft_strlen(path) - 1] != '/') ? "/" : ""),\
		((t_pls*)(lst->content))->name)) || !(newpath = ft_strjoin(path, tmp)))
			errors(0, 0);
		ft_memdel((void**)&tmp);
		if ((dirp = opendir(newpath)))
		{
			if (ft_strcmp(((t_pls*)(lst->content))->name, "..") && \
				ft_strcmp(((t_pls*)(lst->content))->name, "."))
				ft_ls(newpath, flags);
			(void)closedir(dirp);
		}
		ft_memdel((void**)&newpath);
		lst = lst->next;
	}
}

static void		modeguy(struct stat stats, char *mode)
{
	if (S_IFDIR & (stats.st_mode))
		*mode++ = 'd';
	else if (S_IFREG & (stats.st_mode))
		*mode++ = '-';
	else if (S_IFIFO & (stats.st_mode))
		*mode++ = 'p';
	else if (S_IFCHR & (stats.st_mode))
		*mode++ = 'c';
	else if (S_IFBLK & (stats.st_mode))
		*mode++ = 'b';
	else if (S_IFSOCK & stats.st_mode)
		*mode++ = 's';
	else if (S_IFLNK & (stats.st_mode))
		*mode++ = 'l';
	*mode++ = (stats.st_mode & S_IRUSR ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWUSR ? 'w' : '-');
	*mode++ = (stats.st_mode & S_IXUSR ? 'x' : '-');
	*mode++ = (stats.st_mode & S_IRGRP ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWGRP ? 'w' : '-');
	*mode++ = (stats.st_mode & S_IXGRP ? 'x' : '-');
	*mode++ = (stats.st_mode & S_IROTH ? 'r' : '-');
	*mode++ = (stats.st_mode & S_IWOTH ? 'w' : '-');
	*mode++ = (stats.st_mode & S_IXOTH ? 'x' : '-');
}

static int		fill_info(t_pls *info, struct dirent *file, const char *path)
{
	struct stat			stats;
	struct passwd		*pwd;
	struct group		*grp;
	char				*tmp;
	char				*newpath;

	info->name = ft_strdup(file->d_name);
	if (!(tmp = ft_strjoin(((path[ft_strlen(path) - 1] != '/') ? "/" : ""),\
	info->name)))
		errors(0, 0);
	newpath = ft_strjoin(path, tmp);
	ft_memdel((void**)&tmp);
	lstat(newpath, &stats);
	modeguy(stats, info->mode);
	info->links = stats.st_nlink;
	pwd = getpwuid(stats.st_uid);
	info->own = ft_strdup(pwd->pw_name);
	grp = getgrgid(stats.st_gid);
	info->group = ft_strdup(grp->gr_name);
	info->size = stats.st_size;
	info->blocks = stats.st_blocks;
	info->date = stats.st_mtime;
	ft_memdel((void**)&newpath);
	return (0);
}

t_list			*ft_ls_back(const char *path, const char *flags)
{
	t_list				*lst;
	t_list				*tmp;
	t_pls				*info;
	DIR					*dirp;
	struct dirent		*file;

	lst = NULL;
	dirp = NULL;
	if (!(dirp = opendir(path)))
		errors(0, path);
	while ((file = readdir(dirp)))
		if ((file->d_name)[0] != '.' || ft_strchr(flags, 'a'))
		{
			if (!(info = ft_memalloc(sizeof(t_pls))) || \
			fill_info(info, file, path) || \
			!(tmp = ft_lstnew(info, sizeof(t_pls))))
				errors(0, 0);
			ft_memdel((void**)&info);
			if (!lst)
				lst = tmp;
			else
				ft_lstaddend(&lst, tmp);
		}
	(void)closedir(dirp);
	return (lst);
}
