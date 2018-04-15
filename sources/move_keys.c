#include "worldOfWalls.h"

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

int	key_b_r(t_window *wind, int keycode)
{
  int	x;
  int	y;

  ftime(&wind->currentTime);
  wind->weaponBis = 1;
  wind->weaponBisTime = wind->currentTime.time;
  wind->weaponBisMilli = wind->currentTime.millitm + 200;
  if (wind->weaponBisMilli > 1000) {
    wind->weaponBisTime += 1;
    wind->weaponBisMilli -= 1000;
  }

  x = 1 * cos(wind->coord->a) + wind->coord->p_x0;
  y = 1 * sin(wind->coord->a) + wind->coord->p_y0;
  if (keycode == KEYB && (x != (int)wind->coord->p_x0 ||
			  y != (int)wind->coord->p_y0))
    build_or_rm(wind->map, x, y, 1);
  else if (x != 0 && x != x_max_map(wind->map) - 1 &&
	   y != 0 && y != y_max_map(wind->map))
    build_or_rm(wind->map, x, y, 0);
  return (0);
}

int	check_if_run(t_window *wind, int keycode, float *x, float *y)
{
  if (keycode == UP && !wind->kdown && wind->space)
    {
      *x += 0.025 * cos(wind->coord->a);
      *y += 0.025 * sin(wind->coord->a);
    }
  return (0);
}

int	key_up_down(t_window *wind, int keycode)
{
  int	xmap;
  float	x;
  float	y;

  xmap = x_max_map(wind->map);
  x = wind->coord->p_x0;
  y = wind->coord->p_y0;
  if (keycode == UP)
    {
      x += 0.015 * cos(wind->coord->a);
      y += 0.015 * sin(wind->coord->a);
    }
  if (keycode == DOWN && !wind->space)
    {
      x -= 0.015 * cos(wind->coord->a);
      y -= 0.015 * sin(wind->coord->a);
    }
  check_if_run(wind, keycode, &x, &y);
  if (is_wall(wind->map, x, y, xmap) == 0)
    {
      wind->coord->p_x0 = x;
      wind->coord->p_y0 = y;
    }
  return (0);
}

int		key_right_left(t_window *wind, int keycode)
{
  static int	a = 0;

  if (keycode == LEFT)
    wind->coord->a = ++a * (PI / 48);
  if (keycode == RIGHT)
    wind->coord->a = --a * (PI / 48);
  return (0);
}
