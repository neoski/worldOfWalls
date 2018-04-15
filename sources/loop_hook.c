#include "wolf.h"

int	check_codekeys(t_window *wind, int keycode)
{
  if (keycode == RIGHT)
    wind->kright = 0;
  if (keycode == LEFT)
    wind->kleft = 0;
  if (keycode == UP)
    wind->kup = 0;
  if (keycode == DOWN)
    wind->kdown = 0;
  if (keycode == SPACE)
    wind->space = 0;
  return (0);
}

int	key_release(int keycode, t_window *wind)
{
  if (wind->args == 0)
    chose_map(wind, keycode, 0, 0);
  else if (keycode == KEYW || keycode == KEYT || keycode == KEYH ||
	   keycode == KEYB || keycode == KEYR)
    {
      if ((keycode == KEYB || keycode == KEYR) && wind->weapon!= 2)
	key_b_r(wind, keycode);
      if (keycode == KEYW)
	change_weapon(wind);
      if (keycode == KEYT)
	show_target(wind, -1);
      if (keycode == KEYH)
	wind->help *= -1;
      build_img(wind, -1);
    }
  if (keycode == LEFT || keycode == UP || keycode == RIGHT ||
      keycode == DOWN || keycode == SPACE)
    check_codekeys(wind, keycode);
  if (keycode == ECHAP)
    exit(0);
  return (0);
}

int	loop_hook(t_window *wind)
{
  int built;

  built = 0;
  if (wind->kup)
    key_up_down(wind, UP);
  if (wind->kdown)
    key_up_down(wind, DOWN);
  if (wind->kleft)
    key_right_left(wind, LEFT);
  if (wind->kright)
    key_right_left(wind, RIGHT);
  if (wind->weaponBis) {
    ftime(&wind->currentTime);
    if (wind->currentTime.time > wind->weaponBisTime ||
    wind->currentTime.millitm > wind->weaponBisMilli)
      wind->weaponBis = 0;
      build_img(wind, -1);
      built = 1;
  }
  if (!built && (wind->kright || wind->kleft || wind->kup || wind->kdown))
    build_img(wind, -1);
  return (0);
}
