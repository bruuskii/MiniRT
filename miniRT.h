/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:23:21 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/21 23:14:34 by kbassim          ###   ########.fr       */
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

typedef enum    s_type
{
    SPHERE,
    PLANE,
    CYLINDRE,
    LIGHT,
    ALIGHT,
    CAM,
}               t_type;

typedef struct s_win
{
    int     height;
    int     width;
    void    *ptr;
    void    *win;
    void    *img;
}               t_win;

typedef struct s_pnt
{
    float   x;
    float   y;
}               t_pnt;

typedef struct s_vctr
{
    float   x;
    float   y;
    float   z;
}               t_vctr;

typedef struct s_material
{
    t_vctr  color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

typedef struct  s_light
{
    t_vctr          *dir;
    double          brightness;
    t_vctr          *color;
    t_type          type;
    struct s_light  *next;
}               t_light;

typedef struct s_alight
{
    float   ratio;
    t_type  type;
    t_vctr *color;
}               t_alight;

typedef struct s_sp
{
    double      d;
    t_material  *mtrl;
    t_vctr      *cntr;
    t_vctr     *color;
}               t_sp;

typedef struct s_plane
{
    t_vctr  *point;
    t_vctr *normal;
    t_vctr  *color;
}               t_plane;

typedef struct s_cylinder
{
    t_vctr  *c_cntr;
    t_vctr  *c_axis;
    double  d;
    double  height;
    t_vctr  *color;
}               t_cylinder;


typedef struct s_obj
{
    t_type         type;
    t_material     *mtrl;
    void           *obj;
    struct s_obj   *next;
}               t_obj;

typedef struct s_cam
{
    t_vctr          *pos;
    t_vctr          *dir;
    t_type          type;
    double           fov;
}               t_cam;

typedef struct s_scene
{
    struct s_cam    *cam;
    struct s_obj    *obj;
    struct s_light  *light;
    struct s_alight *alight;
}               t_scene;

t_win       *ft_window(int height, int width);
void        ft_free_win(t_win *win);
int         ft_escape_key(int key, void *param);
int         ft_close(t_win *param);
void        ft_display(t_win *w, t_scene *scene);
int	        ft_isdigit(int c);
char	    *ft_strdup(const char *s1);
char	    *ft_strtrim(char const *s1, char const *set);
int	        ft_strcmp(const char *s1, const char *s2);
size_t	    ft_strlen(const char *s);
int         ft_check_extention(char *s);
int         ft_check_args(int ac);
char        **ft_lines(char *filename);
char	    **ft_fullsplit(char const *s);
int	        ft_is_void(char c);
t_obj       *ft_new(void *content);
void        ft_add_back(t_obj **objs, t_obj *node);
void	    ft_lstfree(char **lst);
char	    **ft_split(char const *s, char c);
double	    ft_atodbl(char *str);
double	    ft_atoi(char *str);
void        ft_assign_plane(t_plane *pl, char **lst);
void        ft_assign_cy(t_cylinder *cy, char **lst);
void        ft_assign_sp(t_sp *sp, char **lst);
void        ft_assign_plane_utils(t_plane **pl, char **tmp, int i);
void        ft_assign_cy_utils(t_cylinder **cy, char **lst, int i);
void        ft_assign_sp_utils(t_sp **sp, char **tmp, int i);
t_vctr      *vct_sub(t_vctr *v1, t_vctr *v2);
double      ft_magnitude(t_vctr *vec);
void        ft_assign_camera(t_cam *cam, char **lst);
void        ft_assign_cam_utils(t_cam **cam, char **tmp, int i);
t_cam       *ft_cam(char **lst);
t_obj       *ft_obj(char **lst);
t_scene     *ft_scene(char **lst);
t_scene     *data_input(char *s);
void        ft_assign_light_utils(t_light **lt, char **lst, int i);
void        ft_assign_light(t_light *lt, char **lst);
t_light     *ft_light(char **lst);
void        ft_add_back_lt(t_light **objs, t_light *node);
t_light     *ft_new_lt();
t_alight    *ft_a_light();
void        ft_assign_alight_utils(t_alight **lt, char **lst, int i);
void        ft_assign_alight(t_alight *lt, char **lst);
t_alight    *ft_alight(char **lst);

#endif