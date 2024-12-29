#include "../includes/minirt_bonus.h"
#include <math.h>

t_vec3 phong_lighting(t_vec3 light_dir, t_vec3 view_dir, t_vec3 normal, t_material *material, t_light *light)
{
    t_vec3 reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal, light_dir)), light_dir);
    
    double ambient = material->ambient;
    double diffuse = fmax(vec3_dot(normal, light_dir), 0.0) * material->diffuse;
    double specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), material->shininess) * material->specular;

    t_vec3 color = vec3_scale(material->color, ambient + diffuse);
    color = vec3_add(color, vec3_scale(light->color, specular));
    color = vec3_scale(color, light->intensity);

    return vec3_create(
        fmin(color.x, 1.0),
        fmin(color.y, 1.0),
        fmin(color.z, 1.0)
    );
}

t_vec3 calculate_lighting(t_ray *ray, t_vec3 hit_point, t_vec3 normal, t_scene *scene, t_material *material)
{
    t_vec3 light_dir = vec3_normalize(vec3_sub(scene->light.position, hit_point));
    t_vec3 view_dir = vec3_normalize(vec3_sub(ray->origin, hit_point));

    t_vec3 color = phong_lighting(light_dir, view_dir, normal, material, &scene->light);

    t_vec3 ambient = vec3_scale(scene->ambient_light, material->ambient);
    color = vec3_add(color, ambient);


    // Ensure color values are between 0 and 1
    color.x = fmax(0.0, fmin(color.x, 1.0));
    color.y = fmax(0.0, fmin(color.y, 1.0));
    color.z = fmax(0.0, fmin(color.z, 1.0));

    return color;
}