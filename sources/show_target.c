#include "wolf.h"

int	chose_map(t_window *wind, int i, int w, int h)
{
  if (wind->args == 1)
    {
      wind->img =
	mlx_xpm_file_to_image(wind->ini, "./img/startmenu.xpm", &w, &h);
      if (wind->img == 0)
	{
	  my_puterror("Cannot access to file win image\n");
	  exit (0);
	}
      wind->args = 0;
      mlx_put_image_to_window(wind->ini, wind->window, wind->img, 0, 0);
    }
  if (i == KEYL || i == KEYN || i == KEYS)
    {
      if (i == KEYS)
	wind->map = get_wolf_map(NULL, "maps/littlemap", 0, 0);
      if (i == KEYL)
	wind->map = get_wolf_map(NULL, "maps/bigmap", 0, 0);
      if (i == KEYN)
	wind->map = get_wolf_map(NULL, "maps/normalmap", 0, 0);
      wind->args = 1;
      ini_first_pos(wind, 0, 0, 0);
      build_img(wind, 0);
    }
  return (0);
}

int	get_win_img(t_window *wind)
{
  int	w;
  int	h;

  if (wind->win == 0)
    {
      wind->targetImg =
	mlx_xpm_file_to_image(wind->ini, "./img/win.xpm", &w, &h);
      if (wind->targetImg == 0)
	{
	  my_puterror("Cannot access to file image\n");
	  exit(0);
	}
    }
  return (0);
}

int	check_if_win(t_window *wind, int xmap, int ymap)
{
  int	x;
  int	y;
  int	wall;

  y = 0;
  x = 0;
  wall = 0;
  while (y < ymap + 1)
    {
      while (x < xmap)
	{
	  if (x != 0 && x != xmap - 1 && y != 0 && y != ymap
	      && is_wall(wind->map, x, y, xmap) == 1)
	    wall++;
	  x++;
	}
      x = 0;
      y++;
    }
  if (wall == 0)
    {
      get_win_img(wind);
      wind->win = 1;
    }
  return (wall);
}

int	create_help(t_window *wind)
{
  void	*tmp;
  int	w;
  int	h;

  tmp = mlx_xpm_file_to_image(wind->ini, "./img/man.xpm", &w, &h);
  if (tmp == 0)
    {
      my_puterror("Cannot access to file image\n");
      exit(0);
    }
  wind->helpImg=
    mlx_get_data_addr(tmp, &wind->bpp, &wind->sizeline, &wind->endian);
  return (0);
}

void	show_target(t_window *wind, int i)
{
  void	*tmp;
  void	*tmpr;
  void	*tmpb;
  int	w;
  int	h;

  wind->target*= i;
  if (wind->target== 0)
    {
      tmp = mlx_xpm_file_to_image(wind->ini, "./img/target.xpm", &w, &h);
      tmpb = mlx_xpm_file_to_image(wind->ini, "./img/bluetarg.xpm", &w, &h);
      tmpr = mlx_xpm_file_to_image(wind->ini, "./img/redtarg.xpm", &w, &h);
      if (tmp == 0 || tmpb == 0 || tmpr == 0)
	{
	  my_puterror("Cannot access to target image\n");
	  exit(0);
	}
      wind->targetImg =
	mlx_get_data_addr(tmp, &wind->bpp, &wind->sizeline, &wind->endian);
      wind->rtargImg =
	mlx_get_data_addr(tmpr, &wind->bpp, &wind->sizeline, &wind->endian);
      wind->btargImg =
	mlx_get_data_addr(tmpb, &wind->bpp, &wind->sizeline, &wind->endian);
      wind->target= 1;
    }
}
