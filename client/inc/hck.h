/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hck.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabarij <nrabarij@student.42antanana>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:54:56 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/24 14:55:12 by nrabarij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HCK_H
# define HCK_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <unistd.h>

# ifndef _WIN_SIZE
#  define WIDTH 1024
#  define HEIGHT 800
# endif

// Structure Point pour les coordonnées x et y
typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_pion
{
	int				selected;
	int				status;
	int				player;
	int				radius;
	t_point			position;
	t_point			old_position;
	struct s_pion	*r;
	struct s_pion	*l;
	struct s_pion	*t;
	struct s_pion	*b;
	struct s_pion	*tr;
	struct s_pion	*tl;
	struct s_pion	*bl;
	struct s_pion	*br;
}					t_pion;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				endian;
	int				size_line;
	int				bpp;
}					t_img;

/// @brief nb represent the neighbours [8]
/// [0] top corner
/// [1] top-right corner
/// [2] right corner
/// [3] bot-right corner
/// [4] bot corner
/// [5] bot-left corner
/// [6] left corner
/// [7] top-left corner
typedef struct s_map
{
	t_point			position;
	t_pion			*pion;
	// struct s_map	*r;
	// struct s_map	*l;
	// struct s_map	*t;
	// struct s_map	*b;
	// struct s_map	*tr;
	// struct s_map	*tl;
	// struct s_map	*bl;
	// struct s_map	*br;
	struct s_map	*nb[8];
	struct s_map	*nxt;
	struct s_map	*prv;
}					t_map;

typedef struct s_hck
{
	t_img			*img_data;
}					t_hck;

void				hck_error(int code);
double				ft_max(double n1, double n2);
double				ft_abs(double x1);

#endif
