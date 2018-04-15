#include "wolf.h"

int	check_weapon(t_window *wind)
{
  int	w;
  int	h;
  void	*tmp;
  void  *tmp2;

  if (wind->weapon== 0 || wind->weapon== 1)
    {
      if (wind->weapon== 0)
        {
	tmp =
	  mlx_xpm_file_to_image(wind->ini, "./img/hammer.xpm", &w, &h);
  tmp2 = 
    mlx_xpm_file_to_image(wind->ini, "./img/hammerBis.xpm", &w, &h);
        }
      else
      {
	tmp =
	  mlx_xpm_file_to_image(wind->ini, "./img/scepter.xpm", &w, &h);
  tmp2 =
	  mlx_xpm_file_to_image(wind->ini, "./img/scepterBis.xpm", &w, &h);
      }
      if (tmp == 0)
	{
	  my_puterror("Cannot access to weapons images\n");
	  exit(0);
	}
      wind->weaponImg =
	mlx_get_data_addr(tmp, &wind->bpp, &wind->sizeline, &wind->endian);
      wind->weaponBisImg =
	mlx_get_data_addr(tmp2, &wind->bpp, &wind->sizeline, &wind->endian);
      free(tmp);
      free(tmp2);
    }
  return (0);
}

int	change_weapon(t_window *wind)
{
  if (wind->weapon== 0)
    wind->weapon= 1;
  else if (wind->weapon== 1)
    wind->weapon= 2;
  else if (wind->weapon== 2)
    wind->weapon= 0;
  check_weapon(wind);
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

int	my_datacpy(t_window *wind, char *scr, char *dest, int i)
{
  while (i != YIMG * wind->sizeline + XIMG * (wind->bpp / 8) + 2)
    {
      if (scr[i] == 10 && scr[i + 1] == 100)
	i += 3;
      dest[i] = scr[i];
      i++;
    }
  return (0);
}

int		background(t_window *wind)
{
  static char	*save;
  int		w;
  int		h;

  if (wind->key != 1)
    {
      wind->img =
	mlx_xpm_file_to_image(wind->ini, "./img/bg.xpm", &w, &h);
      if (wind->img == 0)
	{
	  my_puterror("Cannot access to background images\n");
	  exit (0);
	}
      wind->data =
	mlx_get_data_addr(wind->img, &wind->bpp, &wind->sizeline, &wind->endian);
      save = malloc(YIMG * wind->sizeline + XIMG * (wind->bpp / 8) + 2 + 1);
      if (save == NULL)
	exit(0);
      my_datacpy(wind, wind->data, save, 0);
      wind->key = 1;
    }
  my_datacpy(wind, save, wind->data, 0);
  return (0);
}
