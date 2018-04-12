#include "wolf.h"

int	check_codekeys(t_img *img, int keycode)
{
  if (keycode == RIGHT)
    img->kright = 0;
  if (keycode == LEFT)
    img->kleft = 0;
  if (keycode == UP)
    img->kup = 0;
  if (keycode == DOWN)
    img->kdown = 0;
  if (keycode == SPACE)
    img->space = 0;
  return (0);
}

int	key_release(int keycode, t_img *img)
{
  if (img->args == 0)
    chose_map(img, keycode, 0, 0);
  else if (keycode == KEYW || keycode == KEYT || keycode == KEYH ||
	   keycode == KEYB || keycode == KEYR)
    {
      if ((keycode == KEYB || keycode == KEYR) && img->weapon!= 2)
	key_b_r(img, keycode);
      if (keycode == KEYW)
	change_weapon(img);
      if (keycode == KEYT)
	show_target(img, -1);
      if (keycode == KEYH)
	img->help *= -1;
      build_img(img, -1);
    }
  if (keycode == LEFT || keycode == UP || keycode == RIGHT ||
      keycode == DOWN || keycode == SPACE)
    check_codekeys(img, keycode);
  if (keycode == ECHAP)
    exit(0);
  return (0);
}

int	loop_hook(t_img *img)
{
  int built;

  built = 0;
  if (img->kup)
    key_up_down(img, UP);
  if (img->kdown)
    key_up_down(img, DOWN);
  if (img->kleft)
    key_right_left(img, LEFT);
  if (img->kright)
    key_right_left(img, RIGHT);
  if (img->weaponBis) {
    ftime(&img->currentTime);
    if (img->currentTime.time > img->weaponBisTime ||
    img->currentTime.millitm > img->weaponBisMilli)
      img->weaponBis = 0;
      build_img(img, -1);
      built = 1;
  }
  if (!built && (img->kright || img->kleft || img->kup || img->kdown))
    build_img(img, -1);
  return (0);
}
