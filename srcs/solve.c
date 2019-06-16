/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:02:05 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:44:30 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			try_put_piece(t_filler *u, int m_ln, int m_col, int *count_en)
{
	int		p_ln;
	int		p_col;
	int		count_sp;

	p_ln = -1;
	count_sp = 0;
	(*count_en) = 0;
	while (u->p->piece[++p_ln])
	{
		p_col = -1;
		while (u->p->piece[p_ln][++p_col])
		{
			u->m->map[m_ln + p_ln][m_col + p_col] == u->enemy_char
				? (*count_en)++ : 0;
			if (u->p->piece[p_ln][p_col] == '.' ||
			u->m->map[m_ln + p_ln][m_col + p_col] == '.')
				;
			else if (u->p->piece[p_ln][p_col] == '*' &&
				(u->m->map[m_ln + p_ln][m_col + p_col] == u->enemy_char ||
				(u->m->map[m_ln + p_ln][m_col + p_col] == u->my_char
				&& ++count_sp > 1)))
				return (0);
		}
	}
	return (count_sp);
}

float		get_dist_enemy(t_filler *u, int ln1, int col1)
{
	int		ln;
	int		col;
	float	dist;

	dist = 0.0;
	ln = 0;
	while (u->m->map[ln])
	{
		col = 0;
		while (u->m->map[ln][col])
		{
			if (u->m->map[ln][col] && u->m->map[ln][col] == u->enemy_char)
			{
				if (dist == 0.0 || dist > get_distance(col, col1, ln, ln1))
				{
					dist = get_distance(col, col1, ln, ln1);
				}
			}
			col++;
		}
		ln++;
	}
	return (dist);
}

void		update_best_values(t_filler *u, int ln, int col)
{
	u->best_y = ln;
	u->best_x = col;
}

void		get_my_best_pos(t_filler *u, int ln, int col)
{
	float	dist;
	int		count_en;

	while (u->m->map[ln] && ln + u->p->h <= u->m->h)
	{
		while (u->m->map[ln][col] && col + u->p->w <= u->m->w)
		{
			if ((try_put_piece(u, ln, col, &count_en)))
			{
				dist = get_dist_enemy(u, ln + u->p->h - 1, col + u->p->w - 1);
				get_my_best_pos(u, ln, col + 1);
				if (u->best_y == INT_MAX || dist < u->dist
					|| (dist == u->dist && count_en >= u->count_en))
				{
					update_best_values(u, ln, col);
					u->dist = dist;
					u->count_en = count_en;
				}
				return ;
			}
			col++;
		}
		ln++;
		col = 0;
	}
}
