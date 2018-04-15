#include "worldOfWalls.h"

int	change_wall_color(t_window *wind, float ksave)
{
  if (ksave > wind->coord->k)
    {
      wind->color.r = 10;
      wind->color.g = 10;
      wind->color.b = 30;
    }
  else if (ksave < wind->coord->k)
    {
      wind->color.r = 25;
      wind->color.g = 25;
      wind->color.b = 45;
    }
  return (0);
}

int	reset_wall_color(t_window *wind)
{
  wind->color.r = 20;
  wind->color.g = 20;
  wind->color.b = 40;
  return (0);
}
