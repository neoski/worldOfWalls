#include "wolf.h"

int	is_wall(char *map, int x, int y, int xmap)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  x = xmap - x;
  while (map[i] != '\0')
    i++;
  while (i != 0 && j != y)
    {
      i--;
      if (map[i] == ' ')
        j++;
    }
  while (i != 0&& x !=0)
    {
      x--;
      i--;
    }
  if (map[i] == '1' && x == 0)
    return (1);
  return (0);
}

int	calc_dist_y(t_window *wind, int xmap, int ymap)
{
  float	tmp;
  int	x;
  int	y;

  y = 0;
  while (y < ymap + 1)
    {
      tmp = (y - wind->coord->p_y0) / wind->coord->vy;
      x = wind->coord->p_x0 + (tmp * wind->coord->vx);
      if (tmp > 0 && (tmp < wind->coord->k || wind->coord->k == -1)
	  && (is_wall(wind->map, x, y, xmap) == 1 ||
	      is_wall(wind->map, x, y - 1, xmap) == 1))
	wind->coord->k = tmp;
      y++;
    }
  return (0);
}

int	calc_dist_x(t_window *wind, int xmap)
{
  float	tmp;
  int	x;
  int	y;

  x = 0;
  while (x < xmap)
    {
      tmp = (x - wind->coord->p_x0) /wind->coord->vx;
      y = wind->coord->p_y0 + (tmp * wind->coord->vy);
      if (tmp > 0 && (tmp < wind->coord->k || wind->coord->k == -1)
          && ((is_wall(wind->map, x, y, xmap) == 1) ||
	      is_wall(wind->map, x - 1, y, xmap) == 1))
        wind->coord->k = tmp;
      x++;
    }
  return (0);
}

int	calc_x_y(t_window *wind, float xmax)
{
  float	temp;

  wind->coord->p_x1 = 1;
  wind->coord->p_x1 = wind->coord->d;
  wind->coord->p_y1 = ((XIMG / 2) - xmax) / XIMG;
  temp = wind->coord->p_x1;
  wind->coord->p_x1 = (temp * cos(wind->coord->a))
    - (wind->coord->p_y1 * sin(wind->coord->a));
  wind->coord->p_y1 = (temp * sin(wind->coord->a))
    + (wind->coord->p_y1 * cos(wind->coord->a));
  wind->coord->p_x1 = wind->coord->p_x0 + wind->coord->p_x1;
  wind->coord->p_y1 = wind->coord->p_y0 + wind->coord->p_y1;
  wind->coord->vx = wind->coord->p_x1 - wind->coord->p_x0;
  wind->coord->vy = wind->coord->p_y1 - wind->coord->p_y0;
  return (0);
}
