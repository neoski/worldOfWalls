SRC =	./sources/gnl/get_next_line.c \
        ./sources/gnl/get_next_line_fd.c \
	./sources/my_puterror.c \
	./sources/get_wolf_map.c \
	./sources/build_img.c \
	./sources/calc.c \
	./sources/move_keys.c \
	./sources/get_background.c \
	./sources/change_wall_color.c \
	./sources/check_map.c \
	./sources/show_target.c \
	./sources/loop_hook.c \
	./sources/get_score.c \
	./sources/main.c

CFLAGS += -Wextra -Wall -Werror
CFLAGS += -ansi -pedantic
CFLAGS += -I./include

## LINUX
#LDFLAGS = -L /usr/lib64/X11 -L /usr/lib64

## MAC
CFLAGS += -I /usr/X11/include
LDFLAGS = -L /usr/X11/lib

 
LDFLAGS += -l Xext -l X11 -l mlx -lm

NAME =	worldOfWalls

RM =	rm -f

CC = 	gcc

OBJS=	$(SRC:.c=.o)

all: 	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
