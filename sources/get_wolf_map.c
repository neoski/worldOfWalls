#include "worldOfWalls.h"

int	wolf_mapline_len(char *str)
{
  int	i;
  int	y;

  y = 0;
  i = 0;
  while (str[i++] != '\0')
    if (str[i - 1] == '0' || str[i - 1] == '1')
      y++;
  return (y);
}

char		*wolf_map_realloc(char *old, int i, int size)
{
  static int	sizecheck = 0;
  int		z;
  char		*new;

  if (sizecheck == 0)
    sizecheck = size;
  else if (sizecheck != size)
    {
      if (old != NULL)
	free (old);
      my_puterror("Bad coordinates, number of x per lines not similar.\n");
      return (NULL);
    }
  z = 0;
  if ((new = malloc(size + i + 2)) == NULL)
    return (NULL);
  if (old != NULL)
    {
      while (old[z++] != '\0')
	new[z - 1] = old[z - 1];
      new[z - 1] = '\0';
      free(old);
    }
  return (new);
}

char	*get_wolf_map(char *map, char *file, int i, int y)
{
  char	*res;
  int	fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    {
      my_puterror("Cannot access to map file.\n");
      exit(0);
    }
  while ((res = get_next_line(fd)) != NULL)
    {
      if ((map = wolf_map_realloc(map, y, wolf_mapline_len(res))) == NULL)
	exit(0);
      while (res[i++] != '\0')
	if (res[i - 1] == '0' || res[i - 1] == '1')
	  map[y++] = res[i - 1];
      map[y++] = ' ';
      map[y] = '\0';
      i = 0;
      free(res);
    }
  if (map == NULL)
    exit (0);
  map[y - 1] = '\0';
  close(fd);
  return (map);
}
