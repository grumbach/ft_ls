/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 02:53:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/04 15:15:46 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls_rec(const t_list *lst, const char *path, \
				const char *flags)
{
	DIR					*dirp;
	char				*newpath;
	char				*tmp;

	dirp = NULL;
	while (lst)
	{
		if (!(tmp = ft_strjoin("/", ((t_pls*)(lst->content))->name)) || \
			!(newpath = ft_strjoin(path, tmp)))
			errors(0, 0);
		ft_memdel((void**)&tmp);
		if ((dirp = opendir(newpath)))
		{
			if (ft_strcmp(((t_pls*)(lst->content))->name, "..") && \
				ft_strcmp(((t_pls*)(lst->content))->name, "."))
			{
				ft_ls_print_path(newpath, 0, 0, 0);
				ft_ls(newpath, flags);
			}
			(void)closedir(dirp);
		}
		ft_memdel((void**)&newpath);
		lst = lst->next;
	}
}

static void		modeguy(struct stat stats, char *mode)
{
	if (S_IFREG >> 9 == (stats.st_mode >> 9))
		*mode++ = '-';
	else if (S_IFCHR >> 9 == (stats.st_mode >> 9))
		*mode++ = 'c';
	else if (S_IFIFO >> 9 == (stats.st_mode >> 9))
		*mode++ = 'p';
	else if (S_IFDIR >> 9 == (stats.st_mode >> 9))
		*mode++ = 'd';
	else if (S_IFLNK >> 9 == (stats.st_mode >> 9))
		*mode++ = 'l';
	else if (S_IFBLK >> 9 == (stats.st_mode >> 9))
		*mode++ = 'b';
	else if (S_IFSOCK >> 9 == (stats.st_mode >> 9))
		*mode++ = 's';
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

static t_list	*not_a_dir(const char *name, const char *path)
{
	t_list				*lst;
	t_pls				*info;
	DIR					*dirp;
	struct dirent		*file;

	lst = NULL;
	if (!(dirp = opendir(path)))
		return ((t_list*)errors(0, path));
	while ((file = readdir(dirp)))
	{
		if (file->d_namlen == ft_strlen(name) && !ft_strcmp(file->d_name, name))
		{
			if (!(info = ft_memalloc(sizeof(t_pls))) || \
				fill_info(info, file, path) || \
				!(lst = ft_lstnew(info, sizeof(t_pls))))
				errors(0, 0);
			ft_memdel((void**)&info);
			((t_pls*)(lst->content))->not_a_dir = 1;
		}
	}
	if (!lst)
		return ((t_list*)errors(0, name));
	(void)closedir(dirp);
	return (lst);
}

t_list			*ft_ls_back(const char *path, const char *flags)
{
	t_list				*lst;
	t_list				*tmp;
	t_pls				*info;
	DIR					*dirp;
	struct dirent		*file;

	lst = NULL;
	if (!(dirp = opendir(path)))
		return (not_a_dir(path, "."));
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
