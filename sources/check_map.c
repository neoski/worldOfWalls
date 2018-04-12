#include "wolf.h"

int	ini_first_pos(t_img *img, int i, int x, int y)
{
  int	ymax;

  ymax = y_max_map(img->map) - 1;
  while (img->map[i] != '\0')
    {
      if (img->map[i] == '0')
	{
	  img->coord->p_x0 = x + 0.5;
	  img->coord->p_y0 = ymax - y + 1 + 0.5;
	  return (0);
	}
      if (img->map[i] == ' ')
	{
	  i++;
	  y++;
	  x = 0;
	}
      i++;
      x++;
    }
  return (0);
}

int	map_error(int i)
{
  if (i == 1)
    my_puterror("The maze isn't correctly closed : Missing walls.\n");
  else
    my_puterror("There is no space to spawn. Please put a '0' on the map.\n");
  return (-1);
}

int	check_map(char *map)
{
  int	i;
  int	spawn;

  i = 0;
  spawn = 0;
  while (map[i] != '\0')
    {
      if (i == 0)
	while (map[i] != ' ' && map[i] != '\0')
	  if (map[i++] == '0')
	    return (map_error(1));
      if (map[i] == ' ' && (map[i - 1] != '1' || map[i + 1] != '1'))
	return (map_error(1));
      if (map[i] == '0')
	spawn = 1;
      i++;
    }
  if (spawn == 0)
    return (map_error(2));
  while (map[i] != ' ' && i != 0)
    if (map[i--] == '0')
      return (map_error(1));
  return (0);
}
