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

t_map		*retrieve_map_rec(t_map *m, int ln)
{
	char		*line;
	int			res;

	res = 0;
	if (ln < m->h && (res = get_next_line(0, &line)) == 1)
	{
		if (!(m->map[ln] = ft_strdup(line + 4)) ||
			!(m = retrieve_map_rec(m, ln + 1)))
		{
			m->map[ln] ? ft_strdel(&m->map[ln]) : 0;
			m ? free(&m) : 0;
			ft_strdel(&line);
			m = NULL;
		}
		ft_strrchr(m->map[ln], 'O') ? m->p1_f_x =
			ft_strrchr(m->map[ln], 'O') - m->map[ln] : 0;
		ft_strrchr(m->map[ln], 'O') ? m->p1_f_y = ln : 0;
		!(m->p2_f_x) && ft_strchr(m->map[ln], 'X') ? m->p2_f_x =
			ft_strchr(m->map[ln], 'X') - m->map[ln] : 0;
		!(m->p2_f_x) && ft_strchr(m->map[ln], 'X') ? m->p1_f_y = ln : 0;
		ft_strdel(&line);
	}
	return (ln == m->h || res == 1 ? m : NULL);
}

t_map		*init_map(char *line)
{
	t_map		*m;
	char		**ln_split;

	if (!(m = (t_map*)malloc(sizeof(t_map))) ||
		!(ln_split = ft_strsplit(line, ' ')))
	{
		m ? free(&m) : 0;
		ft_strdel(&line);
		return (NULL);
	}
	ft_strdel(&line);
	m->h = ft_atoi(ln_split[1]);
	m->w = ft_atoi(ln_split[2]);
	ft_tabdel(&ln_split);
	if (!(m->map = (char**)malloc(sizeof(char*) * (m->h + 1))))
	{
		free(&m);
		return (NULL);
	}
	m->p2_f_x = 0;
	m->map[m->h] = NULL;
	get_next_line(0, &line);
	ft_strdel(&line);
	return (m);
}
