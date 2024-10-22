#include "../includes/minirt_bonus.h"
#include <math.h>

t_vctr *clr_to_vctr(t_color *color)
{
    t_vctr  *vec;

    vec = malloc(sizeof(t_vctr));
    if (!vec)
        return (NULL);
    vec->x = (double)color->r;
    vec->y = (double)color->g;
    vec->z = (double)color->b;
    return (vec);
}

t_vctr *phong_lighting(t_vctr *light_dir, t_vctr *view_dir, t_vctr *normal, t_material *material, t_light *light, t_scene *scene, t_color *color)
{
    t_vctr *reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal, light_dir)), light_dir);
    (void)scene;

    double ambient = material->ambient;
    double diffuse = fmax(vec3_dot(normal, light_dir), 0.0) * material->diffuse;
    double specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), material->shininess) * material->specular;

    t_vctr *clr = vec3_scale(clr_to_vctr(color), ambient + diffuse);
    clr = vec3_add(clr, vec3_scale(clr_to_vctr(light->color), specular));
    clr = vec3_scale(clr, light->brightness);

    return vec3_create(
        fmin(clr->x, 1.0),
        fmin(clr->y, 1.0),
        fmin(clr->z, 1.0)
    );
}

t_vctr *calculate_lighting(t_ray *ray, t_vctr *hit_point, t_vctr *normal, t_scene *scene, t_material *material, t_color *color)
{
    t_vctr *light_dir = vec3_normalize(vec3_sub(scene->light->dir, hit_point));
    t_vctr *view_dir = vec3_normalize(vec3_sub(ray->origin, hit_point));
    t_vctr *color1 = phong_lighting(light_dir, view_dir, normal, material, scene->light,scene, color);
    t_vctr *ambient = vec3_scale(clr_to_vctr(scene->alight->color), material->ambient);
    t_vctr *v1;

    v1 = vec3_add(color1, ambient);
    v1->x = fmax(0.0, fmin(v1->x, 1.0));
    v1->y = fmax(0.0, fmin(v1->y, 1.0));
    v1->z = fmax(0.0, fmin(v1->z, 1.0));
    return (v1);
}