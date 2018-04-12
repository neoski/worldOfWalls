#ifndef WOLF_H_
# define WOLF_H_

# include <sys/timeb.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/X.h>
# include "get_next_line.h"
# include "mlx.h"

# define XIMG 800
# define YIMG 600
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define SPACE 32
# define KEYW 119
# define KEYB 98
# define KEYT 116
# define KEYH 104
# define KEYR 114
# define KEYN 110
# define KEYL 108
# define KEYS 115
# define ECHAP 65307
# define PI 3.14159265358979323846

typedef struct	s_coord
{
  float		p_x0;
  float		p_y0;
  float		p_x1;
  float		p_y1;
  float		a;
  float		vx;
  float		vy;
  float		k;
  float		d;
}		t_coord;

typedef	struct	s_color
{
  int		r;
  int		g;
  int		b;
}		t_color;

typedef struct	s_img
{
  char	      	*map;
  char	      	*data;
  char	      	*helpImg;
  char	      	*weaponImg;
  char          *weaponBisImg;
  char	      	*targetImg;
  char	      	*rtargImg;
  char	      	*btargImg;
  void	      	*img;
  void	      	*ini;
  void	      	*window;
  int		args;
  int	        help;
  int	        bpp;
  int           sizeline;
  int	        endian;
  int	        key;
  int	        target;
  int	        weapon;
  int           weaponBis;
  unsigned int  weaponBisTime;
  unsigned int  weaponBisMilli;
  struct timeb  currentTime;
  int	        win;
  int	        kup;
  int	        kdown;
  int	        kright;
  int	        kleft;
  int	        space;
  t_coord	*coord;
  t_color	color;
}		t_img;

char	*get_wolf_map(char *map, char *file, int i, int y);
int	build_img(t_img *img, float xmax);
int	calc_x_y(t_img *img, float xmax);
int	calc_dist_x(t_img *img, int xmap);
int	calc_dist_y(t_img *img, int xmap, int ymap);
int	is_wall(char *map, int x, int y, int xmap);
int	my_puterror(char *str);
int	pixel_to_img(t_img *img, int x, int y);
int	key_up_down(t_img *img, int keycode);
int	x_max_map(char *map);
int	y_max_map(char *map);
int	get_background(t_img *img);
int	change_wall_color(t_img *img, float ksave);
int	reset_wall_color(t_img *img);
int	background(t_img *img);
int	key_right_left(t_img *img, int keycode);
int	check_weapon(t_img *img);
int	check_map(char *map);
int	ini_first_pos(t_img *img, int i, int x, int y);
int	change_weapon(t_img *img);
int	key_b_r(t_img *img, int keycode);
int	check_if_win(t_img *img, int xmap, int ymap);
int	create_help(t_img *img);
int	chose_map(t_img *img, int i, int h, int w);
int	loop_hook(t_img *img);
int	key_release(int keycode, t_img *img);
int	my_datacpy(t_img *img, char *scr, char *dest, int i);
int	get_score(t_img *img);
void    show_target(t_img *img, int i);

#endif /* !WOLF_H_ */
