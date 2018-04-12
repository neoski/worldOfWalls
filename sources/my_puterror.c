#include "wolf.h"

int	my_puterror(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  write(2, str, i);
  return (0);
}
