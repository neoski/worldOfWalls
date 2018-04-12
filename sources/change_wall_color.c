#include "wolf.h"

int	change_wall_color(t_img *img, float ksave)
{
  if (ksave > img->coord->k)
    {
      img->color.r = 10;
      img->color.g = 10;
      img->color.b = 30;
    }
  else if (ksave < img->coord->k)
    {
      img->color.r = 25;
      img->color.g = 25;
      img->color.b = 45;
    }
  return (0);
}

int	reset_wall_color(t_img *img)
{
  img->color.r = 20;
  img->color.g = 20;
  img->color.b = 40;
  return (0);
}
