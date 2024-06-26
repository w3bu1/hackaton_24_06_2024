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
		map->pawn.old_position.x = map->position.ox;
		map->pawn.old_position.y = map->position.oy;
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
	int	i;

	i = 0;
	while (i < 8)
	{
		if (pt->nb[i] && !pt->nb[i]->pawn.player)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_enemy(t_map *bgn, t_map *pt)
{
	if (!pt || !pt->pawn.player)
		return (0);
	if (pt->pawn.player != bgn->pawn.player)
		return (1);
	return (0);
}

int	ft_is_combo(t_map *pt)
{
	int	i;
	int	ngt;

	if (!ft_can_move(pt))
		return (0);
	i = 0;
	while (i < 8)
	{
		ngt = i < 4 ? i + 4 : i - 4;
		if (pt->nb[i] && ft_is_enemy(pt, pt->nb[i]) && pt->nb[ngt]
			&& !pt->nb[ngt]->pawn.player)
			return (1);
		else if (pt->nb[i] && pt->nb[i]->nb[i] && ft_is_enemy(pt,
				pt->nb[i]->nb[i]) && !pt->nb[i]->pawn.player)
			return (1);
		i++;
	}
	return (0);
}

t_map	*hck_get_selected(t_map *map)
{
	t_map	*selected;

	selected = map;
	while (selected)
	{
		if (selected->pawn.selected)
			return (selected);
		selected = selected->nxt;
	}
	return (NULL);
}

int	hck_is_near(t_map *pt1, t_map *pt2)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (pt1->nb[i] && pt1->nb[i] == pt2)
			return (1);
		i++;
	}
	return (0);
}

void	ft_select_pawn(t_skt *st, t_mlx *d, int x, int y)
{
	t_map	*map;
	t_map	*selected;
	char	*message;

	map = d->map;
	selected = hck_get_selected(d->map);
	while (map)
	{
		if ((map->position.x + (WIDTH / 2) - 18 <= x && map->position.x + (WIDTH
					/ 2) + 18 >= x) && (map->position.y + (HEIGHT / 2) - 18 <= y
				&& map->position.y + (HEIGHT / 2) + 18 >= y))
		{
			if (map->pawn.player == 1 && d->player == 1 && ft_can_move(map))
			{
				map->pawn.selected = 1;
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[2],
					map->position.x + (WIDTH / 2) - 18, map->position.y
					+ (HEIGHT / 2) - 18);
			}
			else if (map->pawn.player == 2 && d->player == 2
				&& ft_can_move(map))
			{
				map->pawn.selected = 1;
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[3],
					map->position.x + (WIDTH / 2) - 18, map->position.y
					+ (HEIGHT / 2) - 18);
			}
			else if (map->pawn.player == 0 && selected && hck_is_near(selected,
					map))
			{
				message = ft_joinstr(itoa(selected->position.ox), " ");
				message = ft_joinstr(message, itoa(selected->position.oy));
				message = ft_joinstr(message, " ");
				message = ft_joinstr(message, itoa(map->position.ox));
				message = ft_joinstr(message, " ");
				message = ft_joinstr(message, itoa(map->position.oy));
				selected = hck_move(d, (int[2]){selected->position.ox,
						selected->position.oy}, (int[2]){map->position.ox,
						map->position.oy});
				if (selected)
					message = ft_joinstr(message, " combo\n");
				else
					message = ft_joinstr(message, "\n");
				if (message)
					send(st->socket, message, strlen(message), 0);
				free(message);
			}
		}
		else if (map->pawn.selected == 1)
		{
			map->pawn.selected = 0;
			if (map->pawn.player == 1 && d->player == 1)
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[0],
					map->position.x + (WIDTH / 2) - 18, map->position.y
					+ (HEIGHT / 2) - 18);
			else if (map->pawn.player == 2 && d->player == 2)
				mlx_put_image_to_window(d->mlx, d->win, d->pawn_img[1],
					map->position.x + (WIDTH / 2) - 18, map->position.y
					+ (HEIGHT / 2) - 18);
		}
		if (hck_is_end_game(d->map))
		{
			hck_free(d);
			exit(0);
		}
		map = map->nxt;
	}
}
