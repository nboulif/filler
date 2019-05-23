/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:28:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:42:22 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map		*init_map(char *line)
{
	t_map		*m;
	int			res;

	if (!(m = (t_map*)malloc((sizeof(t_map)))))
		return (NULL);
	m->h = ft_atoi(ft_strsplit(line, ' ')[1]);
	m->w = ft_atoi(ft_strsplit(line, ' ')[2]);
	if (!(m->map = (char**)malloc((sizeof(char*) * m->h) + 1)))
		return (NULL);
	m->p2_f_x = 0;
	res = get_next_line(0, &line);
	ft_strdel(&line);
	return (m);
}

int			free_map(char **map, int ln, char *line)
{
	int		i;

	i = 0;
	while (i < ln)
		ft_strdel(&map[i++]);
	ft_strdel(&line);
	return (1);
}

t_map		*retrieve_map(char *line)
{
	t_map		*m;
	int			ln;
	int			res;

	if (!(m = init_map(line)))
		return (NULL);
	ln = -1;
	while (++ln < m->h && (res = get_next_line(0, &line)) == 1)
	{
		if (!(m->map[ln] = ft_strdup(line + 4)) && free_map(m->map, ln, line))
			return (NULL);
		if (ft_strrchr(m->map[ln], 'O'))
		{
			m->p1_f_x = ft_strrchr(m->map[ln], 'O') - m->map[ln];
			m->p1_f_y = ln;
		}
		if (!(m->p2_f_x) && ft_strchr(m->map[ln], 'X'))
		{
			m->p2_f_x = ft_strchr(m->map[ln], 'X') - m->map[ln];
			m->p2_f_y = ln;
		}
		ft_strdel(&line);
	}
	m->map[ln] = 0;
	return (m);
}
