#include "../inc/hck.h"



char   * hck_perform_act(t_skt *st,  t_mlx *d, char *msg)
{
    (void)st;
    printf("message [%s]\n", msg);
    if (strncmp(msg, "play", 4) == 0)
        d->player = atoi(msg + 4);
    if (hck_is_coord_message(msg))
    {
        char    **coords = ft_split(msg, ' ');
        printf("(%s, %s) -> (%s, %s)\n", coords[0], coords[1], coords[2], coords[3]);
        ft_free_splitted_str(coords);
    }
    return (NULL);
}
