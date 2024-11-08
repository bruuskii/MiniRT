#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../miniRT.h"



#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

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
    double t;
    t_vctr point;
    t_vctr normal;
} t_hit;


typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

t_vctr vec3_create(double x, double y, double z);
t_ray create_ray(t_cam *cam, double u, double v);
t_hit *intersect_sphere(t_ray *ray, t_sp *sphere);
t_vctr calculate_lighting(t_ray *ray, t_vctr hit_point, t_vctr normal, t_scene *scene, t_material *material);
t_vctr phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal, t_material *material, t_light *light); 

t_vctr vec3_add(t_vctr v1, t_vctr v2);
t_vctr vec3_sub(t_vctr v1, t_vctr v2);
t_vctr vec3_scale(t_vctr v, double t);
t_vctr vec3_cross(t_vctr v1, t_vctr v2);
double vec3_dot(t_vctr v1, t_vctr v2);
t_vctr vec3_normalize(t_vctr v);
t_hit *intersect_plane(t_ray *ray, t_plane *plane);
t_hit *intersect_cylinder(t_ray *ray, t_cylinder *cy);

#endif