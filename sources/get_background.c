#include "wolf.h"

int	check_weapon(t_img *img)
{
  int	w;
  int	h;
  void	*tmp;
  void  *tmp2;

  if (img->weapon== 0 || img->weapon== 1)
    {
      if (img->weapon== 0)
        {
	tmp =
	  mlx_xpm_file_to_image(img->ini, "./img/hammer.xpm", &w, &h);
  tmp2 = 
    mlx_xpm_file_to_image(img->ini, "./img/hammerBis.xpm", &w, &h);
        }
      else
      {
	tmp =
	  mlx_xpm_file_to_image(img->ini, "./img/scepter.xpm", &w, &h);
  tmp2 =
	  mlx_xpm_file_to_image(img->ini, "./img/scepterBis.xpm", &w, &h);
      }
      if (tmp == 0)
	{
	  my_puterror("Cannot access to weapons images\n");
	  exit(0);
	}
      img->weaponImg =
	mlx_get_data_addr(tmp, &img->bpp, &img->sizeline, &img->endian);
      img->weaponBisImg =
	mlx_get_data_addr(tmp2, &img->bpp, &img->sizeline, &img->endian);
      free(tmp);
      free(tmp2);
    }
  return (0);
}

int	change_weapon(t_img *img)
{
  if (img->weapon== 0)
    img->weapon= 1;
  else if (img->weapon== 1)
    img->weapon= 2;
  else if (img->weapon== 2)
    img->weapon= 0;
  check_weapon(img);
  return (0);
}

int	strlcpy(char *src, char *dest, int i)
{
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (0);
}

int	my_datacpy(t_img *img, char *scr, char *dest, int i)
{
  while (i != YIMG * img->sizeline + XIMG * (img->bpp / 8) + 2)
    {
      if (scr[i] == 10 && scr[i + 1] == 100)
	i += 3;
      dest[i] = scr[i];
      i++;
    }
  return (0);
}

int		background(t_img *img)
{
  static char	*save;
  int		w;
  int		h;

  if (img->key != 1)
    {
      img->img =
	mlx_xpm_file_to_image(img->ini, "./img/bg.xpm", &w, &h);
      if (img->img == 0)
	{
	  my_puterror("Cannot access to background images\n");
	  exit (0);
	}
      img->data =
	mlx_get_data_addr(img->img, &img->bpp, &img->sizeline, &img->endian);
      save = malloc(YIMG * img->sizeline + XIMG * (img->bpp / 8) + 2 + 1);
      if (save == NULL)
	exit(0);
      my_datacpy(img, img->data, save, 0);
      img->key = 1;
    }
  my_datacpy(img, save, img->data, 0);
  return (0);
}
