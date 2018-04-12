#include "wolf.h"

int	my_get_char_size(int nb)
{
  int	size;

  size = 0;
  if (nb == 0)
    size = 1;
  while (nb != 0)
    {
      nb = nb / 10;
      size = size + 1;
    }
  return (size);
}

int	my_get_char(char *result, int nb)
{
  int	size;

  size = my_get_char_size(nb);
  result[size] = '\0';
  if (nb == 0)
    result[0] = '0';
  while (nb != 0)
    {
      size = size - 1;
      result[size] = (nb % 10) + 48;
      nb = nb / 10;
    }
  return (0);
}

int	get_score(t_img *img)
{
  int	nb;
  char	*res;

  if ((nb = check_if_win(img, x_max_map(img->map), y_max_map(img->map))) < 0)
    return (0);
  if ((res = malloc(12)) == NULL)
    exit(0);
  mlx_string_put(img->ini, img->window, 20, 20, 0x33CCFF, "WALLS REMAINING :");
  my_get_char(res, nb);
  mlx_string_put(img->ini, img->window, 130, 20, 0x33CCFF, res);
  free(res);
  return (0);
}
