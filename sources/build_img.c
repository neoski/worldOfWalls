#include "wolf.h"

void		draw_line(t_window *wind, int x, int i, int z)
{
  static float	ksave[3] = {0, 0, 0};
  int		size;
  int		midy;

  midy = YIMG / 2;
  size = YIMG / (2 * wind->coord->k);
  if (ksave[1] != 0 && ksave[2] != 0 && ksave[1] != ksave[0]
      && ksave[2] != ksave[0])
    change_wall_color(wind, ksave[0]);
  while (z < size && z < YIMG)
    {
      pixel_to_img(wind, x, midy + i);
      z++;
      if (z != size && z < YIMG)
	{
	  pixel_to_img(wind, x, midy - i++);
	  z++;
	}
    }
  if (ksave[1] != 0 && ksave[2] != 0 && ksave[1] == ksave[0]
      && ksave[2] == ksave[0])
    reset_wall_color(wind);
  ksave[2] = ksave[1];
  ksave[1] = ksave[0];
  ksave[0] = wind->coord->k;
}

int	x_max_map(char *map)
{
  int	i;

  i = 0;
  while (map[i] != ' ')
    i++;
  return (i);
}

int	y_max_map(char *map)
{
  int	i;
  int	y;

  i = 0;
  y = 0;
  while (map[i] != '\0')
    {
      if (map[i] == ' ')
	y++;
      i++;
    }
  return (y);
}

int	show_all_imgs(t_window *wind, int xmap)
{
  int	x;
  int	y;

  x = 1 * cos(wind->coord->a) + wind->coord->p_x0;
  y = 1 * sin(wind->coord->a) + wind->coord->p_y0;
  if (wind->weapon != 2) {
    if (!wind->weaponBis) 
      my_datacpy(wind, wind->weaponImg, wind->data, 0);
    else
      my_datacpy(wind, wind->weaponBisImg, wind->data, 0);
  }
  if (wind->target== 1 && is_wall(wind->map, x, y, xmap) == 0)
    my_datacpy(wind, wind->targetImg, wind->data, 0);
  else if (wind->target== 1)
    {
      if (x != 0 && x != x_max_map(wind->map) - 1 &&
	  y != 0 && y != y_max_map(wind->map))
	my_datacpy(wind, wind->btargImg, wind->data, 0);
      else
	my_datacpy(wind, wind->rtargImg, wind->data, 0);
    }
  if (wind->help == 1)
    my_datacpy(wind, wind->helpImg, wind->data, 0);
  mlx_put_image_to_window(wind->ini, wind->window, wind->img, 0, 0);
  return (0);
}

int	build_img(t_window *wind, float xmax)
{
  int	xmap;
  int	ymap;

  background(wind);
  reset_wall_color(wind);
  xmap = x_max_map(wind->map);
  ymap = y_max_map(wind->map);
  while (xmax < XIMG)
    {
      calc_x_y(wind, xmax);
      wind->coord->k = -1;
      calc_dist_x(wind, xmap);
      calc_dist_y(wind, xmap, ymap);
      if (wind->coord->k > 0)
	draw_line(wind, xmax, 0, 0);
      xmax++;
    }
  if (wind->win != 1)
    show_all_imgs(wind, xmap);
  get_score(wind);
  if (wind->win == 1)
    mlx_put_image_to_window(wind->ini, wind->window, wind->targetImg, 0, 0);
  return (0);
}
