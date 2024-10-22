#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

#include "../../miniRT.h"
# include <mlx.h>
# include <math.h> 
# include <stdio.h>
# include <stdlib.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080

typedef struct s_ray
{
    t_vctr *origin;
    t_vctr *direction;
}               t_ray;

typedef struct s_hit
{
    int hit;
    double t;
    t_vctr *point;
    t_vctr *normal;
}               t_hit;

typedef struct s_data 
{
    void *mlx;
    void *win;
}               t_data;

t_vctr *vec3_create(double x, double y, double z);
t_ray *create_ray(t_cam *camera, double u, double v);
t_hit *intersect_sphere(t_ray *ray, t_sp *sphere);
t_vctr *calculate_lighting(t_ray *ray, t_vctr *hit_point, t_vctr *normal, t_scene *scene, t_material *material, t_color *color);
t_vctr *phong_lighting(t_vctr *light_dir, t_vctr *view_dir, t_vctr *normal, t_material *material, t_light *light, t_scene *scene, t_color *color);
t_vctr *vec3_add(t_vctr *v1, t_vctr *v2);
t_vctr *vec3_sub(t_vctr *v1, t_vctr *v2);
t_vctr *vec3_scale(t_vctr *v, double t);
t_vctr *vec3_cross(t_vctr *v1, t_vctr *v2);
double vec3_dot(t_vctr *v1, t_vctr *v2);
t_vctr *vec3_normalize(t_vctr *v);

#endif