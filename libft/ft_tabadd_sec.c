/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd_sec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:10:31 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/27 21:10:34 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabadd_sec(char ***tab, size_t i, size_t len)
{
	if (!((*tab)[i] = ft_strnew(len)))
	{
		ft_tabdel(tab);
		return (0);
	}
	return (1);
}
