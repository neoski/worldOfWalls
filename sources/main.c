#include "worldOfWalls.h"

int	expose_hook(t_window *wind)
{
  if (wind->args != 0)
    build_img(wind, -1);
  else if (wind->args == 0)
    mlx_put_image_to_window(wind->ini, wind->window, wind->img, 0, 0);
  return (0);
}

int	key_press(int keycode, t_window *wind)
{
  if (wind->args != 0)
    {
      if (keycode == UP)
	wind->kup = 1;
      if (keycode == DOWN)
	wind->kdown = 1;
      if (keycode == LEFT)
	wind->kleft = 1;
      if (keycode == RIGHT)
	wind->kright = 1;
      if (keycode == SPACE)
	wind->space = 1;
    }
  return (0);
}

int		pixel_to_img(t_window *wind, int x, int y)
{
  unsigned char	*tmp;

  if (x > XIMG || y < 0 || y > YIMG)
    {
      my_puterror("You're trying to draw a pixel outside the image.\n");
      exit(0);
    }
  tmp = (unsigned char*)wind->data;
  if (wind->endian == 0)
    {
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8)] = wind->color.b;
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8) + 1] = wind->color.g;
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8) + 2] = wind->color.r;
    }
  else
    {
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8) + 2] = wind->color.r;
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8) + 1] = wind->color.g;
      tmp[(y * wind->sizeline) + x * (wind->bpp / 8)] = wind->color.b;
    }
  return (0);
}

int	ini_struct(t_window *wind)
{
  if ((wind->coord = malloc(sizeof(t_coord))) == NULL)
    return (-1);
  wind->weapon= 0;
  wind->weaponBis = 0;
  wind->target= 0;
  wind->key = 0;
  wind->help = 1;
  wind->win = 0;
  wind->coord->a = 0;
  wind->coord->d = 0.5;
  wind->args = 1;
  wind->kup = 0;
  wind->kdown = 0;
  wind->kright = 0;
  wind->kleft = 0;
  wind->space = 0;
  if ((wind->ini = mlx_init()) == 0)
    {
      my_puterror("Error : Cannot mlx_init\n");
      return (-1);
    }
  if ((wind->window = mlx_new_window(wind->ini, XIMG, YIMG, "worldOfWalls")) == 0)
    return (-1);
  if ((wind->img = mlx_new_image(wind->ini, XIMG, YIMG)) == 0)
    return (-1);
  return (0);
}

int		main(int ac, char **av)
{
  t_window		*wind;

  if ((wind = malloc(sizeof(t_window))) == NULL)
    return (0);
  if (ini_struct(wind) == -1)
    return (0);
  create_help(wind);
  check_weapon(wind);
  if (ac != 1)
    wind->map = get_wolf_map(NULL, av[1], 0, 0);
  else
    chose_map(wind, 0, 0, 0);
  if (wind->args != 0)
    {
      if (check_map(wind->map) == - 1)
	return (-1);
      ini_first_pos(wind, 0, 0, 0);
      build_img(wind, 0);
    }
  mlx_hook(wind->window, KeyPress, KeyRelease, key_press, wind);
  mlx_key_hook(wind->window, key_release, wind);
  mlx_loop_hook(wind->ini, loop_hook, wind);
  mlx_expose_hook(wind->window, expose_hook, wind);
  mlx_loop(wind->ini);
  return (0);
}
