#include "../inc/hck.h"

// void	hck_print_map(t_map *tmp);

void	hck_clear_point(t_map *p)
{
	if (!p)
		return ;
	hck_clear_point(p->nxt);
	free(p);
	p = NULL;
}

t_map	*hck_create_point(int x_pos, int y_pos, int width, int height)
{
	t_map	*map;

	map = NULL;
	map = (t_map *)malloc(sizeof(t_map));
	if (map)
	{
		map->nb[0] = NULL;
		map->nb[1] = NULL;
		map->nb[2] = NULL;
		map->nb[3] = NULL;
		map->nb[4] = NULL;
		map->nb[5] = NULL;
		map->nb[6] = NULL;
		map->nb[7] = NULL;
		map->position.ox = x_pos;
		map->position.oy = y_pos;
		map->position.x = (x_pos - (width / 2)) * HCK_ZOOM;
		map->position.y = (y_pos - (height / 2)) * HCK_ZOOM;
		map->nxt = NULL;
		map->prv = NULL;
	}
	return (map);
}

void	hck_link_diag_map(t_map **bgn)
{
	t_map	*tmp1;

	if (!bgn || !(*bgn))
		return ;
	tmp1 = (*bgn);
	while (tmp1)
	{
		if ((tmp1->position.ox % 2 == 0 && tmp1->position.oy % 2 == 0)
			|| (tmp1->position.ox % 2 != 0 && tmp1->position.oy % 2 != 0))
		{
			if (tmp1->nb[0])
			{
				if (tmp1->nb[0]->nb[6])
				{
					tmp1->nb[7] = tmp1->nb[0]->nb[6];
					tmp1->nb[7]->nb[3] = tmp1;
				}
				if (tmp1->nb[0]->nb[2])
				{
					tmp1->nb[1] = tmp1->nb[0]->nb[2];
					tmp1->nb[1]->nb[5] = tmp1;
				}
			}
			if (tmp1->nb[4])
			{
				if (tmp1->nb[4]->nb[6])
				{
					tmp1->nb[5] = tmp1->nb[4]->nb[6];
					tmp1->nb[5]->nb[1] = tmp1;
				}
				if (tmp1->nb[4]->nb[2])
				{
					tmp1->nb[3] = tmp1->nb[4]->nb[2];
					tmp1->nb[3]->nb[7] = tmp1;
				}
			}
		}
		tmp1 = tmp1->nxt;
	}
}

void	hck_link_square_map(t_map **bgn)
{
	t_map	*tmp1;
	t_map	*tmp2;

	if (!bgn || !(*bgn))
		return ;
	tmp1 = (*bgn);
	while (tmp1)
	{
		if (tmp1->nxt)
		{
			tmp2 = tmp1->nxt;
			if (tmp2->position.ox == tmp1->position.ox + 1
				&& tmp2->position.oy == tmp1->position.oy
				&& tmp1->nb[2] == NULL)
			{
				tmp1->nb[2] = tmp2;
				tmp2->nb[6] = tmp1;
			}
			while (tmp2 && tmp2->position.ox != tmp1->position.ox)
				tmp2 = tmp2->nxt;
			if (tmp2)
			{
				tmp1->nb[4] = tmp2;
				tmp2->nb[0] = tmp1;
			}
		}
		tmp1 = tmp1->nxt;
	}
}

void	hck_point_add_back(t_map **bgn, t_map *new)
{
	if (!new)
		return ;
	if (!(*bgn))
	{
		(*bgn) = new;
		(*bgn)->prv = (*bgn);
		(*bgn)->nxt = NULL;
		return ;
	}
	(*bgn)->prv->nxt = new;
	(*bgn)->prv->nxt->prv = (*bgn)->prv;
	(*bgn)->prv->nxt->nxt = NULL;
	(*bgn)->prv = (*bgn)->prv->nxt;
}

t_map	*hck_create_map(int width, int height)
{
	t_map	*new;
	t_map	*nxt;
	int		i;
	int		j;

	new = NULL;
	nxt = NULL;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			new = hck_create_point(j, i, width, height);
			if (!new)
				hck_clear_point(nxt);
			hck_point_add_back(&nxt, new);
			j++;
		}
		i++;
	}
	if (nxt)
	{
		hck_link_square_map(&nxt);
		hck_link_diag_map(&nxt);
	}
	return (nxt);
}
