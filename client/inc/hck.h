#ifndef HCK_H
# define HCK_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <unistd.h>
# include "../mlx/mlx.h"

# ifndef _WIN_SIZE
#  define WIDTH 1024
#  define HEIGHT 680
# endif

# ifndef _HCK_CONST
#  define HCK_WHITE 0xFFFFFF
#  define HCK_ZOOM 42
#  define PORT 8080
#  define BUFFER_SIZE 1024
# endif

# ifndef _HCK_MSG
#  define HCK_ERROR "\e[31mError\e[0m"
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
	struct s_map	*nb[8];
	struct s_map	*nxt;
	struct s_map	*prv;
}					t_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*map_img;
	t_img			*pawn;
	char			*adr;
	int				bpp;
	int				len;
	int				end;
	struct s_map	*map;
}					t_mlx;

void				hck_error(int code);
double				ft_max(double n1, double n2);
double				ft_abs(double x1);
t_map				*hck_create_map(int width, int height);
void				hck_clear_point(t_map *p);
void				hck_free(t_mlx *d);
void				hck_mlx_init(t_mlx *d);
int					hck_ctrl(t_mlx *d);

#endif
