#include "../inc/hck.h"

void	hck_put_pixel(t_mlx *d, int x, int y, int col)
{
	char	*dst;

	if ((x + (WIDTH / 2) >= 0) && (x + (WIDTH / 2) < WIDTH) && (y + (HEIGHT / 2) >= 0) && (y + (HEIGHT / 2) < HEIGHT))
	{
		dst = d->adr + ((y + (HEIGHT / 2)) * d->len) + ((x + (WIDTH / 2)) * (d->bpp / 8));
		*(unsigned int *)dst = col;
	}
}

void	hck_draw_point_map(t_mlx *d)
{
	t_map	*map;

	map = d->map;
	while (map)
	{
		hck_put_pixel(d, map->position.x, map->position.y, HCK_WHITE);
		map = map->nxt;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->map_img, 0, 0);
}

void	hck_draw_lc_map(t_mlx *d)
{
	int		x;
	int		y;
	t_map	*map;
	map = d->map;
	x = 0;
	y = 0;
	while (map)
	{
		if (map->nb[2])
		{
			x = map->position.x;
			while (++x < map->nb[2]->position.x)
				hck_put_pixel(d, x, map->position.y, HCK_WHITE);
		}
		if (map->nb[4])
		{
			y = map->position.y;
			while (++y < map->nb[4]->position.y)
				hck_put_pixel(d, map->position.x, y, HCK_WHITE);
		}
		map = map->nxt;
	}
}

void	hck_mlx_init(t_mlx *d)
{
	d->map = hck_create_map(9, 5);
	if (!d->map)
		return (hck_free(d));
	d->mlx = mlx_init();
	if (!d->mlx)
		return (perror(HCK_ERROR), hck_free(d));
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "fanorona");
	if (!d->win)
		return (perror(HCK_ERROR), hck_free(d));
	d->map_img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->map_img)
		return (perror(HCK_ERROR), hck_free(d));
	d->adr = mlx_get_data_addr(d->map_img, &d->bpp, &d->len, &d->end);
	if (!d->adr)
		return (perror(HCK_ERROR), hck_free(d));
	hck_draw_point_map(d);
	hck_draw_lc_map(d);
}
