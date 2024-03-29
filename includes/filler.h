/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:41 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:48:07 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft.h"
# include <limits.h>

# define BUFF_SIZE 100000

typedef struct		s_utils
{
	char		buf[BUFF_SIZE + 1];
	char		*r[OPEN_MAX];
	int			ret;
	int			len;
	int			n;
}					t_utils;

typedef struct		s_map
{
	char		**map;
	int			h;
	int			w;
	int			p1_f_y;
	int			p1_f_x;
	int			p2_f_y;
	int			p2_f_x;
}					t_map;

typedef struct		s_piece
{
	char		**piece;
	int			h;
	int			w;
	int			o_ln;
	int			o_col;
	int			o_y_1;
	int			o_x_1;
}					t_piece;

typedef struct		s_filler
{
	t_map		*m;
	t_piece		*p;
	int			pp;
	char		enemy_char;
	int			count_en;
	char		my_char;
	int			best_y;
	int			best_x;
	float		dist;
	int			count_all_pos;

}					t_filler;

int					parse_data(t_filler *u, char *line, int *res);
int					main(void);

int					get_next_line(const int fd, char **line);

t_map				*init_map(char *line);
t_map				*retrieve_map_rec(t_map *m, int ln);

int					is_empty_col(char **piece, int ln_start,
					int ln_max, int col);
char				**read_piece(char *line, t_piece *p);
t_piece				*create_piece(char **tmp_piece, t_piece *p, int ln,
					int col);
t_piece				*parse_piece(char **tmp_piece);
t_piece				*retrieve_piece(char *line);

int					try_put_piece(t_filler *u, int m_ln, int m_col,
					int *count_en);
float				get_dist_enemy(t_filler *u, int ln1, int col1);
void				update_best_values(t_filler *u, int ln, int col);
void				get_my_best_pos(t_filler *u, int ln, int col);

void				send_result(t_filler *u);
void				reinit_utils_struct(t_filler *u);

#endif
