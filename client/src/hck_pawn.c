#include "../inc/hck.h"

void	init_pawn(t_mlx *d)
{
	t_map	*map;

	map = d->map;
	while (map)
	{
		map->pawn.selected = 0;
		map->pawn.status = 1;
		map->pawn.position.x = map->position.x;
		map->pawn.position.y = map->position.y;
		map->pawn.old_position.x = map->position.x;
		map->pawn.old_position.y = map->position.y;
		if (map->position.oy < (5 / 2) || (map->position.oy == (5 / 2)
				&& ((map->position.ox % 2 == 0 && map->position.ox < (9 / 2))
					|| (map->position.ox % 2 == 1 && map->position.ox > (9
							/ 2)))))
			map->pawn.player = 2;
		else if (map->position.oy > (5 / 2) || (map->position.oy == (5 / 2)
				&& ((map->position.ox % 2 == 1 && map->position.ox < (9 / 2))
					|| (map->position.ox % 2 == 0 && map->position.ox > (9
							/ 2)))))
			map->pawn.player = 1;
		else
			map->pawn.player = 0;
		map = map->nxt;
	}
}

int	ft_can_move(t_map *pt)
{
	int	i = 0;
	while (i < 8)
	{
		if (pt->nb[i] && !pt->nb[i]->pawn.player)
			return (1);
		i++;
	}
	return (0);
}

t_map	*hck_get_selected(t_map *map)
{
	while (map)
	{
		printf("(%d, %d) -> [%d]\n", map->position.ox, map->position.oy, map->pawn.selected);
		if (map->pawn.selected)
			return (map);
		map = map->nxt;
	}
	printf("tsy nisy select\n");
	return (NULL);
}

int	hck_is_near(t_map *pt1, t_map *pt2)
{
	int	i = 0;
	while (i < 8)
	{
		if (pt1->nb[i] && pt1->nb[i] == pt2)
			return (1);
		i++;
	}
	return (0);
}

void	ft_select_pawn(t_mlx *d, int x, int y)
{
	t_map	*map;
	t_map	*selected;

	map = d->map;
	while (map)
	{
		if ((map->position.x + (WIDTH / 2) - 18 <= x && map->position.x + (WIDTH
					/ 2) + 18 >= x) && (map->position.y + (HEIGHT / 2) - 18 <= y
				&& map->position.y + (HEIGHT / 2) + 18 >= y))
		{
			if (map->pawn.player && ft_can_move(map))
				map->pawn.selected = 1;
			if (map->pawn.player == 1 && d->player == 1)
			{
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[2], map->position.x + (WIDTH / 2) - 18, map->position.y + (HEIGHT / 2) - 18);
			}
			else if (map->pawn.player == 2 && d->player == 2)
			{
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[3], map->position.x + (WIDTH / 2) - 18, map->position.y + (HEIGHT / 2) - 18);
			}
			else if (map->pawn.player == 0)
			{
				printf("ato isika izao\n");
				selected = hck_get_selected(d->map);
				if (selected)
				{
					printf("(%d, %d)\n", selected->position.ox, selected->position.oy);
					// printf("Afaka makeo\n");
				}
			}
		} else
		{
			if (map->pawn.selected == 1 && map->pawn.player)
			{
				if (map->pawn.player == 0)
				{

				}
				else
				{
					map->pawn.selected = 0;
					if (map->pawn.player == 1 && d->player == 1)
						mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[0], map->position.x + (WIDTH / 2) - 18, map->position.y + (HEIGHT / 2) - 18);
					else if (map->pawn.player == 2 && d->player == 2)
						mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[1], map->position.x + (WIDTH / 2) - 18, map->position.y + (HEIGHT / 2) - 18);
				}
			}
		}
		// printf("hors loop\n");
		map = map->nxt;
	}
	hck_get_selected(d->map);
}
