/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:23:21 by kbassim           #+#    #+#             */
/*   Updated: 2024/09/30 14:23:26 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/get_next_line/get_next_line.h"

#define HEIGHT 800
#define WIDTH 800
#define ERROR_MESSAGE "Error\n"

typedef struct s_win
{
    int     height;
    int     width;
    void    *ptr;
    void    *win;
    void    *img;
}               t_win;

typedef struct s_color
{
    int r;
    int g;
    int b;
}               t_color;

typedef struct s_vctr
{
    float   x;
    float   y;
    float   z;
}               t_vctr;

typedef struct  s_light
{
    t_color     *color;
    t_vctr      dir;
    double      brightness;
}               t_light;

typedef struct s_Alight
{
    float   ratio;
    t_color *color;
}               t_Alight;

typedef struct s_sp
{
    float   r;
    float   c_x;
    float   c_y;
    float   c_z;
    t_color *color;
}               t_sp;

typedef struct s_plane
{
    t_vctr  *point;
    t_vctr  *normal;
    t_color *color;
}               t_plane;

typedef struct s_cylinder
{
    t_vctr  *b_point;
    t_vctr  *b_direction;
    double  height;
    double  r;
    t_color *color;
}               t_cylinder;

typedef struct s_obj
{
    struct s_sp        *sp;
    struct s_plane     *pl;
    struct s_cylinder  *clndr;
}               t_obj;

typedef struct s_cam
{
    struct t_vctr   *pos;
    struct t_vctr   *dir;
    float           fov;
}               t_cam;

typedef struct s_scene
{
    struct s_cam   *cam;
    struct s_obj   *obj;
    struct s_light *light;
}               t_scene;

t_win   *ft_window(int height, int width);
void    ft_free_win(t_win *win);
int     ft_escape_key(int key, void *param);
int     ft_close(t_win *param);
void    ft_display(t_win *w);
int	    ft_atoi(const char *str);
int	    ft_isdigit(int c);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1, char const *set);
int	    ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int     ft_check_extention(char *s);
int     ft_check_args(int ac);
char    **ft_lines(char *filename);

#endif