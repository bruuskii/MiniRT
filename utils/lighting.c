#include "../miniRT.h"

t_vctr phong_lighting(t_vctr light_dir, t_vctr view_dir, t_vctr normal, t_material *material, t_light *light)
{
    t_vctr reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal, light_dir)), light_dir);
    
    double ambient = material->ambient;
    double diffuse = fmax(vec3_dot(normal, light_dir), 0.0) * material->diffuse;
    double specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), material->shininess) * material->specular;

    t_vctr color = vec3_scale(material->color, ambient + diffuse);
    color = vec3_add(color, vec3_scale(*light->color, specular));
    color = vec3_scale(color, light->brightness);

    return (vec3_create(fmin(color.x, 255.0),fmin(color.y, 255.0),fmin(color.z, 255.0)));
}

t_hit *intersect_scene(t_ray *ray, t_scene *scene)
{
    t_hit *nearest_hit = NULL;
    double nearest_t = INFINITY;
    t_sp *sp = scene->sp;
    t_plane *pl = scene->pl;
    t_cylinder *cy = scene->cy;

    if (sp)
    {
        while (sp)
        {
            t_hit *hit = intersect_sphere(ray, sp);
            if (hit && hit->t < nearest_t)
            {
                if (nearest_hit) 
                    free(nearest_hit);
                nearest_hit = hit;
                nearest_t = hit->t;
            }
            else if (hit)
            {
                free(hit);
            }
            sp = sp->next;
        }
    }
    if (pl)
    {
        while (pl)
        {
            t_hit *hit = intersect_plane(ray, pl);
            if (hit && hit->t < nearest_t)
            {
                if (nearest_hit) 
                    free(nearest_hit);
                nearest_hit = hit;
                nearest_t = hit->t;
            }
            else if (hit)
            {
                free(hit);
            }
            pl = pl->next;
        }

    }
    if (cy)
    {
        while (cy)
        {
            t_hit *hit = intersect_cylinder(ray,cy);
            if (hit && hit->t < nearest_t)
            {
                if (nearest_hit) 
                    free(nearest_hit);
                nearest_hit = hit;
                nearest_t = hit->t;
            }
            else if (hit)
            {
                free(hit);
            }
            cy = cy->next;
        }

    }
    return nearest_hit;
}


double vec3_length(t_vctr vec) 
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// Add this at the top of your file or in a header file
t_vctr vec3_multiply(t_vctr v1, t_vctr v2)
{
    t_vctr result;
    result.x = (v1.x * v2.x) / 255.0;
    result.y = (v1.y * v2.y) / 255.0;
    result.z = (v1.z * v2.z) / 255.0;
    return result;
}

t_vctr calculate_lighting(t_ray *ray, t_hit hit, t_vctr normal, t_scene *scene, t_material *material, t_light *light, double u, double v)
{
    t_vctr color;
    t_ray raysh;
    
    t_vctr light_dir = vec3_normalize(*light->dir); 
    t_vctr view_dir = vec3_normalize(vec3_sub(ray->origin, hit.point)); 
    
    color = phong_lighting(light_dir, view_dir, normal, material, light);
    
    raysh.origin = hit.point;
    raysh.direction = vec3_scale(*light->dir, -hit.t);
    t_hit *lol = intersect_scene(&raysh, scene);
    //scene->sp->chess = 0;

    if (scene->sp && scene->sp->chess == 1)
    {
        u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
        v = 0.5 - asin(normal.y) / M_PI;
        int square_u = floor(u * 16);
        int square_v = floor(v * 16);
        t_vctr pattern_color;
        t_vctr white = {255.0, 255.0, 255.0}; 
        t_vctr black = {0.0, 0.0, 0.0};
        pattern_color = (square_u + square_v) % 2 == 0 ? white : black; 

        if (lol->hit && !lol->t)
        {
            free(lol);
            t_vctr shadowed = vec3_scale(color, -1);
            return vec3_multiply(shadowed, pattern_color);
        }
        free(lol);
        t_vctr ambient = vec3_scale(*scene->alight->color, material->ambient);
        color = vec3_add(color, ambient);
        color = vec3_multiply(color, pattern_color);
    }
    else
    {
        if (lol && lol->hit && !lol->t)
        {
            free(lol);
            return vec3_scale(color, 0.75);
        }
        free(lol);
        t_vctr ambient = vec3_scale(*scene->alight->color, material->ambient);
        color = vec3_add(color, ambient);
    }
    color.x = fmin(fmax(color.x, 0.0), 255.0);
    color.y = fmin(fmax(color.y, 0.0), 255.0);
    color.z = fmin(fmax(color.z, 0.0), 255.0);

    return color;
}




