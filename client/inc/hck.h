#ifndef HCK_H
# define HCK_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <unistd.h>

# ifndef _WIN_SIZE
#  define WIDTH 680
#  define HEIGHT 680
# endif

# ifndef _HCK_CONST
#  define HCK_WHITE 0xFFFFFF
#  define HCK_ZOOM 72
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
	int				ox;
	int				oy;
	int				y;
}					t_point;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				endian;
	int				size_line;
	int				bpp;
}					t_img;
typedef struct s_pawn
{
	int				selected;
	int				status;
	int				player;
	t_point			position;
	t_point			old_position;
	char			*img_path;
	char			*slt_pth;
	void			*img;
}					t_pawn;


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
	t_pawn			pawn;
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
void				init_pawn(t_mlx *d, int w, int h);

#endif
