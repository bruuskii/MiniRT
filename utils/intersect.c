#include "../miniRT.h"


double  ft_magnitude(t_vctr *vec)
{
    return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}
t_hit *intersect_sphere(t_ray *ray, t_sp *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    t_vctr oc = vec3_sub(ray->origin, *sphere->cntr);
    double a = vec3_dot(ray->direction, ray->direction);
    double r = sphere->d / 2;
    double b = 2.0 * vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - r * r;
    double discriminant = b * b - 4 * a * c;
    hit->t = 0;
    if (discriminant < 0)
    {
        hit->hit = 0;
        return hit;
    }
    hit->shaddow = discriminant ? 1.0 : 0.0;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);
    
    if (t1 > 1e-6)
        hit->t = t1;
    else if (t2 > 1e-6)
        hit->t = t2;
    else 
        return (hit);
    
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    t_vctr original_normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
    
    if (sphere->fl == 1)
    {
        double bump_intensity = 0.1;
        double noise_x = fmod(sin(hit->point.x * 10), 1.0);
        double noise_y = fmod(cos(hit->point.y * 10), 1.0);
        double noise_z = fmod(tan(hit->point.z * 10), 1.0); 
        t_vctr noise_offset = {
            noise_x * bump_intensity,
            noise_y * bump_intensity,
            noise_z * bump_intensity
        };
        hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
    }
    else
        hit->normal = original_normal;
    return (hit);
}


t_hit *intersect_plane(t_ray *ray, t_plane *plane)
{
    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;

    hit->hit = 0;
    double denom = vec3_dot(vec3_normalize(*plane->normal), ray->direction);
    
    if (fabs(denom) < 1e-6)
        return hit;

    t_vctr oc = vec3_sub(*plane->point, ray->origin);
    double t = vec3_dot(oc, *plane->normal) / denom;
    if (t > 1e-6)
    {
        hit->t = t;
        t_vctr intersection_point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
        intersection_point.x /= (intersection_point.z);
        intersection_point.y /= (intersection_point.z);
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
    if (distance > cy->height )
    {
        hit->hit = 0;
        return hit;
    }
    hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
    return hit;
}

t_hit *intersect_cone(t_ray *ray, t_cone *cone)
{
    if (!ray || !cone)
        return NULL;

    t_hit *hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;

    t_vctr CO = vec3_sub(ray->origin, *(cone->vertex));
    t_vctr D = ray->direction;
    t_vctr V = vec3_normalize(*(cone->axis));
    double k = tan(cone->tang * M_PI / 180.0);

    double D_dot_V = vec3_dot(D, V);
    double CO_dot_V = vec3_dot(CO, V);
    double D_dot_D = vec3_dot(D, D);
    double CO_dot_D = vec3_dot(CO, D);
    double CO_dot_CO = vec3_dot(CO, CO);

    double a = D_dot_D - (1.0 + k * k) * D_dot_V * D_dot_V;
    double b = 2.0 * (CO_dot_D - (1.0 + k * k) * D_dot_V * CO_dot_V);
    double c = CO_dot_CO - (1.0 + k * k) * CO_dot_V * CO_dot_V;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0 || fabs(a) < 1e-6) {
        free(hit);
        return NULL;
    }
    double sqrt_discriminant = sqrt(discriminant);
    double t0 = (-b - sqrt_discriminant) / (2.0 * a);
    double t1 = (-b + sqrt_discriminant) / (2.0 * a);
    double t;
    if (t0 > 1e-6 && t1 > 1e-6)
        t = fmin(t0, t1);
    else if (t0 > 1e-6)
        t = t0;
    else if (t1 > 1e-6)
        t = t1;
    else {
        free(hit);
        return NULL;
    }
    t_vctr intersection_point = vec3_add(ray->origin, vec3_scale(D, t));
    t_vctr hit_to_vertex = vec3_sub(intersection_point, *(cone->vertex));
    double m = vec3_dot(hit_to_vertex, V);
    if (m < cone->minm || m > cone->maxm) 
    {
        free(hit);
        return NULL;
    }
    t_vctr normal = vec3_sub(hit_to_vertex, vec3_scale(V, m));
    normal = vec3_normalize(normal);
    hit->t = t;
    hit->hit = 1;
    hit->point = intersection_point;
    hit->normal = normal;

    return hit;
}
