#include "wolf.h"

void		draw_line(t_img *img, int x, int i, int z)
{
  static float	ksave[3] = {0, 0, 0};
  int		size;
  int		midy;

  midy = YIMG / 2;
  size = YIMG / (2 * img->coord->k);
  if (ksave[1] != 0 && ksave[2] != 0 && ksave[1] != ksave[0]
      && ksave[2] != ksave[0])
    change_wall_color(img, ksave[0]);
  while (z < size && z < YIMG)
    {
      pixel_to_img(img, x, midy + i);
      z++;
      if (z != size && z < YIMG)
	{
	  pixel_to_img(img, x, midy - i++);
	  z++;
	}
    }
  if (ksave[1] != 0 && ksave[2] != 0 && ksave[1] == ksave[0]
      && ksave[2] == ksave[0])
    reset_wall_color(img);
  ksave[2] = ksave[1];
  ksave[1] = ksave[0];
  ksave[0] = img->coord->k;
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

int	show_all_imgs(t_img *img, int xmap)
{
  int	x;
  int	y;

  x = 1 * cos(img->coord->a) + img->coord->p_x0;
  y = 1 * sin(img->coord->a) + img->coord->p_y0;
  if (img->weapon != 2) {
    if (!img->weaponBis) 
      my_datacpy(img, img->weaponImg, img->data, 0);
    else
      my_datacpy(img, img->weaponBisImg, img->data, 0);
  }
  if (img->target== 1 && is_wall(img->map, x, y, xmap) == 0)
    my_datacpy(img, img->targetImg, img->data, 0);
  else if (img->target== 1)
    {
      if (x != 0 && x != x_max_map(img->map) - 1 &&
	  y != 0 && y != y_max_map(img->map))
	my_datacpy(img, img->btargImg, img->data, 0);
      else
	my_datacpy(img, img->rtargImg, img->data, 0);
    }
  if (img->help == 1)
    my_datacpy(img, img->helpImg, img->data, 0);
  mlx_put_image_to_window(img->ini, img->window, img->img, 0, 0);
  return (0);
}

int	build_img(t_img *img, float xmax)
{
  int	xmap;
  int	ymap;

  background(img);
  reset_wall_color(img);
  xmap = x_max_map(img->map);
  ymap = y_max_map(img->map);
  while (xmax < XIMG)
    {
      calc_x_y(img, xmax);
      img->coord->k = -1;
      calc_dist_x(img, xmap);
      calc_dist_y(img, xmap, ymap);
      if (img->coord->k > 0)
	draw_line(img, xmax, 0, 0);
      xmax++;
    }
  if (img->win != 1)
    show_all_imgs(img, xmap);
  get_score(img);
  if (img->win == 1)
    mlx_put_image_to_window(img->ini, img->window, img->targetImg, 0, 0);
  return (0);
}
