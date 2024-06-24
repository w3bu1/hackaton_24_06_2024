#include "../inc/hck.h"

/// @todo verify if d was allocated.
/// @todo if d was allocated, uncomment the last free.
void	hck_free(t_mlx *d)
{
	if (d)
	{
		if (d->map)
			hck_clear_point(d->map);
			// (&(d->map));
		if (d->mlx)
		{
			if (d->map_img)
				mlx_destroy_image(d->mlx, d->map_img);
			if (d->win)
				mlx_destroy_window(d->mlx, d->win);
			mlx_destroy_display(d->mlx);
			free(d->mlx);
		}
		// free(d);
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

int	hck_mouse(int key, int x, int y, t_mlx *d)
{
	if (key == 1)
		ft_select_pawn(d, x, y);
	return (0);
}

int	hck_ctrl(t_mlx *d)
{
	mlx_hook(d->win, 17, 0, &hck_exit, d);
	mlx_hook(d->win, 2, 1L << 0, &hck_mlx_key, d);
	mlx_mouse_hook(d->win, &hck_mouse, d);
	return (0);
}
