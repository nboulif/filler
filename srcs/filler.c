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
	int i;

	i = -1;
	while (++i < u->p->h)
		ft_strdel(&u->p->piece[i]);
	free(&u->p);
	i = -1;
	while (++i < u->m->h)
		ft_strdel(&u->m->map[i]);
	free(&u->m);
}

int		free_splited_line(char **ln_split)
{
	ft_strdel(&ln_split[0]);
	ft_strdel(&ln_split[1]);
	ft_strdel(&ln_split[2]);
	free(&ln_split);
	return (1);
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
		if (res == -1)
			return (-1);
		get_my_best_pos(&u, 0, 0, 0);
		send_result(&u);
		if (u.best_y <= 0 && u.best_x <= 0)
			break ;
	}
	// free_rest_utils(&u);
	return (0);
}
