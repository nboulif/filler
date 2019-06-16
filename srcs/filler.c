/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_rest_utils(t_filler *u)
{
	if (u->p)
	{
		if (u->p->piece)
			ft_tabdel(&u->p->piece);
		free(u->p);
	}
	if (u->m)
	{
		if (u->m->map)
			ft_tabdel(&u->m->map);
		free(u->m);
	}
}

int			parse_data(t_filler *u, char *line)
{
	if (ft_strstr(line, "$$$ exec") &&
		ft_strstr(line, "nboulif.filler") && line[10] - '0' == 2)
	{
		u->pp = 2;
		u->my_char = 'X';
		u->enemy_char = 'O';
	}
	else if (ft_strstr(line, "Plateau"))
	{
		if (!(u->m = retrieve_map(line)))
			return (-1);
	}
	else if (ft_strstr(line, "Piece"))
	{
		if (!(u->p = retrieve_piece(line)))
			return (-1);
		return (2);
	}
	return (1);
}

int			main(void)
{
	char		*line;
	t_filler	u;
	int			res;

	init_utils_struct(&u);
	while (1)
	{
		reinit_utils_struct(&u);
		while ((res = get_next_line(0, &line)) == 1)
		{
			res = parse_data(&u, line);
			if (res == 2 || res == -1)
				break ;
		}
		if (res == -1 || !u.m)
			return (0);
		get_my_best_pos(&u, 0, 0);
		send_result(&u);
		free_rest_utils(&u);
		if (u.best_y == INT_MAX && u.best_x == INT_MAX)
			break ;
	}
	return (0);
}
