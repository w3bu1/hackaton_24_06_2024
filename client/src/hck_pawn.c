#include "../inc/hck.h"

void	init_pawn(t_mlx *d)
{
  t_map *map = d->map;
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
    // if (map->pawn.player == 1)
    //   map->pawn.img = p1;
    // else if (map->pawn.player == 2)
    //   map->pawn.img = p2;
		map = map->nxt;
	}
}
