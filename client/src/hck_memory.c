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
