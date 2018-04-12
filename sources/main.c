#include "wolf.h"

int	expose_hook(t_img *img)
{
  if (img->args != 0)
    build_img(img, -1);
  else if (img->args == 0)
    mlx_put_image_to_window(img->ini, img->window, img->img, 0, 0);
  return (0);
}

int	key_press(int keycode, t_img *img)
{
  if (img->args != 0)
    {
      if (keycode == UP)
	img->kup = 1;
      if (keycode == DOWN)
	img->kdown = 1;
      if (keycode == LEFT)
	img->kleft = 1;
      if (keycode == RIGHT)
	img->kright = 1;
      if (keycode == SPACE)
	img->space = 1;
    }
  return (0);
}

int		pixel_to_img(t_img *img, int x, int y)
{
  unsigned char	*tmp;

  if (x > XIMG || y < 0 || y > YIMG)
    {
      my_puterror("You're trying to draw a pixel outside the image.\n");
      exit(0);
    }
  tmp = (unsigned char*)img->data;
  if (img->endian == 0)
    {
      tmp[(y * img->sizeline) + x * (img->bpp / 8)] = img->color.b;
      tmp[(y * img->sizeline) + x * (img->bpp / 8) + 1] = img->color.g;
      tmp[(y * img->sizeline) + x * (img->bpp / 8) + 2] = img->color.r;
    }
  else
    {
      tmp[(y * img->sizeline) + x * (img->bpp / 8) + 2] = img->color.r;
      tmp[(y * img->sizeline) + x * (img->bpp / 8) + 1] = img->color.g;
      tmp[(y * img->sizeline) + x * (img->bpp / 8)] = img->color.b;
    }
  return (0);
}

int	ini_struct(t_img *img)
{
  if ((img->coord = malloc(sizeof(t_coord))) == NULL)
    return (-1);
  img->weapon= 0;
  img->weaponBis = 0;
  img->target= 0;
  img->key = 0;
  img->help = 1;
  img->win = 0;
  img->coord->a = 0;
  img->coord->d = 0.5;
  img->args = 1;
  img->kup = 0;
  img->kdown = 0;
  img->kright = 0;
  img->kleft = 0;
  img->space = 0;
  if ((img->ini = mlx_init()) == 0)
    {
      my_puterror("Error : Cannot mlx_init\n");
      return (-1);
    }
  if ((img->window = mlx_new_window(img->ini, XIMG, YIMG, "worldOfWalls")) == 0)
    return (-1);
  if ((img->img = mlx_new_image(img->ini, XIMG, YIMG)) == 0)
    return (-1);
  return (0);
}

int		main(int ac, char **av)
{
  t_img		*img;

  if ((img = malloc(sizeof(t_img))) == NULL)
    return (0);
  if (ini_struct(img) == -1)
    return (0);
  create_help(img);
  check_weapon(img);
  if (ac != 1)
    img->map = get_wolf_map(NULL, av[1], 0, 0);
  else
    chose_map(img, 0, 0, 0);
  if (img->args != 0)
    {
      if (check_map(img->map) == - 1)
	return (-1);
      ini_first_pos(img, 0, 0, 0);
      build_img(img, 0);
    }
  mlx_hook(img->window, KeyPress, KeyRelease, key_press, img);
  mlx_key_hook(img->window, key_release, img);
  mlx_loop_hook(img->ini, loop_hook, img);
  mlx_expose_hook(img->window, expose_hook, img);
  mlx_loop(img->ini);
  return (0);
}
