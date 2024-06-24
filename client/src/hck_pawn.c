#include "../inc/hck.h"


void init_pawn(t_map *map)
{
  t_map *tmp;

  tmp = map;
  while (tmp)
  {
    tmp->pion = (t_pawn *)malloc(sizeof(t_pawn));
    if (!tmp->pion)
      hck_error(1);
    tmp->pion->selected = 0;
    tmp->pion->status = 1;
    tmp->pion->position.x = tmp->position.x;
    tmp->pion->position.y = tmp->position.y;
    tmp->pion->old_position.x = tmp->position.x;
    tmp->pion->old_position.y = tmp->position.y;
    if (tmp->position.y < (5 / 2) || (tmp->position.y == (5 / 2) + 1 && ((tmp->position.x % 2 == 0 && tmp->position.x < (9 / 2)) || (tmp->position.x % 2 == 1 && tmp->position.x > (9 / 2)))))
      tmp->pion->player = 1;
    else if (tmp->position.y > (5 / 2) + 1 || (tmp->position.y == (5 / 2) + 1 && ((tmp->position.x % 2 == 1 && tmp->position.x < (9 / 2)) || (tmp->position.x % 2 == 0 && tmp->position.x > (9 / 2)))))
      tmp->pion->player = 2;
    else
      tmp->pion->player = 0;
    tmp = tmp->nxt;
  }
}