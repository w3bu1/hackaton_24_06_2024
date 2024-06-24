/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:41:54 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/24 14:26:19 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hck.h"

static void	ft_put_pixel(t_hck *map, int x, int y, int color)
{
	char	*dst;
	int		index;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return ;
	index = (y * map->img_data->size_line + x * (map->img_data->bpp / 8));
	dst = map->img_data->addr + index;
	*(unsigned int *)dst = color;
}

static void	ft_draw_line(t_hck *data, t_point frm, t_point dst)
{
	double	dcord[2];
	double	from[2];
	double	dest[2];
	double	max;
	int		c[2];

	from[0] = frm.x;
	from[1] = frm.y;
	dest[0] = dst.x;
	dest[1] = dst.y;
	dcord[0] = dest[0] - from[0];
	dcord[1] = dest[1] - from[1];
	max = ft_max(ft_abs(dcord[0]), ft_abs(dcord[1]));
	dcord[0] /= max;
	dcord[1] /= max;
	c[0] = 0;
	while ((int)(from[0] - dest[0]) || (int)(from[1] - dest[1]))
	{
		ft_fdf_put_pixel(data, (int)round(from[0]), (int)round(from[1]),
			0xFFFFFF);
		from[0] += dcord[0];
		from[1] += dcord[1];
		c[0]++;
	}
}
void	ft_create_map(void)
{
}
