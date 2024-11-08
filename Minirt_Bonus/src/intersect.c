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

t_hit *intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit = malloc(sizeof(t_hit));
    double a;
    double b;
    double c;

    a = vec3_dot(ray->direction, ray->direction) - vec3_dot(ray->direction, *cy->c_axis) * vec3_dot(ray->direction, *cy->c_axis);
    b = 2 * (vec3_dot(ray->direction, vec3_sub(ray->origin, *cy->c_cntr)) - vec3_dot(ray->direction, *cy->c_axis) * (vec3_dot(vec3_sub(ray->origin, *cy->c_cntr), *cy->c_axis)));
    c = vec3_dot(vec3_sub(ray->origin, *cy->c_cntr), vec3_sub(ray->origin, *cy->c_cntr)) - vec3_dot(vec3_sub(ray->origin, *cy->c_cntr), *cy->c_axis) * vec3_dot(vec3_sub(ray->origin, *cy->c_cntr), *cy->c_axis) + (cy->d / 2) * (cy->d / 2);
    double des;
    des = b * b - 4 * a * c;
    if (des < 0)
    {
        hit->hit = 0;
        return (hit);
    }
    double t1 =  (-b - sqrt(des)) / (2 * a);
    double t2 =  (-b + sqrt(des)) / (2 * a);
    double t = -1;
    if (t1)
        t = t1;
    else
        t = t2;
    hit->t = t;
    hit->hit = 1;
    hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
    double height_proj = vec3_dot(vec3_sub(hit->point, *cy->c_cntr), *cy->c_axis);
    if (height_proj < 0 || height_proj > cy->height) 
    {
        hit->hit = 0;
        return hit;
    }
    t_vctr projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point,*cy->c_cntr), *cy->c_axis));
    hit->normal = vec3_normalize(vec3_sub(hit->point, vec3_add(*cy->c_cntr, projection)));
    return hit;
}
