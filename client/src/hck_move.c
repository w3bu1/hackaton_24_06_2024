#include "../inc/hck.h"

t_map	*get_exact_point(t_mlx *d, int ox, int oy)
{
	t_map	*map;

	map = d->map;
	while (map)
	{
		if (map->position.ox == ox && map->position.oy == oy)
			return (map);
		map = map->nxt;
	}
	return (NULL);
}

int	hck_get_direction(t_map *frm, t_map *dst)
{
	int	direction;

	direction = 0;
	while (direction < 8)
	{
		if (frm->nb[direction] == dst)
			return (direction);
		direction++;
	}
	return (direction);
}

void	hck_kill_pawn(t_map *bgn, int direction)
{
	if (!bgn)
		return ;
	if (bgn->nb[direction]
		&& bgn->nb[direction]->pawn.player == bgn->pawn.player)
		hck_kill_pawn(bgn->nb[direction], direction);
	bgn->pawn.player = 0;
	bgn->pawn.selected = 0;
	bgn->pawn.status = 0;
}

void	hck_perform_move(t_map *bgn, int dir1, int dir2)
{
	printf("dir1 %d - dir2 %d\n", dir1, dir2);
	if (bgn->nb[dir1] && bgn->nb[dir1]->pawn.player
		&& bgn->nb[dir1]->pawn.player != bgn->pawn.player)
		hck_kill_pawn(bgn->nb[dir1], dir1);
	else if (bgn->nb[dir2] && bgn->nb[dir2]->nb[dir2]
		&& bgn->nb[dir2]->nb[dir2]->pawn.player
		&& bgn->nb[dir2]->nb[dir2]->pawn.player != bgn->pawn.player)
		hck_kill_pawn(bgn->nb[dir2]->nb[dir2], dir2);
}

t_map	*hck_move(t_mlx *d, int from[2], int dest[2])
{
	t_map	*frm;
	t_map	*dst;

	frm = get_exact_point(d, from[0], from[1]);
	if (!frm)
		return (NULL);
	dst = get_exact_point(d, dest[0], dest[1]);
	if (!dst)
		return (NULL);
	printf("[%p][%p]\n", dst, frm);
	dst->pawn.player = frm->pawn.player;
	dst->pawn.old_position = frm->position;
	dst->pawn.selected = 0;
	dst->pawn.status = 1;
	hck_perform_move(dst, hck_get_direction(frm, dst), hck_get_direction(dst,
			frm));
	if (!ft_is_combo(dst))
		dst = NULL;
	frm->pawn.player = 0;
	frm->pawn.selected = 0;
	frm->pawn.status = 0;
	bzero(d->adr, WIDTH * HEIGHT * (d->bpp / 8));
	hck_draw_point_map(d);
	hck_draw_lc_map(d);
	hck_draw_diag_right(d);
	hck_draw_diag_left(d);
	mlx_put_image_to_window(d->mlx, d->win, d->map_img, 0, 0);
	hck_put_pawn(d);
	mlx_do_sync(d->mlx);
	return (dst);
}
