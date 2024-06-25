#include "../inc/hck.h"

t_map   *get_exact_point(t_mlx *d, int ox, int oy)
{
    t_map   *map = d->map;
    while (map)
    {
        if (map->position.ox == ox && map->position.oy == oy)
            return (map);
        map = map->nxt;
    }
    return (NULL);
}

void    hck_move(t_mlx *d, int from[2], int dest[2])
{
    t_map   *frm = get_exact_point(d, from[0], from[1]);
    if (!frm)
        return ;
    t_map   *dst = get_exact_point(d, dest[0], dest[1]);
    if (!dst)
        return ;
    dst->pawn.player = frm->pawn.player;
    dst->pawn.old_position = frm->position;
    dst->pawn.selected = 0;
    dst->pawn.status = 1;
    frm->pawn.player = 0;
    frm->pawn.selected = 0;
    frm->pawn.status = 0;
    bzero(d->adr,  WIDTH * HEIGHT *  (d->bpp / 8));
    mlx_put_image_to_window(d->mlx, d->win, d->map_img, 0, 0);
    hck_draw_point_map(d);
    hck_draw_lc_map(d);
    hck_draw_diag_right(d);
    hck_draw_diag_left(d);
    mlx_put_image_to_window(d->mlx, d->win, d->map_img, 0, 0);
    hck_put_pawn(d);
	mlx_do_sync(d->mlx);
}
