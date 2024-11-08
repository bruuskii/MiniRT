#include "../includes/minirt_bonus.h"

t_hit *intersect_sphere(t_ray *ray, t_sp *sphere)
{
    t_hit *hit = malloc(sizeof(t_hit));
    t_vctr oc = vec3_sub(ray->origin, *sphere->cntr);
    double a = vec3_dot(ray->direction, ray->direction);
    double b = 2.0 * vec3_dot(oc, ray->direction);
    double c = vec3_dot(oc, oc) - (sphere->d / 2) * (sphere->d / 2);
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return hit;
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);
    if (t1 > 0.001)
        hit->t = t1;
    else if (t2 > 0.001)
        hit->t = t2;
    else
        return hit;
    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    hit->normal = vec3_normalize(vec3_sub(hit->point, *sphere->cntr));
    return hit;
}

t_hit *intersect_plane(t_ray *ray, t_plane *plane)
{
    t_hit *hit = malloc(sizeof(t_hit));
    double denom = vec3_dot(ray->direction, *plane->normal);

    hit->hit = 0;
    if (fabs(denom) < 1e-6)
        return hit;
    t_vctr oc = vec3_sub(*plane->point, ray->origin);
    double t = vec3_dot(oc, *plane->normal) / denom;
    if (t < 1.0)
    {
        hit->t = t;
        hit->hit = 1;
        hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
        hit->normal = vec3_normalize(*plane->normal);

    }
    return hit;
}


double vec3_length(t_vctr v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_hit *intersect_cylinder(t_ray *ray, t_cylinder *cy) {
    t_hit *hit = malloc(sizeof(t_hit));
    hit->hit = 0;

    double a = vec3_dot(ray->direction, ray->direction) - 
               pow(vec3_dot(ray->direction, *cy->c_axis), 2);
    t_vctr oc = vec3_sub(ray->origin, *cy->c_cntr);
    double b = 2 * (vec3_dot(ray->direction, oc) - 
                    vec3_dot(ray->direction, *cy->c_axis) * 
                    vec3_dot(oc, *cy->c_axis));
    double c = vec3_dot(oc, oc) - 
               pow(vec3_dot(oc, *cy->c_axis), 2) - 
               pow(cy->d / 2, 2);

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return hit;

    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    double t = (t1 > 0 && t2 > 0) ? fmin(t1, t2) : (t1 > 0 ? t1 : (t2 > 0 ? t2 : -1));

    if (t < 0)
        return hit;

    t_vctr intersection = vec3_add(ray->origin, vec3_scale(ray->direction, t));
    double height_proj = vec3_dot(vec3_sub(intersection, *cy->c_cntr), *cy->c_axis);

    if (height_proj >= 0 && height_proj <= cy->height) {
        hit->hit = 1;
        hit->t = t;
        hit->point = intersection;
        t_vctr projection = vec3_scale(*cy->c_axis, height_proj);
        hit->normal = vec3_normalize(vec3_sub(vec3_sub(hit->point, *cy->c_cntr), projection));
        return hit;
    }

    // Cap intersection check
    double cap_t[2];
    t_vctr cap_center[2];
    cap_center[0] = vec3_add(*cy->c_cntr, vec3_scale(*cy->c_axis, 0));
    cap_center[1] = vec3_add(*cy->c_cntr, vec3_scale(*cy->c_axis, cy->height));

    for (int i = 0; i < 2; i++) {
        double denom = vec3_dot(ray->direction, *cy->c_axis);
        if (fabs(denom) > 1e-6) {
            cap_t[i] = vec3_dot(vec3_sub(cap_center[i], ray->origin), *cy->c_axis) / denom;
            t_vctr p = vec3_add(ray->origin, vec3_scale(ray->direction, cap_t[i]));
            double dist = vec3_length(vec3_sub(p, cap_center[i]));
            if (cap_t[i] > 0 && dist <= cy->d / 2) {
                hit->hit = 1;
                hit->t = cap_t[i];
                hit->point = p;
                hit->normal = vec3_normalize(vec3_sub(p, cap_center[i]));
                return hit;
            }
        }
    }

    return hit;
}

