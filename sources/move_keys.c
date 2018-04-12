#include "wolf.h"

int	build_or_rm(char *map, int x, int y, int command)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  x = x_max_map(map) - x;
  while (map[i] != '\0')
    i++;
  while (i != 0 && j != y)
    {
      i--;
      if (map[i] == ' ')
	j++;
    }
  while (i != 0 && x !=0)
    {
      x--;
      i--;
    }
  if (command == 0)
    map[i] = '0';
  else
    map[i] = '1';
  return (0);
}

int	key_b_r(t_img *img, int keycode)
{
  int	x;
  int	y;

  ftime(&img->currentTime);
  img->weaponBis = 1;
  img->weaponBisTime = img->currentTime.time;
  img->weaponBisMilli = img->currentTime.millitm + 200;
  if (img->weaponBisMilli > 1000) {
    img->weaponBisTime += 1;
    img->weaponBisMilli -= 1000;
  }

  x = 1 * cos(img->coord->a) + img->coord->p_x0;
  y = 1 * sin(img->coord->a) + img->coord->p_y0;
  if (keycode == KEYB && (x != (int)img->coord->p_x0 ||
			  y != (int)img->coord->p_y0))
    build_or_rm(img->map, x, y, 1);
  else if (x != 0 && x != x_max_map(img->map) - 1 &&
	   y != 0 && y != y_max_map(img->map))
    build_or_rm(img->map, x, y, 0);
  return (0);
}

int	check_if_run(t_img *img, int keycode, float *x, float *y)
{
  if (keycode == UP && !img->kdown && img->space)
    {
      *x += 0.025 * cos(img->coord->a);
      *y += 0.025 * sin(img->coord->a);
    }
  return (0);
}

int	key_up_down(t_img *img, int keycode)
{
  int	xmap;
  float	x;
  float	y;

  xmap = x_max_map(img->map);
  x = img->coord->p_x0;
  y = img->coord->p_y0;
  if (keycode == UP)
    {
      x += 0.015 * cos(img->coord->a);
      y += 0.015 * sin(img->coord->a);
    }
  if (keycode == DOWN && !img->space)
    {
      x -= 0.015 * cos(img->coord->a);
      y -= 0.015 * sin(img->coord->a);
    }
  check_if_run(img, keycode, &x, &y);
  if (is_wall(img->map, x, y, xmap) == 0)
    {
      img->coord->p_x0 = x;
      img->coord->p_y0 = y;
    }
  return (0);
}

int		key_right_left(t_img *img, int keycode)
{
  static int	a = 0;

  if (keycode == LEFT)
    img->coord->a = ++a * (PI / 48);
  if (keycode == RIGHT)
    img->coord->a = --a * (PI / 48);
  return (0);
}
