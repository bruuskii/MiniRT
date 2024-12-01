/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:23:21 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/01 20:44:50 by kbassim          ###   ########.fr       */
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
    double   x;
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
}               t_material;

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
    struct s_sp *next;
    
}               t_sp;

typedef struct s_plane
{
    t_vctr          *point;
    t_vctr          *normal;
    t_material      *mtrl;
    t_vctr          *color;
    struct s_plane  *next;
}               t_plane;

typedef struct s_cylinder
{
    t_vctr  *c_cntr;
    t_vctr  *c_axis;
    t_material      *mtrl;
    double  d;
    double  height;
    t_vctr  *color;
    struct s_cylinder  *next;
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
    struct s_sp     *sp;
    struct s_plane  *pl;
    struct s_cylinder   *cy;
    struct s_light  *light;
    struct s_alight *alight;
}               t_scene;

typedef struct s_ray
{
    t_vctr origin;
    t_vctr direction;
} t_ray;

typedef struct s_camera
{
    t_vctr position;
    t_vctr direction;
    double fov;
} t_camera;

typedef struct s_sphere
{
    t_vctr center;
    double radius;
    t_material material;
} t_sphere;

typedef struct s_hit
{
    int     hit;
    double  shaddow;
    double  t;
    t_vctr  point;
    t_vctr  normal;
} t_hit;


typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

t_vctr vec3_create(double x, double y, double z);
t_ray create_ray(t_cam *cam, double u, double v);
t_hit *intersect_sphere(t_ray *ray, t_sp *sphere);
t_ray create_shadow_ray(t_hit hit, t_vctr point, t_light *light);

t_vctr  calculate_lighting(t_ray *ray, t_hit hit, t_vctr normal, t_scene *scene, t_material *material, t_light *light, double u, double v);
t_vctr  phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal, t_material *material, t_light *light); 
t_ray   create_nray(t_vctr point, t_vctr dir, double u, double v);
int     ft_is_shadowed(t_scene *scene, t_vctr *point, double u, double v);
t_vctr vec3_add(t_vctr v1, t_vctr v2);
t_vctr vec3_sub(t_vctr v1, t_vctr v2);
t_vctr vec3_scale(t_vctr v, double t);
t_vctr vec3_cross(t_vctr v1, t_vctr v2);
double vec3_dot(t_vctr v1, t_vctr v2);
t_vctr vec3_normalize(t_vctr v);
t_hit  *intersect_plane(t_ray *ray, t_plane *plane);
t_hit  *intersect_cylinder(t_ray *ray, t_cylinder *cy);
t_hit  *intersect_scene(t_ray *ray, t_scene *scene);


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
void        ft_add_back(t_sp **objs, t_sp *node);
t_sp        *ft_new(t_sp *content);
t_plane     *ft_new_pl(t_plane *content);
t_plane     *ft_obj_pl(char **lst);
void        ft_add_back_pl(t_plane **objs, t_plane *node);
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
t_sp       *ft_obj(char **lst);
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
void        ft_add_back_cy(t_cylinder **objs, t_cylinder *node);
t_cylinder   *ft_new_cy(t_cylinder *content);
t_cylinder  *ft_obj_cy(char **lst);
double      ft_magnitude(t_vctr *vec);
void        ft_free_cylinder(t_cylinder *c);
void        ft_free_scene(t_scene *scene);
#endif