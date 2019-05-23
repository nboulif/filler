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

typedef struct		s_utils2
{
	t_map		*m;
	t_piece		*p;
	int			pp;
	char		enemy_char;
	char		my_char;
	int			best_y;
	int			best_x;
	float		dist;
	int			count_all_pos;

}					t_utils2;

int					parse_data(t_utils2 *u, char *line);
int					main(void);

int					get_next_line(const int fd, char **line);

t_map				*init_map(char *line);
t_map				*retrieve_map(char *line);

int					is_empty_col(char **piece, int ln_start,
					int ln_max, int col);
char				**read_piece(char *line, t_piece *p);
t_piece				*create_piece(char **tmp_piece, t_piece *p, int ln,
					int col);
t_piece				*parse_piece(char **tmp_piece, t_piece *p);
t_piece				*retrieve_piece(char *line);

int					try_put_piece(t_utils2 *u, int m_ln, int m_col);
float				get_dist_nearest_enemy(t_utils2 *u, int ln1, int col1);
void				get_my_best_pos(t_utils2 *u, int ln, int col, int count);

void				send_result(t_utils2 *u);
float				get_distance(int x1, int x2, int y1, int y2);
void				reinit_utils_struct(t_utils2 *u);
t_utils2			*init_utils_struct(void);

#endif
