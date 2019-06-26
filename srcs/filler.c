/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/06/25 22:43:44 by nboulif          ###   ########.fr       */
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

int			parse_data(t_filler *u, char *line, int *res)
{
	if (ft_strstr(line, "$$$ exec") &&
		ft_strstr(line, "nboulif.filler") && line[10] - '0' == 2)
	{
		ft_strdel(&line);
		u->pp = 2;
		u->my_char = 'X';
		u->enemy_char = 'O';
	}
	else if (ft_strstr(line, "Plateau"))
	{
		(*res) = -1;
		if (!(u->m = init_map(line)))
			ft_strdel(&line);
		else if (retrieve_map_rec(u->m, 0))
			(*res) = 1;
	}
	else if (ft_strstr(line, "Piece"))
	{
		u->p = retrieve_piece(line);
		if (((*res) = u->p ? 2 : -1) == -1)
			free_rest_utils(u);
	}
	else
		ft_strdel(&line);
	return (*res);
}

int			main(void)
{
	char		*line;
	t_filler	u;
	int			ret;

	u.pp = 1;
	u.my_char = 'O';
	u.enemy_char = 'X';
	while (1)
	{
		reinit_utils_struct(&u);
		while ((ret = get_next_line(0, &line)) == 1 &&
			parse_data(&u, line, &ret) > 0)
			if (ret == 2)
				break ;
		if (ret <= 0)
			break ;
		get_my_best_pos(&u, 0, 0);
		send_result(&u);
		free_rest_utils(&u);
		if (u.best_y == INT_MAX && u.best_x == INT_MAX)
			break ;
	}
	return (0);
}
