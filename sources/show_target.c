#include "wolf.h"

int	chose_map(t_img *img, int i, int w, int h)
{
  if (img->args == 1)
    {
      img->img =
	mlx_xpm_file_to_image(img->ini, "./img/startmenu.xpm", &w, &h);
      if (img->img == 0)
	{
	  my_puterror("Cannot access to file win image\n");
	  exit (0);
	}
      img->args = 0;
      mlx_put_image_to_window(img->ini, img->window, img->img, 0, 0);
    }
  if (i == KEYL || i == KEYN || i == KEYS)
    {
      if (i == KEYS)
	img->map = get_wolf_map(NULL, "maps/littlemap", 0, 0);
      if (i == KEYL)
	img->map = get_wolf_map(NULL, "maps/bigmap", 0, 0);
      if (i == KEYN)
	img->map = get_wolf_map(NULL, "maps/normalmap", 0, 0);
      img->args = 1;
      ini_first_pos(img, 0, 0, 0);
      build_img(img, 0);
    }
  return (0);
}

int	get_win_img(t_img *img)
{
  int	w;
  int	h;

  if (img->win == 0)
    {
      img->targetImg =
	mlx_xpm_file_to_image(img->ini, "./img/win.xpm", &w, &h);
      if (img->targetImg == 0)
	{
	  my_puterror("Cannot access to file image\n");
	  exit(0);
	}
    }
  return (0);
}

int	check_if_win(t_img *img, int xmap, int ymap)
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
	      && is_wall(img->map, x, y, xmap) == 1)
	    wall++;
	  x++;
	}
      x = 0;
      y++;
    }
  if (wall == 0)
    {
      get_win_img(img);
      img->win = 1;
    }
  return (wall);
}

int	create_help(t_img *img)
{
  void	*tmp;
  int	w;
  int	h;

  tmp = mlx_xpm_file_to_image(img->ini, "./img/man.xpm", &w, &h);
  if (tmp == 0)
    {
      my_puterror("Cannot access to file image\n");
      exit(0);
    }
  img->helpImg=
    mlx_get_data_addr(tmp, &img->bpp, &img->sizeline, &img->endian);
  return (0);
}

void	show_target(t_img *img, int i)
{
  void	*tmp;
  void	*tmpr;
  void	*tmpb;
  int	w;
  int	h;

  img->target*= i;
  if (img->target== 0)
    {
      tmp = mlx_xpm_file_to_image(img->ini, "./img/target.xpm", &w, &h);
      tmpb = mlx_xpm_file_to_image(img->ini, "./img/bluetarg.xpm", &w, &h);
      tmpr = mlx_xpm_file_to_image(img->ini, "./img/redtarg.xpm", &w, &h);
      if (tmp == 0 || tmpb == 0 || tmpr == 0)
	{
	  my_puterror("Cannot access to target image\n");
	  exit(0);
	}
      img->targetImg =
	mlx_get_data_addr(tmp, &img->bpp, &img->sizeline, &img->endian);
      img->rtargImg =
	mlx_get_data_addr(tmpr, &img->bpp, &img->sizeline, &img->endian);
      img->btargImg =
	mlx_get_data_addr(tmpb, &img->bpp, &img->sizeline, &img->endian);
      img->target= 1;
    }
}
