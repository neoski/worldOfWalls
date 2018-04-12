# WorldOfWalls
A 3D game coded in C mainly pixel by pixel using an external lib (*the Minilibx*).

<img alt="WorldOfWalls Demo" src="https://s17.postimg.cc/cqgtprdlb/world_Of_Walls_Demo.gif" height="300px"/>

This project was one of the biggest solo-projects of my studies, basically the aim was to create 3D walls using the minilibx. I went further and added other features including weapons, a target with different states, the possibility to build/destroy walls and to run, some menus, an aim and a score.

### Requirements :

gcc

make

xorg and x11 for Linux systems / XQuartz for Mac (which includes x11)

The minilibx installed (You can find it in `minilibx.tgz` which you can decompress with `tar -xf`, `make` and move their `libmlx.a` in `/usr/X11/lib` or `/usr/local/lib` depending of your OS)

If you're a Linux system, uncomment Linux's LDFLAGS rule on the root Makefile


### Usage :

1. `make`

2. `./worldOfWalls [mapfile]`

**Author** : Sebastien S.

**Github repository :** https://github.com/neoski/worldOfWalls

Made during my studies in january 2015.
