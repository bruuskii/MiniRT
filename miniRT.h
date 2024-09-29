#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR_MESSAGE "Error\n"

typedef struct s_win
{
    int     height;
    int     width;
    void    *ptr;
    void    *win;
    void    *img;
}               t_win;

typedef struct s_vctr
{
    float   x;
    float   y;
    float   z;
}               t_vctr;

t_win   *ft_window(int height, int width);
void    ft_free_win(t_win *win);
int     ft_escape_key(int key, void *param);
int     ft_close(t_win *param);
void    ft_display(t_win *w);

#endif