#include "../miniRT.h"

t_hit *intersect_sphere(t_ray *ray, t_sp *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    t_vctr oc = vec3_sub(ray->origin, *sphere->cntr);
    double a = vec3_dot(ray->direction, ray->direction);
    double  r = sphere->d / 2;
    double b = 2.0 * vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - r * r;
    double discriminant = b * b - 4 * a * c;
    hit->t = 0;
    if (discriminant < 0)
    {
        hit->hit = 0;
        return hit;
    }
    hit->shaddow = 0.0;
    if (discriminant)
        hit->shaddow = 1.0;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);
    if (t1 > 1e-6)
        hit->t = t1;
    else if (t2 > 1e-6)
        hit->t = t1;
    else 
        return (hit);
    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    hit->normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
    return (hit);
}


// typedef struct s_hit
// {
//     int     hit;
//     double  shaddow;
//     double  t;
//     t_vctr  point;
//     t_vctr  normal;
// } t_hit;


// t_hit *normal_sphere(t_hit *nhit, t_sp *sp, t_ray *ray)
// {
//     t_hit *tmp;

//     tmp = intersect_sphere(ray, sp);
//     if (tmp && ((nhit->t > tmp->t || nhit->t == -1) && tmp->t > 1e-6))
//     {
//         tmp->hit = vec3_add(ray->origin, vec3_scale(ray->direction, tmp->t));
//         tmp->normal = vec3_normalize(vec3_sub(tmp->normal, *sp->cntr));
//         if (vec3_dot(ray->direction, tmp->normal) > 1e-6)
//             tmp->normal = vec3_scale(tmp->normal, -1);
//         *nhit = *tmp;
//     }
//     return nhit;
// }

t_hit *intersect_plane(t_ray *ray, t_plane *plane, double d)
{
    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;

    hit->hit = 0;
    hit->t = 0;
    double denom = vec3_dot(*plane->normal, ray->direction);
    
    if (fabs(denom) < 1e-6)
        return hit;

    t_vctr oc = vec3_sub(*plane->point, ray->origin);
    double t = vec3_dot(oc, *plane->normal) / denom;
    if (t > 1e-6)
    {
        hit->t = t;
        t_vctr intersection_point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
        intersection_point.x /= (intersection_point.z + d);
        intersection_point.y /= (intersection_point.z + d);
        hit->hit = 1;
        hit->point = intersection_point;
        hit->normal = vec3_normalize(*plane->normal);
    }

    return hit;
}



t_hit *intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit = malloc(sizeof(t_hit));

    if (!hit) 
        return NULL;
    hit->hit = 0;
    hit->t = 0;
    t_vctr oc = vec3_sub(ray->origin, *cy->c_cntr);

    double a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, *cy->c_axis), 2);
    double b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction, *cy->c_axis) * vec3_dot(oc, *cy->c_axis));
    double c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2, 2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return hit;

    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);
    double t = -1;

    if (t1 > 1e-6)
        t = t1;
    else if (t2 > 1e-6)
        t = t2;
    else 
        return (hit);
    hit->t = t;
    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    t_vctr projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point, *cy->c_cntr), *cy->c_axis));
    t_vctr proj_point = vec3_add(*cy->c_cntr, projection);
    t_vctr vctr = vec3_sub(proj_point, *cy->c_cntr);
    double distance = ft_magnitude(&vctr);
    if (distance > cy->height / 2)
    {
        hit->hit = 0;
        return hit;
    }
    hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
    return hit;
}


// t_hit *intersect_scene(t_ray *ray, t_scene *scene)
// {
//     t_hit *hit = NULL;
//     t_hit *closest_hit = NULL;
//     double closest_t = INFINITY;

//     if (scene->cy)
//     {
//         t_cylinder *cy = scene->cy;
//         while (cy)
//         {
//             hit = intersect_cylinder(ray, cy);
//             if (hit->hit && hit->t < closest_t)
//             {
//                 if (closest_hit) free(closest_hit);
//                 closest_hit = hit;
//                 closest_t = hit->t;
//             }
//             free(hit);
//             cy = cy->next;
//         }
//     }
//     if (scene->sp)
//     {
//         t_sp *sphere = scene->sp;
//         while (sphere)
//         {
//             hit = intersect_sphere(ray, sphere);
//             if (hit->hit && hit->t < closest_t)
//             {
//                 if (closest_hit) free(closest_hit);
//                 closest_hit = hit;
//                 closest_t = hit->t;
//             }
//             free(hit);
//             sphere = sphere->next;
//         }
//     }
//     if (scene->pl)
//     {
//         t_plane *plane = scene->pl;
//         while (plane)
//         {
//             hit = intersect_plane(ray, plane);
//             if (hit->hit && hit->t < closest_t)
//             {
//                 if (closest_hit) free(closest_hit);
//                 closest_hit = hit;
//                 closest_t = hit->t;
//             }
//             free(hit);
//             plane = plane->next;
//         }
//     }
//     return (closest_hit);
// }
