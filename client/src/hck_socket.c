#include "../inc/hck.h"


char   * hck_perform_act(t_skt *st,  t_mlx *d, char *msg)
{
    (void)st;
    if (strncmp(msg, "play", 4) == 0)
        d->player = atoi(msg + 4);
    return (NULL);
}
