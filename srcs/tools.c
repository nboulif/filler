/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 03:16:32 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:46:12 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			send_result(t_utils2 *u)
{
	if (u->best_y == 9999)
	{
		u->best_y = 0;
		u->best_x = 0;
	}
	ft_putnbr_fd(u->best_y - u->p->o_ln, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(u->best_x - u->p->o_col, 1);
	ft_putstr_fd("\n", 1);
}

float			get_distance(int x1, int x2, int y1, int y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void			reinit_utils_struct(t_utils2 *u)
{
	u->m = NULL;
	u->p = NULL;
	u->count_all_pos = 0;
	u->best_y = 9999;
	u->best_x = 9999;
}

void			init_utils_struct(t_utils2 *u)
{
	u->pp = 1;
	u->my_char = 'O';
	u->enemy_char = 'X';
	reinit_utils_struct(u);
}
