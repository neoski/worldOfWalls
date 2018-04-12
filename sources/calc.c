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

int	calc_dist_y(t_img *img, int xmap, int ymap)
{
  float	tmp;
  int	x;
  int	y;

  y = 0;
  while (y < ymap + 1)
    {
      tmp = (y - img->coord->p_y0) / img->coord->vy;
      x = img->coord->p_x0 + (tmp * img->coord->vx);
      if (tmp > 0 && (tmp < img->coord->k || img->coord->k == -1)
	  && (is_wall(img->map, x, y, xmap) == 1 ||
	      is_wall(img->map, x, y - 1, xmap) == 1))
	img->coord->k = tmp;
      y++;
    }
  return (0);
}

int	calc_dist_x(t_img *img, int xmap)
{
  float	tmp;
  int	x;
  int	y;

  x = 0;
  while (x < xmap)
    {
      tmp = (x - img->coord->p_x0) /img->coord->vx;
      y = img->coord->p_y0 + (tmp * img->coord->vy);
      if (tmp > 0 && (tmp < img->coord->k || img->coord->k == -1)
          && ((is_wall(img->map, x, y, xmap) == 1) ||
	      is_wall(img->map, x - 1, y, xmap) == 1))
        img->coord->k = tmp;
      x++;
    }
  return (0);
}

int	calc_x_y(t_img *img, float xmax)
{
  float	temp;

  img->coord->p_x1 = 1;
  img->coord->p_x1 = img->coord->d;
  img->coord->p_y1 = ((XIMG / 2) - xmax) / XIMG;
  temp = img->coord->p_x1;
  img->coord->p_x1 = (temp * cos(img->coord->a))
    - (img->coord->p_y1 * sin(img->coord->a));
  img->coord->p_y1 = (temp * sin(img->coord->a))
    + (img->coord->p_y1 * cos(img->coord->a));
  img->coord->p_x1 = img->coord->p_x0 + img->coord->p_x1;
  img->coord->p_y1 = img->coord->p_y0 + img->coord->p_y1;
  img->coord->vx = img->coord->p_x1 - img->coord->p_x0;
  img->coord->vy = img->coord->p_y1 - img->coord->p_y0;
  return (0);
}
