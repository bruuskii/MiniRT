#include "../includes/minirt_bonus.h"

double vec3_length(t_vctr vec) 
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
t_hit *intersect_scene_shadow(t_ray *ray, t_scene *scene, double max_dist)
{
    t_hit *hit = NULL;
    t_hit *closest_hit = NULL;
    double closest_t = INFINITY;

    if (scene->cy)
    {
        t_cylinder *cy = scene->cy;
        while (cy)
        {
            hit = intersect_cylinder(ray, cy);
            if (hit->hit && hit->t < closest_t && hit->t < max_dist)
            {
                if (closest_hit) 
                    free(closest_hit);
                closest_hit = hit;
                closest_t = hit->t;
            }
            else
                free(hit);
            cy = cy->next;
        }
    }

    if (scene->sp)
    {
        t_sp *sphere = scene->sp;
        while (sphere)
        {
            hit = intersect_sphere(ray, sphere);
            if (hit->hit && hit->t < closest_t && hit->t < max_dist)
            {
                if (closest_hit) 
                    free(closest_hit);
                closest_hit = hit;
                closest_t = hit->t;
            }
            else
                free(hit);
            sphere = sphere->next;
        }
    }

    if (scene->pl)
    {
        t_plane *plane = scene->pl;
        while (plane)
        {
            hit = intersect_plane(ray, plane);
            if (hit->hit && hit->t < closest_t && hit->t < max_dist)
            {
                if (closest_hit) 
                    free(closest_hit);
                closest_hit = hit;
                closest_t = hit->t;
            }
            else
                free(hit);
            plane = plane->next;
        }
    }

    return (closest_hit);
}

bool is_in_shadow(t_scene *scene, t_vctr hit_point, t_vctr light_pos)
{
    t_vctr light_dir = vec3_sub(light_pos, hit_point);
    double light_distance = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);
    
    t_ray shadow_ray;
    t_vctr offset = vec3_scale(light_dir, 0.001);
    shadow_ray.origin = vec3_add(hit_point, offset);
    shadow_ray.direction = light_dir;
    
    t_hit *shadow_hit = intersect_scene_shadow(&shadow_ray, scene, light_distance);
    bool in_shadow = false;

    if (shadow_hit && shadow_hit->hit && shadow_hit->t > 0.001 && shadow_hit->t < light_distance)
        in_shadow = true;
    
    if (shadow_hit)
        free(shadow_hit);
    
    return in_shadow;
}

t_vctr phong_lighting(t_ray *ray, t_hit *hit, t_material material, t_light *light, double shadow_factor)
{
    t_vctr light_dir = vec3_normalize(vec3_sub(*light->dir, hit->point));
    t_vctr view_dir = vec3_normalize(vec3_sub(ray->origin, hit->point));
    t_vctr reflect_dir = vec3_sub(vec3_scale(hit->normal, 2 * vec3_dot(hit->normal, light_dir)), 
                                 light_dir);
    
    double ambient = material.ambient;
    double diffuse = fmax(vec3_dot(hit->normal, light_dir), 0.0) * material.diffuse;
    double specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 
                         material.shininess) * material.specular;

    diffuse *= shadow_factor;
    specular *= shadow_factor;

    t_vctr color = vec3_scale(material.color, ambient + diffuse);
    color = vec3_add(color, vec3_scale(*light->color, specular));
    color = vec3_scale(color, light->brightness);

    return (vec3_create(fmin(color.x, 255.0), 
                       fmin(color.y, 255.0), 
                       fmin(color.z, 255.0)));
}

t_vctr calculate_lighting(t_ray *ray, t_hit *hit, t_scene *scene, t_material material)
{
    double shadow_factor = 1.0;
    if (is_in_shadow(scene, hit->point, *scene->light->dir))
        shadow_factor = 0.2; // Soft shadow factor

    t_vctr color = phong_lighting(ray, hit, material, scene->light, shadow_factor);
    

    t_vctr ambient = vec3_scale(*scene->alight->color, material.ambient);
    color = vec3_add(color, ambient);
    
 
    color.x = fmax(0.0, fmin(color.x, 255.0));
    color.y = fmax(0.0, fmin(color.y, 255.0));
    color.z = fmax(0.0, fmin(color.z, 255.0));
    
    return (color);
}
