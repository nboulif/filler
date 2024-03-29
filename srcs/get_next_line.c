/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:29:39 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:55 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int			ft_clean(char **line)
{
	ft_strdel(line);
	return (0);
}

static char			*ft_join_cust(char *src, char *src2, char *dst)
{
	char				*tmp;

	tmp = dst;
	if (!(dst = ft_strjoin(src, src2)))
		return (NULL);
	free(tmp);
	return (dst);
}

int					get_next_line(const int fd, char **line)
{
	static t_utils		u;
	char				*ptr;

	if (fd < 0 || fd > OPEN_MAX || BUFF_SIZE < 1 || !line
		|| read(fd, u.buf, 0) < 0 ||
		(!(u.r[fd]) && (u.r[fd] = ft_strnew(0)) == NULL))
		return (-1);
	while (!(ft_strchr(u.r[fd], '\n'))
		&& (u.ret = read(fd, u.buf, BUFF_SIZE)) > 0)
	{
		u.buf[u.ret] = '\0';
		if (!(u.r[fd] = ft_join_cust(u.r[fd], u.buf, u.r[fd])))
			return (ft_clean(&u.r[fd]) - 1);
	}
	ptr = ft_strchr(u.r[fd], '\n');
	u.n = ptr ? 1 : 0;
	u.len = ptr ? ptr - u.r[fd] : ft_strlen(u.r[fd]);
	if ((u.len > 0 || ptr) && !(*line = ft_strsub(u.r[fd], 0, u.len)))
		return (ft_clean(&u.r[fd]) - 1);
	if (!(ptr) || !(ptr + 1) || !(*(ptr + 1)))
		ft_strdel(&u.r[fd]);
	else if (!(u.r[fd] = ft_join_cust(ptr + 1, "", u.r[fd])))
		return (ft_clean(&u.r[fd]) + ft_clean(line) - 1);
	return ((!(*line) || (u.len == 0 && (!u.n))) ? 0 : 1);
}
