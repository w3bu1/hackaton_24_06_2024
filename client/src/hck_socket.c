#include "../inc/hck.h"

char	*hck_perform_act(t_skt *st, t_mlx *d, char *msg)
{
	char	**coords;

	if (strncmp(msg, "exit", 4) == 0)
	{
		if (st->socket)
			close(st->socket);
		exit(0);
	}
	if (strncmp(msg, "play", 4) == 0)
		d->player = atoi(msg + 4);
	if (hck_is_coord_message(msg))
	{
		coords = ft_split(msg, ' ');
		hck_move(d, (int[2]){atoi(coords[0]), atoi(coords[1])},
			(int[2]){atoi(coords[2]), atoi(coords[3])});
		ft_free_splitted_str(coords);
		mlx_do_sync(d->mlx);
	}
	return (NULL);
}
