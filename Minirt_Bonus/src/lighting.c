#include "../includes/minirt_bonus.h"
#include <math.h>

t_vctr phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal, t_material *material, t_light *light)
{
    t_vctr reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal, light_dir)), light_dir);
    
    double ambient = material->ambient;
    double diffuse = fmax(vec3_dot(normal, light_dir), 0.0) * material->diffuse;
    double specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), material->shininess) * material->specular;

    t_vctr color = vec3_scale(material->color, ambient + diffuse);
    color = vec3_add(color, vec3_scale(*light->color, specular));
    color = vec3_scale(color, light->brightness);

    return vec3_create(
        fmin(color.x, 255.0),
        fmin(color.y, 255.0),
        fmin(color.z, 255.0)
    );
}

t_vctr calculate_lighting(t_ray *ray, t_vctr hit_point, t_vctr normal, t_scene *scene, t_material *material)
{
    t_vctr light_dir = vec3_normalize(vec3_sub(*scene->light->dir, hit_point));
    t_vctr view_dir = vec3_normalize(vec3_sub(ray->origin, hit_point));

    t_vctr color = phong_lighting(light_dir, view_dir, normal, material, scene->light);

    t_vctr ambient = vec3_scale(*scene->alight->color, material->ambient);
    color = vec3_add(color, ambient);


    // Ensure color values are between 0 and 1
    color.x = fmax(0.0, fmin(color.x, 255.0));
    color.y = fmax(0.0, fmin(color.y, 255.0));
    color.z = fmax(0.0, fmin(color.z, 255.0));

    return color;
}