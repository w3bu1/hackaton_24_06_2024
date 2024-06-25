#include "../inc/hck.h"

void	hck_free(t_mlx *d)
{
	if (d)
	{
		if (d->map)
			hck_clear_point(d->map);
		if (d->mlx)
		{
			if (d->map_img)
				mlx_destroy_image(d->mlx, d->map_img);
			if (d->win)
				mlx_destroy_window(d->mlx, d->win);
			mlx_destroy_display(d->mlx);
			free(d->mlx);
		}
		if (d->pawn_img[0] && d->pawn_img[1] && d->pawn_img[2]
			&& d->pawn_img[3])
		{
			free(d->pawn_img[0]);
			free(d->pawn_img[1]);
			free(d->pawn_img[2]);
			free(d->pawn_img[3]);
		}
	}
}

int	hck_mlx_key(int keysym, t_mlx *d)
{
	if (keysym == 0xff1b)
		return (hck_free(d), exit(0), 0);
	return (0);
}

int	hck_exit(t_mlx *d)
{
	hck_free(d);
	exit(0);
}

int	hck_mouse(int key, int x, int y, t_hck *d)
{
	if (key == 1)
		ft_select_pawn(&d->d_skt, &d->d_mlx, x, y);
	return (0);
}

int	hck_ctrl(t_hck *d)
{
	mlx_hook(d->d_mlx.win, 17, 0, &hck_exit, &d->d_mlx);
	mlx_hook(d->d_mlx.win, 2, 1L << 0, &hck_mlx_key, &d->d_mlx);
	mlx_mouse_hook(d->d_mlx.win, &hck_mouse, d);
	return (0);
}
