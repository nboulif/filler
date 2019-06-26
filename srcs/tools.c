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

void			send_result(t_filler *u)
{
	if (u->best_y == INT_MAX || u->best_x == INT_MAX)
	{
		u->best_y = 0;
		u->best_x = 0;
	}
	ft_putnbr_fd(u->best_y - u->p->o_ln, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(u->best_x - u->p->o_col, 1);
	ft_putstr_fd("\n", 1);
}

void			reinit_utils_struct(t_filler *u)
{
	u->m = NULL;
	u->p = NULL;
	u->count_all_pos = 0;
	u->count_en = 0;
	u->best_y = INT_MAX;
	u->best_x = INT_MAX;
}
