#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>



#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typedef struct s_camera
{
    t_vec3 position;
    t_vec3 direction;
    double fov;
} t_camera;


typedef struct s_material
{
    t_vec3 color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

typedef struct s_light
{
    t_vec3 position;
    t_vec3 color;
    double intensity;
} t_light;

typedef struct s_sphere
{
    t_vec3 center;
    double radius;
    t_material material;
} t_sphere;

typedef struct s_scene
{
    t_camera camera;
    t_sphere sphere;
    t_light light;
    t_vec3 ambient_light;
} t_scene;

typedef struct s_hit
{
    int hit;
    double t;
    t_vec3 point;
    t_vec3 normal;
} t_hit;


typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

t_vec3 vec3_create(double x, double y, double z);
t_ray create_ray(t_camera *camera, double u, double v);
t_hit intersect_sphere(t_ray *ray, t_sphere *sphere);
t_vec3 calculate_lighting(t_ray *ray, t_vec3 hit_point, t_vec3 normal, t_scene *scene, t_material *material);
t_vec3 phong_lighting(t_vec3 light_dir, t_vec3 view_dir, t_vec3 normal, t_material *material, t_light *light); 

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_scale(t_vec3 v, double t);
t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);
double vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_normalize(t_vec3 v);


#endif