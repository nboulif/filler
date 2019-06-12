/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 23:28:50 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:45:02 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			is_empty_col(char **piece, int ln_start, int ln_max, int col)
{
	while (ln_start < ln_max)
		if (piece[ln_start++][col] == '*')
			return (0);
	return (1);
}

t_piece		*create_piece(char **tmp_piece, t_piece *p, int ln, int col)
{
	int			i;

	if (!(p->piece = (char**)malloc((sizeof(char*) * p->h) + 1)))
		return (NULL);
	i = -1;
	while (++i < p->h)
		if (!(p->piece[i] = ft_strsub(tmp_piece[ln + i], col, p->w)))
			break ;
	if (i == p->h)
	{
		p->piece[i] = 0;
		return (p);
	}
	while (i-- > 0)
		ft_strdel(&p->piece[i]);
	free(p->piece);
	return (NULL);
}

t_piece		*parse_piece(char **tmp_piece, t_piece *p)
{
	int			ln;
	int			col;

	ln = 0;
	while (!(ft_strchr(tmp_piece[ln], '*')))
		ln++;
	p->o_ln = ln;
	p->o_y_1 = ln;
	p->o_x_1 = ft_strchr(tmp_piece[ln], '*') - tmp_piece[ln];
	p->h = 0;
	while (tmp_piece[ln + p->h] && ft_strchr(tmp_piece[ln + p->h], '*'))
		p->h++;
	col = 0;
	while (is_empty_col(tmp_piece, ln, ln + p->h, col))
		col++;
	p->o_col = col;
	p->w = 0;
	while (tmp_piece[0][col + p->w] &&
		!(is_empty_col(tmp_piece, ln, ln + p->h, col + p->w)))
		p->w++;
	return (create_piece(tmp_piece, p, ln, col));
}

void		free_no_need_lines(char *ln, char **ln_split)
{
	ft_strdel(&ln);
	ft_tabdel(&ln_split);
}

t_piece		*retrieve_piece(char *line)
{
	t_piece		*p;
	char		**tmp_piece;
	int			ln;
	int			res;
	char		**line_splited;

	if (!(p = (t_piece*)malloc(sizeof(t_piece)))
		|| !(line_splited = ft_strsplit(line, ' '))
		|| !(tmp_piece = (char**)malloc((sizeof(char*)
			* ft_atoi(line_splited[1]) + 1))))
		return (NULL);
	p->h = ft_atoi(line_splited[1]);
	p->w = ft_atoi(line_splited[2]);
	ln = -1;
	while (++ln < p->h && (res = get_next_line(0, &line)) >= 0)
		tmp_piece[ln] = line;
	tmp_piece[ln] = 0;
	if (ln < p->h)
		ft_tabdel(&tmp_piece);
	else
		p = parse_piece(tmp_piece, p);
	free_no_need_lines(line, line_splited);
	return (p);
}
